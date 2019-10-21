#ifndef _CHUNK_BUILDER_H_
#define _CHUNK_BUILDER_H_
#include "main.h"

//TODO: Possibility for singleton?
class ChunkBuilder{
  std::vector<Chunk> chunks;
  std::vector<Block> ghost_blocks;

  int xlen, ylen;

  TextureSheet tex = TextureSheet("/usd/Media/textures/texture.png",16,16);
public:
  void buildChunks(int xlength, int ylength);
  Block* findBlock(CubePosition pos);

  void render();
};

#endif
