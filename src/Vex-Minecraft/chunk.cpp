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
  {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}},
  {{-1, 0}, {0, 0}, {-1, -1}, {0, -1}},
  {{0, -1}, {0, 0}, {-1, -1}, {-1, 0}},
  {{0, 0}, {0, -1}, {-1, 0}, {-1, -1}},
  {{0, 0}, {0, -1}, {-1, 0}, {-1, -1}},
  {{-1, 0}, {-1, -1}, {0, 0}, {0, -1}}};

static const int indices[6][6] = {
    {0, 3, 2, 0, 1, 3},
    {0, 3, 1, 0, 2, 3},
    {0, 3, 2, 0, 1, 3},
    {0, 3, 1, 0, 2, 3},
    {0, 3, 2, 0, 1, 3},
    {0, 3, 1, 0, 2, 3}
};

Chunk::Chunk(Vector2f ichunkCoordinate, TextureSheet* itex, ChunkBuilder* icb){
  chunkCoordinate = ichunkCoordinate;

  chunk_size = diameter*diameter*height;
  tex = itex;
  cb = icb;
  //cubes = (Cube*) malloc(chunk_size*sizeof(Cube));

  //fill(1);

  for (int x = 0; x < 4;x++)
    for (int y = 0; y < 8;y++)
      for (int z = 0; z < 4;z++){
        if (x < y) add_cube(CubePosition(x,y,z),0);
        else  add_cube(CubePosition(x,y,z),1);
        }



}

Chunk::~Chunk(){
}

void Chunk::add_cube(CubePosition coordinate,int id){
  //fprintf(stderr,"{%d}\n",coordinate.x + diameter * (coordinate.y + height * coordinate.z));
  cubes[to_index(coordinate)] = Block(id,coordinate,*tex);
};

void Chunk::add_face(int face, CubePosition blockpos){
              blockpositions.push_back(blockpos);
              faces.push_back(face);
              faces_showing += 1;

};


void Chunk::generate_mesh(){
  faces_showing = 0;
  std::vector<std::vector<int>>().swap(textures);

  std::vector<int>().swap(faces);
  std::vector<CubePosition>().swap(blockpositions);

  adjacentChunks = cb->getAdjacentChunks(this);

  AdjacentBlockPositions abp;

  for (int z = 0; z < diameter; z++){
    for (int x = 0; x < diameter; x++){
      for (int y = 0; y < height; y++){
          Block this_block = cubes[to_index(x,y,z)];
          if (this_block.id == 0)
            continue;
          abp.update(x,y,z);
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

      subset->AppliedTexture = new Texture(tex->getTexture(textures[i][0],textures[i][1]),16,16);
      for (int32 a = 0; a < vertexCount; a++)
      {
        Vector3f position = Vector3f(
          (chunkCoordinate.X * diameter) + (blockpositions[i].x*2) + positions[faces[i]][a][0],
          (blockpositions[i].y*2) + positions[faces[i]][a][1],
          (chunkCoordinate.Y * diameter) + (blockpositions[i].z*2) + positions[faces[i]][a][2]);

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
  bool no_adj = false;
  if (this_block.id == 0) return;
  if (block_coords.Z >= diameter || block_coords.X >= diameter || block_coords.Y >= height ||
      block_coords.Z < 0         || block_coords.X < 0         || block_coords.Y < 0){
      no_adj = true;
      /*TODO: Actually get inter chunk culling working
       *probably need to redo cube memory structures for this throughout
       * To get acceptable performance */

      if(this_block.id != 0){
        auto adjChunk= adjacentChunks.find(direction);
        if (adjChunk != adjacentChunks.end()) {
          int globX = block_coords.X+ (diameter*static_cast<int>(chunkCoordinate.X));
          int globZ = block_coords.Z+ (diameter*static_cast<int>(chunkCoordinate.Y));
          if (adjChunk->second->get_cube(CubePosition(globX,static_cast<int>(block_coords.Y),globZ))->id == 0){
              should_add_face = true;
            }
          }
        else should_add_face = true;
      }
    }

  if (!should_add_face && !no_adj){
    Block adjBlock = cubes[to_index(block_coords.X,block_coords.Y,block_coords.Z)];
    should_add_face = should_add_face_to_mesh(adjBlock, this_block);
  }

  if (should_add_face){
    add_face((int)direction, CubePosition(this_block.coordinate.x, this_block.coordinate.y, this_block.coordinate.z));
    std::vector<int> texture(2);
    texture[0] = Block::getTexture(this_block.id,(int)direction,0);
    texture[1] = Block::getTexture(this_block.id,(int)direction,1);
    textures.push_back(texture);
  }
}
bool Chunk::should_add_face_to_mesh(Block adjBlock, Block block){
  if (adjBlock.id == 0 && block.id != 0) return true;
  return false;
}

void Chunk::render(){

    if(chunk_mesh){
      Matrix modelSpace = Matrix::Translate(
        Vector3f(chunkCoordinate.X * diameter,0,chunkCoordinate.Y*diameter)) /** Matrix::RotateX(180)*/;
      chunk_mesh->Draw(modelSpace);
    }
    //fprintf(stderr,"%d\n",faces_showing);
};

void Chunk::remove_cube(CubePosition coordinate){
  add_cube(coordinate,0);
};

int Chunk::to_index(CubePosition coordinate){
  return coordinate.x + diameter * (coordinate.y + height * coordinate.z);
}
int Chunk::to_index(int x, int y, int z){
  return x + diameter * (y + height * z);
}

// Global cube position
Block* Chunk::get_cube(struct CubePosition coordinate){

    int localX = coordinate.x- (diameter*static_cast<int>(chunkCoordinate.X));
    int localZ = coordinate.z- (diameter*static_cast<int>(chunkCoordinate.Y));

    if (localZ < diameter && localX < diameter  && coordinate.y < height &&
        localZ >= 0 && localX >= 0 && coordinate.y >= 0){

          return &cubes[to_index(
          localX,
          coordinate.y,
          localZ)];
    }
    /*
    fprintf(stderr,"Chunk X: %d, Chunk Y: %d, Block X: %d, Block Y: %d, Block Z: %d;\n",
    static_cast<int>(chunkCoordinate.X),static_cast<int>(chunkCoordinate.Y),
    coordinate.x,coordinate.y,coordinate.z);
    */

    return &empty;
}

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
