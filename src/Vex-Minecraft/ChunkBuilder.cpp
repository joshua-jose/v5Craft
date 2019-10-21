#include "main.h"

void ChunkBuilder::buildChunks(int xlength, int ylength){
  xlen = xlength, ylen = ylength;
  for (int i = 0; i <xlength;i++)
    for (int j = 0; j <ylength;j++){
      Chunk c = Chunk(Vector2f(i,j),&tex, this);
      c.generate_mesh();
      chunks.push_back(c);
    }
}

Block* ChunkBuilder::findBlock(CubePosition pos){
    if (pos.x > 0 && pos.y > 0 && pos.z > 0 && pos.y < CHUNK_HEIGHT){
      int chunkX = pos.x / CHUNK_DIAMETER, chunkY = pos.z / CHUNK_DIAMETER;
        return chunks[(chunkX *(ylen)) + chunkY].get_cube(pos);


    }
    Block b = Block(0, pos, tex);
    ghost_blocks.push_back(b);
    return &ghost_blocks.back();
}

void ChunkBuilder::render(){
  for (Chunk i: chunks){
    i.render();
  }
}
