#include "main.h"

Chunk::Chunk(Vector2f ichunkCoordinate){
  chunkCoordinate = ichunkCoordinate;
  chunk_size = diameter*diameter*height;
  //cubes = (Cube*) malloc(chunk_size*sizeof(Cube));
  fill();

}

Chunk::~Chunk(){
}

void Chunk::add_cube(CubePosition coordinate,bool air){
  fprintf(stderr,"{%d}\n",coordinate.x + diameter * (coordinate.y + height * coordinate.z));

  cubes.push_back(Cube(coordinate,
    Matrix::Translate(Vector3f(coordinate.x*1.9,coordinate.y*1.9,coordinate.z*1.9)),air));
};

void Chunk::render(Light *light){
  for (auto i = cubes.begin(); i != cubes.end(); ++i)
      i->render(light);


};

void Chunk::remove_cube(CubePosition coordinate){
  //for ()
};

void Chunk::fill(bool air){
  for (int x = 0; x < diameter;x++){
    for (int y = 0; y < height;y++){
      for (int z = 0; z < diameter;z++){
            fprintf(stderr,"(%d,%d,%d)",x,y,z);
            add_cube(CubePosition(x,y,z),true);

      }
    }
  }
};
