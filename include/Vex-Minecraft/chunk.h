#include "main.h"
#include <vector>


#ifndef _CHUNK_H_
#define _CHUNK_H_

enum Direction{
  left=0,
  right=1,
  bottom=2,
  top=3,
  front=4,
  back=5
};

//TODO: Split these functions all up!
// TODO: Optimise, asynchronise, no render on chunk borders
class Chunk{
public:
  Chunk(Vector2f ichunkCoordinate);
  ~Chunk();
  int diameter = CHUNK_DIAMETER;
  int height = CHUNK_HEIGHT;

  Vector2f chunkCoordinate;

  std::vector<std::vector<std::vector<Block>>> cubes;
  int chunk_size;
  Mesh * chunk_mesh;

  TextureSheet tex = TextureSheet("/usd/Media/textures/texture.png",16,16);

  void generate_mesh();
  void try_add_face_to_mesh(Vector3f block_coords, Direction direction, Block this_block);
  bool should_add_face_to_mesh(Block adjBlock, Block block);
  void add_face(int face, CubePosition blockpos);

  int faces_showing = 0;
  std::vector<std::vector<std::vector<float>>> meshP;
  std::vector<std::vector<float>> meshN;
  std::vector<std::vector<std::vector<float>>> meshU;
  std::vector<std::vector<int>> meshI;

  std::vector<int> faces;
  std::vector<CubePosition> blockpositions;

  std::vector<std::vector<int>> textures;

  void render(Light *light);
  void add_cube(struct CubePosition coordinate,int id);
  void remove_cube(struct CubePosition coordinate);

  void fill(int id);
};

#endif
