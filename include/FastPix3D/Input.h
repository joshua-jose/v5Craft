#include "main.h"
#include <map>

class  Input
{
private:
	static int32 JoyX[2];
	static int32 JoyY[2];
	static int32 JoyXSpeed[2];
	static int32 JoyYSpeed[2];
	
	static void Initialize();
	static void Destroy();
public:
	static void Clear();
	static void Update(int32 dt);

	static int32 getJoyX(int32 joy);
	static int32 getJoyY(int32 joy);
	static int32 getJoyXSpeed(int32 joy);
	static int32 getJoyYSpeed(int32 joy);

	static bool getKeyDown(pros::controller_digital_e_t key);

	static void setJoyPosition(int32 x, int32 y, int32 joy, bool updateMouseSpeed);

	friend class Device;
};
