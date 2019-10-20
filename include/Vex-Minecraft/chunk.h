#include "main.h"
#include <vector>

#define CHUNK_DIAMETER 1
#define CHUNK_HEIGHT 1

#ifndef _CHUNK_H_
#define _CHUNK_H_

class Chunk{
public:
  Chunk(Vector2f ichunkCoordinate);
  ~Chunk();
  int diameter = CHUNK_DIAMETER;
  int height = CHUNK_HEIGHT;

  Vector2f chunkCoordinate;

  std::vector<Cube> cubes;
  int chunk_size;

  TextureSheet tex = TextureSheet("/usd/Media/textures/texture.png",16,16);

  void render(Light *light);
  void add_cube(struct CubePosition coordinate,bool air);
  void remove_cube(struct CubePosition coordinate);

  void fill(bool air = true);
};

#endif
