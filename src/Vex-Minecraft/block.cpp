#include "main.h"

static const int TexMap[BLOCK_COUNT][6][2] = {
  // Left,Right, bottom, top,  front, back
  {{0,14},{0,14},{0,15},{0,13},{0,14},{0,14}} // Grass
};

Block::Block() : coordinate(0,0,0){
  id = 0;
  coordinate = CubePosition(0,0,0);
}

Block::Block(int iid, struct CubePosition icoordinate, TextureSheet tex): coordinate(icoordinate){
  id = iid;


  for (int i = 0; i<6;i++)
    for (int j = 0; j<2;j++)
      texMap[i][j] = TexMap[0][i][j];
}
