#include "main.h"

#ifndef _BLOCK_H_
#define _BLOCK_H_
class Block{
public:
  Block();
  Block(int id, struct CubePosition icoordinate, TextureSheet tex);
  CubePosition coordinate;
  int id;

  static int getTexture(int id, int face, int coord);
};

#endif
