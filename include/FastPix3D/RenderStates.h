class  RenderStates
{
private:
	static void Initialize();
	static void Destroy();
public:
	static const int32 MaximumLightCount;

	static bool EnableZWrites;
	static bool EnableStencilMask;
	static bool EnableLights;
	static CullMode cullMode;
	static float ClipNear;
	static float Zoom;
	static Matrix CameraSpace;
	static Texture *CurrentTexture;
	static Light **Lights;

	static void Reset();

	friend class Device;
};