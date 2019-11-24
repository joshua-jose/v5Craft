#include "main.h"

void ChunkBuilder::buildChunks(int xlength, int ylength){
  xlen = xlength, ylen = ylength;
  for (int i = 0; i <xlength;i++){
    for (int j = 0; j <ylength;j++){
      Chunk c = Chunk(Vector2f(i,j),&tex, this);
      chunks.push_back(c);
    }
  }
  for (int i = 0; i <xlength;i++){
    for (int j = 0; j <ylength;j++){
      chunks[(i *(ylen)) + j].generate_mesh();
    }
  }

}

std::map<Direction,Chunk*> ChunkBuilder::getAdjacentChunks(Chunk* centre){
    AdjacentChunkPositions adjPos;
    adjPos.update(centre->chunkCoordinate.X, centre->chunkCoordinate.Y);

    std::map<Direction,Chunk*> ret;
    if (adjPos.left.X < xlen && adjPos.left.X >= 0 && adjPos.left.Y < ylen && adjPos.left.Y >= 0){
      ret[Direction::left] = &chunks[adjPos.left.X * ylen + adjPos.left.Y];
    }
    if (adjPos.right.X < xlen && adjPos.right.X >= 0 && adjPos.right.Y < ylen && adjPos.right.Y >= 0){
      ret[Direction::right] = &chunks[adjPos.right.X * ylen + adjPos.right.Y];
    }
    if (adjPos.front.X < xlen && adjPos.front.X >= 0 && adjPos.front.Y < ylen && adjPos.front.Y >= 0){
      ret[Direction::front] = &chunks[adjPos.front.X * ylen + adjPos.front.Y];
    }
    if (adjPos.back.X < xlen && adjPos.back.X >= 0 && adjPos.back.Y < ylen && adjPos.back.Y >= 0){
      ret[Direction::back] = &chunks[adjPos.back.X * ylen + adjPos.back.Y];
    }
    return ret;
};

Block* ChunkBuilder::findBlock(CubePosition pos){
    if (pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.y < CHUNK_HEIGHT){
      int chunkX = pos.x / CHUNK_DIAMETER, chunkY = pos.z / CHUNK_DIAMETER;
      if (chunkX < xlen && chunkY < ylen && chunkX >= 0 && chunkY >= 0)
        return chunks[(chunkX *(ylen)) + chunkY].get_cube(pos);
    }
    ghost_blocks.emplace_back(0, pos, tex);
    //printf("Get ghosted fam %d\n", ghost_blocks.back().id);
    return &ghost_blocks.back();
}

Block* ChunkBuilder::findBlockSafe(CubePosition pos){
    if (pos.x >= 0 && pos.y >= 0 && pos.z >= 0 && pos.y < CHUNK_HEIGHT){
      int chunkX = pos.x / CHUNK_DIAMETER, chunkY = pos.z / CHUNK_DIAMETER;
      if (chunkX < xlen && chunkY < ylen && chunkX >= 0 && chunkY >= 0)
        return chunks[(chunkX *(ylen)) + chunkY].get_cube(pos);
    }
    return nullptr;
}

void ChunkBuilder::breakBlock(CubePosition pos){
  int chunk_index = index_from_cubepos(pos);
  if (chunk_index != -1){
    chunks[chunk_index].remove_cube(pos);
    for (std::pair<Direction,Chunk*> i: getAdjacentChunks(&chunks[chunk_index])){
      i.second->generate_mesh();
    }
    chunks[chunk_index].generate_mesh();
  }

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
