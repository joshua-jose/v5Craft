#include "main.h"

#ifndef _BLOCK_H_
#define _BLOCK_H_
class Block{
public:
  Block();
  Block(int id, struct CubePosition icoordinate, TextureSheet tex);
  CubePosition coordinate;
  int id;
  int texMap[6][2];
};

#endif
