#include "main.h"

Player::Player(){
  RenderStates::ClipNear = 1.0f;
  RenderStates::Zoom = 2;
  position = Vector3f(0,0,0);
  rotation = Vector3f(0,0,0);
};

void Player::update(ChunkBuilder *cb){
  RenderStates::CameraSpace = flm.Update();
  position = flm.getPosition() / 2;
  position.X = -flm.getPosition().X / 2;
  position.Y = -flm.getPosition().Y / 2;
  position.Z = -flm.getPosition().Z / 2;

  rotation = flm.getRotation();
  if(Input::getKeyDown(DIGITAL_R1)){
    printf("raying\n");
    //printf("x: %f, y: %f, z: %f\n",position.X,position.Y,position.Z);
    Ray r(position, rotation);
    while(r.getLength() < 12){
      CubePosition rayPos((int)r.getEnd().X,(int)r.getEnd().Y,(int)r.getEnd().Z);
      Block* b = cb->findBlockSafe(rayPos);

      //printf("x: %f, y: %f, z: %f\n",r.getEnd().X,r.getEnd().Y,r.getEnd().Z);
      //printf("%d\n",b->id);
      if (b != nullptr && b->id != 0 && b->id < BLOCK_COUNT && b->id > 0 &&
          r.getEnd().X >= 0 && r.getEnd().Y >= 0 && r.getEnd().Z >= 0){
          printf("x: %f, y: %f, z: %f\n",position.X,position.Y,position.Z);
          printf("Found %d\n", b->id);
          cb->breakBlock(rayPos);
          break;
      }
      r.step(0.1);

    }
  }
  //printf("X: %f Y: %f Z: %f\n",position.X,position.Y,position.Z);
}
