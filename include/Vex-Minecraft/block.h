#include "main.h"

#ifndef _BLOCK_H_
#define _BLOCK_H_
class Block{
public:
  Block();
  int id;
private:
  Cube cube; // TODO: make this one big cube renderer for memory savings
};

#endif
