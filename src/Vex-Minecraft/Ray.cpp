#include  "main.h"
#include "FastPix3D/FastPix3D.h"

Ray::Ray(Vector3f iposition, Vector3f idirection){
  start = iposition;
  direction = idirection;

  length = Vector3f(0,0,0);
  end = start;
};
void Ray::step(float scale){

  /*printf("ray direction X: %f, Y: %f, Z: %f\n", sin(direction.Y* DEG2R),
  tan(direction.X* DEG2R), cos(direction.Y* DEG2R));*/

  Vector3f stepVector = Vector3f(
    -sin(direction.Y* (M_PI/180)) * scale,
     tan(direction.X* (M_PI/180)) * scale,
     cos(direction.Y* (M_PI/180)) * scale
  );

  end += stepVector;
  length = end - start;
};

Vector3f Ray::getEnd(){
  return end;
};

Vector3f Ray::getLengthVec(){
  return length;
};

float Ray::getLength(){
  return length.getLength();
};
