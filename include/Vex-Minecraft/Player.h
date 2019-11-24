#ifndef _PLAYER_H_
#define  _PLAYER_H_

#include "FastPix3D/FastPix3D.h"

class Player{
public:
  Vector3f position;
  Vector3f rotation;
  Player();
  void update(ChunkBuilder* cb);
private:
  FreelookManager flm;
};

#endif // _PLAYER_H_
