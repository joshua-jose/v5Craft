#ifndef _CHUNK_BUILDER_H_
#define _CHUNK_BUILDER_H_
#include "main.h"

struct AdjacentChunkPositions
{
    void update(int x, int y)
    {
        left   =   Vector2f(x - 1, y    );
        right  =   Vector2f(x + 1, y    );
        front  =   Vector2f(x,     y - 1);
        back   =   Vector2f(x,     y + 1);
    }
    Vector2f left;
    Vector2f right;
    Vector2f front;
    Vector2f back;
};

//TODO: Possibility for singleton?
class ChunkBuilder{
  std::vector<Chunk> chunks;
  std::vector<Block> ghost_blocks;

  int xlen, ylen;

  TextureSheet tex = TextureSheet("Media/textures/texture.png",16,16);
public:
  void buildChunks(int xlength, int ylength);
  Block* findBlock(CubePosition pos);

  std::map<Direction,Chunk*> getAdjacentChunks(Chunk* centre);

  void render();
};

#endif
