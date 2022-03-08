#pragma once
#include "Polygon3D.h"
#include "Vertex.h"
#include <vector>
#include "Matrix.h"
#include "Camera.h"
#include <algorithm>
#include "DirLight.h"
#include "AmbientLight.h"
#include <iostream>
#include "PointLight.h"
#include "UVCoords.h"
#include "Texture.h"

class Model
{
public:
	Model();
	~Model();
	// Accessors
	std::vector<Polygon3D>& GetPolygons();
	Polygon3D GetPolygon(int index);
	std::vector<Vertex>& GetVertices();
	std::vector<Vertex>& GetTransVertices();
	std::vector<UVCoords>& GetUVCoords();
	Texture& GetTexture();
	void DrawSolidTextured();
	Vertex GetTransVert(int index);
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void CalculateAvgZ();
	void ApplyTransformToLocalVertices(const Matrix& transform);
	void ApplyTransformToTransformedVertices(const Matrix& transform);
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2, int uv0, int uv1, int uv2);
	void AddTextureUV(float u, float v);
	void dehomogenizeVertecies();
	void CalculateBackfaces(Camera cam);
	static int ClampNumber(int number, int min, int max);
	void GenerateNormalVectorForVertex();
	void CalculatePointLight(vector<PointLight> light);
	void CalculatePointLightForPolygons(vector<PointLight> lights);
	void CalculateAmbientLight(AmbientLight light);
	void CalculateLightingDirectional(vector<DirLight> lights);
	void Sort();
	static bool sortByZAvg(const Polygon3D& lhs, const Polygon3D& rhs);

private:
	float _kdRed;
	float _kdGreen;
	float _kdBlue;
	float _kaRed;
	float _kaGreen;
	float _kaBlue;
	float _a;
	float _b;
	float _c;
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transformedVertices;
	std::vector<UVCoords> _uvcoords;
	Texture _texture;
};

