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
public:
  std::vector<Chunk> chunks;
  std::vector<Block> ghost_blocks;

  int xlen, ylen;
#ifdef THREADS_STD
  TextureSheet tex = TextureSheet("Media/textures/texture.png",16,16);
#else
  TextureSheet tex = TextureSheet("/usd/Media/textures/texture.png",16,16);
#endif

  void buildChunk(int x, int y);
  void buildChunks(int xlength, int ylength);
  Block* findBlock(CubePosition pos);
  Block* findBlockSafe(CubePosition pos);

  Chunk* findChunk(int x, int y);

  void breakBlock(CubePosition pos);

  std::map<Direction,Chunk*> getAdjacentChunks(Chunk* centre);

  void render();
private:
  int index_from_cubepos(CubePosition pos);
};

#endif
