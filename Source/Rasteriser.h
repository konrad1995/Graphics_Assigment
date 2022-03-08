#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Model.h"
#include <vector>
#include "Camera.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Render(const Bitmap& bitmap);
	void DrawString(const Bitmap& bitmap, LPCTSTR text);
	void DrawPolygonGDI(const Bitmap& bitmap);
	void Presentation(const Bitmap& bitmap);
	void Update(const Bitmap& bitmap);
	void DrawWireFrame(const Bitmap& bitmap);
	void FillSolidTextured(const Bitmap& bitmap);
	void DrawSolidFlatGouraud(const Bitmap& bitmap);
	void DrawSolidFlat(const Bitmap& bitmap);

	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);
	
	void fillTopFlatTriangleGouraud(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3);
	void fillBottomFlatTriangleGouraud(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3);
	void fillBottomFlatTriangle(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3, COLORREF color);
	void fillTopFlatTriangle(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3, COLORREF color);

	void DrawBresenhamLine(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color);

private:
	float _d;
	int counter = 0;
	COLORREF _backgroundC = RGB(0,0,0);
	Model _model;
	Camera _camera;
	Matrix _worldMatrix, _screenMatrix, _perspMatrix, _translationMatrix;
	DirLight _directionalLight;
	AmbientLight _ambLight;
	PointLight _lightPoint;
	vector<DirLight> _dirLights;
	vector<PointLight> _lightPoints;

};