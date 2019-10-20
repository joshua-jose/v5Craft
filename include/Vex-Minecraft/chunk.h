#include "main.h"
#include <vector>

#define CHUNK_DIAMETER 2
#define CHUNK_HEIGHT 2

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

  void render(Light *light);
  void add_cube(struct CubePosition coordinate,bool air);
  void remove_cube(struct CubePosition coordinate);

  void fill(bool air = true);
};

#endif
