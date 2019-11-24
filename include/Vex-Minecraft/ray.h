#ifndef _RAY_H_
#define  _RAY_H_

#include "FastPix3D/FastPix3D.h"

class Ray{
public:
  Ray(Vector3f position, Vector3f direction);
  void step(float scale);
  Vector3f getEnd();
  Vector3f getLengthVec();
  float getLength();
private:
  Vector3f length;
  Vector3f end;
  Vector3f start;
  Vector3f direction;
};

#endif /* _RAY_H_ */
