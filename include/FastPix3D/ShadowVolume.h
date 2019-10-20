struct ShadowVolume{
	ShadowVolume(Mesh *mesh);
	int32 Draw(Light *light, Matrix modelSpace, float length);

private:
	int TriangleCount;
	ShadowTriangle *Triangles;

};
