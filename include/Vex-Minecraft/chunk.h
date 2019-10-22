class ChunkBuilder;

#include "main.h"
#include <vector>


#ifndef _CHUNK_H_
#define _CHUNK_H_


enum Direction{
  left=0,
  right=1,
  bottom=2,
  top=3,
  front=4,
  back=5
};

struct AdjacentBlockPositions
{
    void update(int x, int y, int z)
    {
        up     =   Vector3f(x,     y - 1,  z    );
        down   =   Vector3f(x,     y + 1,  z    );
        left   =   Vector3f(x - 1, y,      z    );
        right  =   Vector3f(x + 1, y,      z    );
        front  =   Vector3f(x,     y,      z - 1);
        back   =   Vector3f(x,     y,      z + 1);
    }

    Vector3f up;
    Vector3f down;
    Vector3f left;
    Vector3f right;
    Vector3f front;
    Vector3f back;
};

//TODO: Split these functions all up!
// TODO: Optimise, asynchronise, no render on chunk borders
class Chunk{
public:
  Chunk(Vector2f ichunkCoordinate, TextureSheet* itex, ChunkBuilder* icb);
  ~Chunk();
  int diameter = CHUNK_DIAMETER;
  int height = CHUNK_HEIGHT;

  Vector2f chunkCoordinate;

  //TODO: what happens if a coordinate is negative? Need a better solution
  std::array<Block,CHUNK_HEIGHT*CHUNK_DIAMETER*CHUNK_DIAMETER> cubes;
  int chunk_size;
  Mesh * chunk_mesh;
  ChunkBuilder* cb;

  bool mesh_ready = false;

  Block empty;

  TextureSheet *tex;

  void generate_mesh();
  void try_add_face_to_mesh(Vector3f block_coords, Direction direction, Block this_block);
  bool should_add_face_to_mesh(Block adjBlock, Block block);
  void add_face(int face, CubePosition blockpos);

  int faces_showing = 0;
  std::vector<int> faces;
  std::vector<CubePosition> blockpositions;
  std::vector<std::vector<int>> textures;
  std::map<Direction,Chunk*> adjacentChunks;

  int to_index(CubePosition coordinate);
  int to_index(int x, int y, int z);

  void render();
  void add_cube(struct CubePosition coordinate,int id);
  void remove_cube(struct CubePosition coordinate);
  Block* get_cube(struct CubePosition coordinate);

  void fill(int id);
};

#endif
