#include "main.h"
#include "FastPix3D/FastPix3D.h"
#include <vector>

void initialize() {
    pros::delay(100);
    fprintf(stderr,"init\n");
}
void disabled() {}
void competition_initialize() {}
void autonomous() {}

void opcontrol() {
    fprintf(stderr,"start\n");
    pros::delay(10);
    Device::Initialize(LV_HOR_RES, LV_VER_RES);

    RenderStates::ClipNear = 1.0f;
    RenderStates::Zoom = 2;

    //FPSCounter* fpsCounter = new FPSCounter(20);
    FreelookManager *freelookManager = new FreelookManager();

    Font* font = new Font("/usd/Media/Fonts/16x16.png");

    RenderStates::CameraSpace = Matrix::RotateY(-30) * Matrix::RotateX(-20) * Matrix::Translate(Vector3f(0, 0, 20));
    int last_time = pros::millis();
    pros::delay(20);


    RenderStates::Lights[0]->Enabled = true;
  	RenderStates::Lights[0]->Type = LightType::Spot;
  	RenderStates::Lights[0]->Intensity = 40;
  	RenderStates::Lights[0]->DiffuseColor = Color(165, 210, 255);

    Light::AmbientColor = Color(200, 200, 200);

    /*
  	for (int32 x = -1, i = 1; x <= 1; x += 2)
  	{
  		for (int32 z = -1; z <= 1; z += 2, i++)
  		{
  			RenderStates::Lights[i]->Enabled = true;
  			RenderStates::Lights[i]->Type = LightType::Point;
  			RenderStates::Lights[i]->Intensity = 2;
  			RenderStates::Lights[i]->DiffuseColor = Color(127, 100, 75);
  			RenderStates::Lights[i]->Position = Vector3f(x * 8, -.5f, z * 8 - (z < 0 ? 1.f : 0.f));
  		}
  	}
    */

    Chunk chunk(Vector2f(0,0));
    chunk.fill(false);
    RenderStates::Lights[0]->Enabled = false;

    while (true) {
        float time = pros::millis() - last_time;
        last_time = pros::millis();

        Device::ClearBackBuffer(Color(53,81,92));
    		Device::ClearDepthBuffer();
    		Device::ClearStencilBuffer();

    		RenderStates::CameraSpace = freelookManager->Update();

    		RenderStates::EnableStencilMask = false;
    		RenderStates::cullMode = CullMode::Back;


    		chunk.render(RenderStates::Lights[0]);

        /*
    		RenderStates::Lights[0]->Enabled = false;
    		RenderStates::EnableStencilMask = true;
    		RenderStates::cullMode = CullMode::Back;
        */

    		//cube.mesh->Draw(cube.modelSpace);
    		//cube2.mesh->Draw(cube2.modelSpace);
        Device::Present();

        Input::Update(time);
        pros::delay(1);
    }

    Device::Destroy();
}
