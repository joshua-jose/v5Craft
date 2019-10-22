#include "main.h"

static const int TexMap[BLOCK_COUNT][6][2] = {
  // Left, Right, top,   bottom, front, back
  {{0,14},{0,14},{0,13},{0,15},{0,14},{0,14}}, // Grass
  {{4,14},{4,14},{4,15},{4,15},{4,14},{4,14}} // Oak log
};

Block::Block() : coordinate(0,0,0){
  id = 0;
  coordinate = CubePosition(0,0,0);
}

Block::Block(int iid, struct CubePosition icoordinate, TextureSheet tex): coordinate(icoordinate){
  id = iid;
}

int Block::getTexture(int id, int face, int coord){
  return TexMap[id-1][face][coord];
}
