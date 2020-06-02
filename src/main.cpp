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
Skybox *skybox;

int chunkx = 15, chunky=15, currentchunkx=0, currentchunky=0;
int currentloop = 0 , buildinterval = 5;

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

    RenderStates::Lights[0]->Enabled = false;
    RenderStates::EnableStencilMask = false;
    RenderStates::cullMode = CullMode::Back;

    player = new Player;
    skybox = new Skybox;

    programrunning = true;
}

void builder(){
  if (currentchunkx < chunkx && currentchunky < chunky){
    currentloop++;
    if (currentloop < buildinterval){
      return;
    }
    currentloop = 0;
    fprintf(stderr, "%d, %d\n", currentchunkx, currentchunky);
    cb->buildChunk(currentchunkx, currentchunky);
    currentchunky++;
    if (currentchunky >= chunky){
      currentchunky = 0;
      currentchunkx++;
    }

  }

}

void run_game(){
    builder();

    Device::ClearBackBuffer(Color(13,195,219));
    Device::ClearDepthBuffer();
    Device::ClearStencilBuffer();

    Input::Update(5);

    RenderStates::EnableZWrites = false;
	RenderStates::ClipNear = 10;
    skybox->render();
	RenderStates::EnableZWrites = true;
	RenderStates::ClipNear = 0.5f;

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
