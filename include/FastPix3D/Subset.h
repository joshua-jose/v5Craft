class Subset
{
private:
	int32 VertexCount, TriangleCount;



public:
	Subset(int32 vertexCount, int32 triangleCount);
	~Subset();
  Vertex *Vertices;
	int32 getVertexCount();
	int32 getTriangleCount();
	Vertex* getVertexBuffer();
	Triangle* getTriangleBuffer();
	Texture* getTexture();
	Triangle *Triangles;
	Texture *AppliedTexture;

	friend class Mesh;
};
