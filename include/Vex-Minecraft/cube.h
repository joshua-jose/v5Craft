#include "FastPix3D/FastPix3D.h"
#include "main.h"

class Cube{
public:
  Cube(struct CubePosition icoordinate, Matrix space,bool air=false);
  CubePosition coordinate = CubePosition(0,0,0);
  Mesh *mesh;
  ShadowVolume *shadow;
  Matrix modelSpace = Matrix::Identity();

  void render(Light *light);
};
