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

Cube::Cube(struct CubePosition icoordinate, Matrix space, bool air){
  coordinate = icoordinate;
  modelSpace = space;
  mesh = new Mesh(6);
  int32 vertexCount = 4, triangleCount= 2;
  for (int32 i = 0; i < mesh->SubsetCount; i++)
  {
    Subset *subset = new Subset(vertexCount, triangleCount);

    subset->AppliedTexture = new Texture(256,256);

    for (int32 a = 0; a < vertexCount; a++)
    {
      Vector3f position = Vector3f(positions[i][a][0],positions[i][a][1],positions[i][a][2]);
      Vector3f normal= Vector3f(normals[i][0],normals[i][1],normals[i][2]);
      Vector2f UVs = Vector2f(uvs[i][a][0],uvs[i][a][1]);
      subset->Vertices[a] = Vertex(position,normal,UVs);
      subset->Vertices[a].VertexColor = Color(255, 255, 255);

    }

    subset->Triangles[0].Vertex1 = &subset->Vertices[indices[i][0]];
    subset->Triangles[0].Vertex2 = &subset->Vertices[indices[i][1]];
    subset->Triangles[0].Vertex3 = &subset->Vertices[indices[i][2]];
    subset->Triangles[1].Vertex1 = &subset->Vertices[indices[i][3]];
    subset->Triangles[1].Vertex2 = &subset->Vertices[indices[i][4]];
    subset->Triangles[1].Vertex3 = &subset->Vertices[indices[i][5]];


    mesh->Subsets[i] = subset;
  };
  shadow = new ShadowVolume(mesh);
}

void Cube::render(Light *light){
  mesh->Draw(modelSpace);
  shadow->Draw(light, modelSpace, 20);
}
