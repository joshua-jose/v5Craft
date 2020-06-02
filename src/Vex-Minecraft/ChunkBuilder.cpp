#include "main.h"
#include <algorithm>

void ChunkBuilder::buildChunk(int x, int y){
  Chunk c = Chunk(Vector2f(x,y),&tex, this);


  for (std::pair<Direction,Chunk*> i: getAdjacentChunks(&c)){
    if (i.second != nullptr)
      i.second->generate_mesh();
  }
  c.generate_mesh();
  chunks.push_back(c);
}

void ChunkBuilder::buildChunks(int xlength, int ylength){
  xlen = xlength, ylen = ylength;
  //chunks.reserve(xlength * ylength);

  for (int i = 0; i <xlength;i++){
    for (int j = 0; j <ylength;j++){
      buildChunk(i,j);
    }
  }
  /*
  for (int i = 0; i <xlength;i++){
    for (int j = 0; j <ylength;j++){
      chunks[(i *(ylen)) + j].generate_mesh();
    }
  }*/

}

Chunk* ChunkBuilder::findChunk(int x, int y){
  auto chunk = std::find_if(chunks.begin(), chunks.end(), [=](const Chunk chunk){
    return x == chunk.chunkCoordinate.X && y == chunk.chunkCoordinate.Y;
  });
  if (chunk != chunks.end())
    return &*chunk;

  return nullptr;
}

std::map<Direction,Chunk*> ChunkBuilder::getAdjacentChunks(Chunk* centre){
    AdjacentChunkPositions adjPos;
    adjPos.update(centre->chunkCoordinate.X, centre->chunkCoordinate.Y);

    std::map<Direction,Chunk*> ret;
    ret[Direction::left] = findChunk(adjPos.left.X, adjPos.left.Y);
    ret[Direction::right] = findChunk(adjPos.right.X, adjPos.right.Y);
    ret[Direction::front] = findChunk(adjPos.front.X, adjPos.front.Y);
    ret[Direction::back] = findChunk(adjPos.back.X, adjPos.back.Y);
    return ret;
};

Block* ChunkBuilder::findBlock(CubePosition pos){
    int chunkX = pos.x / CHUNK_DIAMETER, chunkY = pos.z / CHUNK_DIAMETER;
    auto chunk = findChunk(chunkX,chunkY);
    if (chunk != nullptr)
      return chunk->get_cube(pos);


    ghost_blocks.emplace_back(0, pos, tex);
    //printf("Get ghosted fam %d\n", ghost_blocks.back().id);
    return &ghost_blocks.back();
}

Block* ChunkBuilder::findBlockSafe(CubePosition pos){
    int chunkX = pos.x / CHUNK_DIAMETER, chunkY = pos.z / CHUNK_DIAMETER;
    auto chunk = findChunk(chunkX,chunkY);
    if (chunk != nullptr)
      return chunk->get_cube(pos);

    return nullptr;
}

void ChunkBuilder::breakBlock(CubePosition pos){
  Chunk* chunk = findChunk(pos.x / CHUNK_DIAMETER,pos.z / CHUNK_DIAMETER);
  if (chunk == nullptr) return;

  chunk->remove_cube(pos);
  for (std::pair<Direction,Chunk*> i: getAdjacentChunks(chunk)){
    if (i.second == nullptr) continue;
    i.second->generate_mesh();
  }
  chunk->generate_mesh();


};

int ChunkBuilder::index_from_cubepos(CubePosition pos){
  if (pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.y < CHUNK_HEIGHT){
    int chunkX = pos.x / CHUNK_DIAMETER, chunkY = pos.z / CHUNK_DIAMETER;
    if (chunkX < xlen && chunkY < ylen && chunkX >= 0 && chunkY >= 0)
      return (chunkX *(ylen)) + chunkY;
  }
  return -1;
}

void ChunkBuilder::render(){
  for (Chunk i: chunks){
    i.render();
  }
}
