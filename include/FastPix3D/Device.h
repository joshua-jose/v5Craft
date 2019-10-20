#include "api.h"

class  Device
{
private:
	static int32 Width;
	static int32 Height;
	static int32 *BackBuffer;
	static int16 *DepthBuffer;
	static sbyte *StencilBuffer;
public:
	static void Initialize(int32 width, int32 height);
	static void Destroy();

	static void ClearBackBuffer();
	static void ClearBackBuffer(Color color);
	static void ClearStencilBuffer();
	static void ClearDepthBuffer();
	static void Present();

	static string getTitle();
	static int32 getWidth();
	static int32 getHeight();

	static void setTitle(string title);


	friend class Input;
	friend class Graphics;
	friend class Drawer;
};
