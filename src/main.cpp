#include "main.h"
#include "api.h"
#include "FastPix3D/FastPix3D.h"
#include <vector>

// When switching between PC and V5, the delays need to be commented out/ uncommented out.
// Thank you cmake/mingw for just not working

ChunkBuilder *cb;
bool programrunning;
int last_time;
Player *player;

void initialize() {
    //pros::delay(100);
    fprintf(stderr,"init\n");
    Device::Initialize(LV_HOR_RES, LV_VER_RES);

    //int last_time = pros::millis();
    RenderStates::Lights[0]->Enabled = true;
  	RenderStates::Lights[0]->Type = LightType::Spot;
  	RenderStates::Lights[0]->Intensity = 40;
  	RenderStates::Lights[0]->DiffuseColor = Color(165, 210, 255);

    Light::AmbientColor = Color(200, 200, 200);
    cb = new ChunkBuilder();
    cb->buildChunks(2,2);
    RenderStates::Lights[0]->Enabled = false;
    RenderStates::EnableStencilMask = false;
    RenderStates::cullMode = CullMode::Back;

    player = new Player;

    programrunning = true;
}

void run_game(){
    Device::ClearBackBuffer(Color(13,195,219));
    Device::ClearDepthBuffer();
    Device::ClearStencilBuffer();

    Input::Update(5);

    player->update(cb);
    cb->render();
    Device::Present();
}

void opcontrol() {
    while (programrunning) {
        //float time = pros::millis() - last_time;
        //last_time = pros::millis();
        run_game();
        //pros::delay(1);
    }
    Device::Destroy();
}
#ifdef THREADS_STD
#include "pcbuild/SDL/SDL.h"
int main(int argc, char *argv[]){
    SDL_Event evt;
    SDL_PumpEvents();
    initialize();
    while (true){
      run_game();
      while( SDL_PollEvent(&evt) ){
        switch(evt.type){
          case SDL_QUIT:
          programrunning = false;
          break;
        }
      }
    }
}
#endif

void disabled() {}
void competition_initialize() {}
void autonomous() {}
