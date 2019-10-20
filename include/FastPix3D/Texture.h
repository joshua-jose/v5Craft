class Texture
{
private:
	string FileName;

	int32 *Buffer;

	static int32 GetLogarithmicCeiling(int32 number);
	static int32 GetExponent(int32 number);
public:
	Texture(string path);
	Texture(int width, int height);
	~Texture();
	int32 Width, Height, WidthExponent;

	int32 getWidth();
	int32 getHeight();
	int32* getBuffer();
	string getFileName();

	friend class Drawer;
};
