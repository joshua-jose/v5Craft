#include "main.h"

static const float positions[6][4][3] = {
    {{-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1}},
    {{+1, -1, -1}, {+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}},
    {{-1, +1, -1}, {-1, +1, +1}, {+1, +1, -1}, {+1, +1, +1}},
    {{-1, -1, -1}, {-1, -1, +1}, {+1, -1, -1}, {+1, -1, +1}},
    {{-1, -1, -1}, {-1, +1, -1}, {+1, -1, -1}, {+1, +1, -1}},
    {{-1, -1, +1}, {-1, +1, +1}, {+1, -1, +1}, {+1, +1, +1}}
};
static const float normals[6][3] = {
    {-1, 0, 0},
    {+1, 0, 0},
    {0, +1, 0},
    {0, -1, 0},
    {0, 0, -1},
    {0, 0, +1}
};
static const float uvs[6][4][2] = {
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
    {{1, 0}, {0, 0}, {1, 1}, {0, 1}},
    {{0, 1}, {0, 0}, {1, 1}, {1, 0}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    {{1, 0}, {1, 1}, {0, 0}, {0, 1}}
};
static const int indices[6][6] = {
    {0, 3, 2, 0, 1, 3},
    {0, 3, 1, 0, 2, 3},
    {0, 3, 2, 0, 1, 3},
    {0, 3, 1, 0, 2, 3},
    {0, 3, 2, 0, 1, 3},
    {0, 3, 1, 0, 2, 3}
};

Chunk::Chunk(Vector2f ichunkCoordinate){
  chunkCoordinate = ichunkCoordinate;
  chunk_size = diameter*diameter*height;

  cubes.resize(diameter);
  for (int i = 0; i < diameter;i++){
    cubes[i].resize(diameter);
    for (int j = 0; j < diameter;j++){
      cubes[i][j].resize(height);
    }
  }
  //cubes = (Cube*) malloc(chunk_size*sizeof(Cube));

  fill(0);
  add_cube(CubePosition(0,0,0),1);

  generate_mesh();

}

Chunk::~Chunk(){
}

void Chunk::add_cube(CubePosition coordinate,int id){
  //fprintf(stderr,"{%d}\n",coordinate.x + diameter * (coordinate.y + height * coordinate.z));

  cubes[coordinate.z][coordinate.x][coordinate.y] = Block(id,coordinate,tex);
};

void Chunk::add_face(int face, CubePosition blockpos){

              // 2D vectors in C++ ugh
              std::vector<std::vector<float> > pos{
                  {positions[face][0][0] + blockpos.x,positions[face][0][1] + blockpos.y,positions[face][0][2] + blockpos.z},
                  {positions[face][1][0] + blockpos.x,positions[face][1][1] + blockpos.y,positions[face][1][2] + blockpos.z},
                  {positions[face][2][0] + blockpos.x,positions[face][2][1] + blockpos.y,positions[face][2][2] + blockpos.z},
                  {positions[face][3][0] + blockpos.x,positions[face][3][1] + blockpos.y,positions[face][3][2] + blockpos.z}};

              /*
              std::vector<float> norms = {normals[face][0],normals[face][1],normals[face][2]};

              std::vector<std::vector<float> > Uv{
                  {uvs[face][0][0],uvs[face][0][1]},
                  {uvs[face][1][0],uvs[face][1][1]},
                  {uvs[face][2][0],uvs[face][2][1]},
                  {uvs[face][3][0],uvs[face][3][1]}};

              std::vector<int> ind = {indices[face][0],indices[face][1],indices[face][2]};



              meshN.push_back(norms);
              meshU.push_back(Uv);
              meshI.push_back(ind);
              */
              meshP.push_back(pos);
              faces.push_back(face);
              faces_showing += 1;

};

struct AdjacentBlockPositions
{
    void update(int x, int y, int z)
    {
        up     =   Vector3f(x,     y + 1,  z    );
        down   =   Vector3f(x,     y - 1,  z    );
        left   =   Vector3f(x - 1, y,      z    );
        right  =   Vector3f(x + 1, y,      z    );
        front  =   Vector3f(x,     y,      z + 1);
        back   =   Vector3f(x,     y,      z - 1);
    }

    Vector3f up;
    Vector3f down;
    Vector3f left;
    Vector3f right;
    Vector3f front;
    Vector3f back;
};



void Chunk::generate_mesh(){
  faces_showing = 0;
  std::vector<std::vector<std::vector<float>>>().swap(meshP);
  std::vector<std::vector<std::vector<float>>>().swap(meshU);
  std::vector<std::vector<float>>().swap(meshN);
  std::vector<std::vector<int>>().swap(meshI);
  std::vector<std::vector<int>>().swap(textures);

  AdjacentBlockPositions abp;

  for (int z = 0; z < diameter; z++){
    for (int x = 0; x < diameter; x++){
      for (int y = 0; y < diameter; y++){
          abp.update(x,y,z);
          Block this_block = cubes[z][x][y];
          try_add_face_to_mesh(abp.up, Direction::top,this_block);
          try_add_face_to_mesh(abp.down, Direction::bottom,this_block);

          try_add_face_to_mesh(abp.left,Direction::left,this_block);
          try_add_face_to_mesh(abp.right, Direction::right,this_block);

          try_add_face_to_mesh(abp.front, Direction::front,this_block);
          try_add_face_to_mesh(abp.back, Direction::back,this_block);

      }
    }
  }
  chunk_mesh = new Mesh(faces_showing);


  int32 vertexCount = 4, triangleCount= 2;

  for (int32 i = 0; i < chunk_mesh->SubsetCount; i++)
    {
      Subset *subset = new Subset(vertexCount, triangleCount);

      subset->AppliedTexture = new Texture(tex.getTexture(textures[i][0],textures[i][1]),16,16);

      for (int32 a = 0; a < vertexCount; a++)
      {
        Vector3f position = Vector3f(positions[faces[i]][a][0],positions[faces[i]][a][1],positions[faces[i]][a][2]);
        Vector3f normal= Vector3f(normals[faces[i]][0],normals[faces[i]][1],normals[faces[i]][2]);
        Vector2f UVs = Vector2f(uvs[faces[i]][a][0],uvs[faces[i]][a][1]);
        subset->Vertices[a] = Vertex(position,normal,UVs);
        subset->Vertices[a].VertexColor = Color(255, 255, 255);

      }

      subset->Triangles[0].Vertex1 = &subset->Vertices[indices[faces[i]][0]];
      subset->Triangles[0].Vertex2 = &subset->Vertices[indices[faces[i]][1]];
      subset->Triangles[0].Vertex3 = &subset->Vertices[indices[faces[i]][2]];
      subset->Triangles[1].Vertex1 = &subset->Vertices[indices[faces[i]][3]];
      subset->Triangles[1].Vertex2 = &subset->Vertices[indices[faces[i]][4]];
      subset->Triangles[1].Vertex3 = &subset->Vertices[indices[faces[i]][5]];

      chunk_mesh->Subsets[i] = subset;
    };
};

void Chunk::try_add_face_to_mesh(Vector3f block_coords, Direction direction, Block this_block){

  bool should_add_face = false;
  if (block_coords.Z >= diameter || block_coords.X >= diameter || block_coords.Y >= height ||
      block_coords.Z < 0         || block_coords.X < 0         || block_coords.Y < 0)
      should_add_face = true;

  if (!should_add_face){
    Block adjBlock = cubes[block_coords.Z][block_coords.X][block_coords.Y];
    should_add_face = should_add_face_to_mesh(adjBlock, this_block);
  }

  if (should_add_face){
    add_face((int)direction, CubePosition(block_coords.X,block_coords.Y,block_coords.Z));
    std::vector<int> texture(2);
    texture[0] = this_block.texMap[(int)direction][0];
    texture[1] = this_block.texMap[(int)direction][1];
    textures.push_back(texture);
  }
}
bool Chunk::should_add_face_to_mesh(Block adjBlock, Block block){
  if (adjBlock.id == 0 && block.id != 0) return true;
  return false;
}

void Chunk::render(Light *light){


    Matrix modelSpace = Matrix::Translate(
      Vector3f(chunkCoordinate.X*1.9 * diameter,0,chunkCoordinate.Y*1.9*diameter)) * Matrix::RotateX(180);


    chunk_mesh->Draw(modelSpace);
    fprintf(stderr,"%d\n",faces_showing);
};

void Chunk::remove_cube(CubePosition coordinate){
  //for ()
};

void Chunk::fill(int id){
  for (int x = 0; x < diameter;x++){
    for (int y = 0; y < height;y++){
      for (int z = 0; z < diameter;z++){
            //fprintf(stderr,"(%d,%d,%d)",x,y,z);
            add_cube(CubePosition(x,y,z),id);

      }
    }
  }
};
