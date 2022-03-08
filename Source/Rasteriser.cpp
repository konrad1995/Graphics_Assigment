#include "Rasteriser.h"
#include <vector>
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include <algorithm>
#include <gdiplus.h>


Rasteriser app;
bool Rasteriser::Initialise()
{

	if(!MD2Loader::LoadModel("3DModels/cube.md2", "lines.pcx", _model, &Model::AddPolygon, &Model::AddVertex, &Model::AddTextureUV))
	{
		return false;
	}
	_d = 1;
	_camera = Camera(0, 0, 0, Vertex(0, 0, -50));
	_backgroundC = RGB(100, 100, 100);
	_worldMatrix = Matrix::ScaleMatrix(1.0f) * Matrix::RotationXMatrix(0);
	_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
	_dirLights.push_back(_directionalLight);
	_ambLight = AmbientLight(0, 255, 0);
	_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
	_lightPoints.push_back(_lightPoint);
	return true;
}

void Rasteriser::Render(const Bitmap& bitmap)
{	

	bitmap.Clear(_backgroundC);

	if (counter >= 0 && counter < 100)
	{
		_model.ApplyTransformToLocalVertices(_worldMatrix);;
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Displayed Model");

	}
	else if (counter >= 100 && counter < 150)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(1.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);;
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Positive Y Rotation ");

	}
	else if (counter >= 150 && counter < 200)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-1.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);;
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Negative Y Rotation");
	}
	else if (counter >= 200 && counter < 250)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationZMatrix(1.0f);
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Positive Z Rotation");
	}
	else if (counter >= 250 && counter < 300)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationZMatrix(-1.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Negative Z Rotation");
	}
	else if (counter >= 300 && counter < 350)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationXMatrix(1.0f);
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Positive X Rotation");
	}
	else if (counter >= 350 && counter < 400)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationXMatrix(-1.0f);
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Negative X Rotation");
	}
	else if (counter >= 400 && counter < 450)
	{
		_worldMatrix = _worldMatrix * Matrix::ScaleMatrix(0.99f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Scaling Down");
	}
	else if (counter >= 450 && counter < 500)
	{
		_worldMatrix = _worldMatrix * Matrix::ScaleMatrix(1.01f);
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Scaling Up");		
	}
	else if (counter >= 500 && counter < 550)
	{
		_worldMatrix = _worldMatrix * Matrix::GenerateTranslationMatrix(Vertex(0, 0, 2));

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Translating Negative On Z Axis");
	}
	else if (counter >= 550 && counter < 600)
	{
		_worldMatrix = _worldMatrix * Matrix::GenerateTranslationMatrix(Vertex(0, 0, -2));
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Translating Positive On Z Axis");
	}
	else if (counter >= 600 && counter < 650)
	{
		_worldMatrix = _worldMatrix * Matrix::GenerateTranslationMatrix(Vertex(0, -2, 0));

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Translating Negative On Y Axis");
	}
	else if (counter >= 650 && counter < 700)
	{
		_worldMatrix = _worldMatrix * Matrix::GenerateTranslationMatrix(Vertex(0, 2, 0));
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Translating Positive On Y Axis");
	}
	else if (counter >= 700 && counter < 750)
	{
		_worldMatrix = _worldMatrix * Matrix::GenerateTranslationMatrix(Vertex(-2, 0, 0));

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Translating Negative On X Axis");
	}
	else if (counter >= 750 && counter < 800)
	{
		_worldMatrix = _worldMatrix * Matrix::GenerateTranslationMatrix(Vertex(2, 0, 0));
		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Translating Positive On X Axis");
	}
	else if (counter >= 800 && counter < 850)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Back Face Culling");
	}
	else if (counter >= 850 && counter < 900)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Back Face Culling");
	}
	else if (counter >= 900 && counter < 950)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Back Face Culling with Sorting");
	}
	else if (counter >= 950 && counter < 1000)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawWireFrame(bitmap);
		DrawString(bitmap, L"Back Face Culling with Sorting");
	}
	else if (counter >= 1000 && counter < 1050)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawPolygonGDI(bitmap);
		DrawString(bitmap, L"Draw Polygon with GDI");
	}
	else if (counter >= 1050 && counter < 1100)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawPolygonGDI(bitmap);
		DrawString(bitmap, L"Draw Polygon with GDI");
	}
	else if (counter >= 1100 && counter < 1150)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Draw Polygon with Standard Model");
	}
	else if (counter >= 1150 && counter < 1200)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Draw Polygon with Standard Model");
	}
	else if (counter >= 1200 && counter < 1250)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_ambLight = AmbientLight(0, 255, 0);
		_model.CalculateAmbientLight(_ambLight);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Ambient Light");
	}
	else if (counter >= 1250 && counter < 1300)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_ambLight = AmbientLight(0, 255, 0);
		_model.CalculateAmbientLight(_ambLight);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Ambient Light");
	}
	else if (counter >= 1300 && counter < 1350)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 0, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Directional Light");
	}
	else if (counter >= 1350 && counter < 1400)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 0, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Directional Light");
	}
	else if (counter >= 1400 && counter < 1450)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 0, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(0, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
		_lightPoints.clear();
		_lightPoints.push_back(_lightPoint);
		_model.CalculatePointLightForPolygons(_lightPoints);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Point Light");
	}
	else if (counter >= 1450 && counter < 1500)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 0, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(0, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
		_lightPoints.clear();
		_lightPoints.push_back(_lightPoint);
		_model.CalculatePointLightForPolygons(_lightPoints);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Point Light");
	}
	else if (counter >= 1500 && counter < 1550)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 255, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
		_lightPoints.clear();
		_lightPoints.push_back(_lightPoint);
		_model.CalculatePointLightForPolygons(_lightPoints);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Ambient + Directional + Point Light");
	}
	else if (counter >= 1550 && counter < 1600)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 255, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
		_lightPoints.clear();
		_lightPoints.push_back(_lightPoint);
		_model.CalculatePointLightForPolygons(_lightPoints);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Ambient + Directional + Point Light");
	}
	else if (counter >= 1600 && counter < 1650)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 255, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
		_lightPoints.clear();
		_lightPoints.push_back(_lightPoint);
		_model.CalculatePointLightForPolygons(_lightPoints);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlatGouraud(bitmap);
		DrawString(bitmap, L"Gouraud Shading");
	}
	else if (counter >= 1650 && counter < 1700)
	{
		_worldMatrix = _worldMatrix * Matrix::RotationYMatrix(-3.0f);

		_model.ApplyTransformToLocalVertices(_worldMatrix);
		_model.CalculateBackfaces(_camera);
		_model.GenerateNormalVectorForVertex();
		_ambLight = AmbientLight(0, 255, 0);
		_model.CalculateAmbientLight(_ambLight);
		_directionalLight = DirLight(255, 0, 0, Vector3D(0.0f, 0.0f, -50.0f));
		_dirLights.clear();
		_dirLights.push_back(_directionalLight);
		_model.CalculateLightingDirectional(_dirLights);
		_lightPoint = PointLight(0, 0, 255, Vertex(0.0f, 0.0f, -50.0f));
		_lightPoints.clear();
		_lightPoints.push_back(_lightPoint);
		_model.CalculatePointLightForPolygons(_lightPoints);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspMatrix);
		_model.dehomogenizeVertecies();
		_model.ApplyTransformToTransformedVertices(_screenMatrix);
		DrawSolidFlatGouraud(bitmap);
		DrawString(bitmap, L"Gouraud Shading");
	}
	else
	{
	counter = 0;
 }
}
void Rasteriser::DrawString(const Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}

void Rasteriser::DrawPolygonGDI(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();

	for (Polygon3D poly : _model.GetPolygons())
	{
		if (poly.ToBeCulled())
		{
			POINT pointArr[3];
			pointArr[0] = { (int)_model.GetTransVertices().at(poly.GetIndex(0)).GetX(), (int)_model.GetTransVertices().at(poly.GetIndex(0)).GetY() };
			pointArr[1] = { (int)_model.GetTransVertices().at(poly.GetIndex(1)).GetX(), (int)_model.GetTransVertices().at(poly.GetIndex(1)).GetY() };
			pointArr[2] = { (int)_model.GetTransVertices().at(poly.GetIndex(2)).GetX(), (int)_model.GetTransVertices().at(poly.GetIndex(2)).GetY() };
			COLORREF color = RGB(255,255,255);
			POINT *pointerToArr;
			pointerToArr = pointArr;
			Polygon(hdc, pointerToArr, 3);
		}

	}
}
void Rasteriser::Presentation(const Bitmap& bitmap)
{
}
void Rasteriser::Update(const Bitmap& bitmap)
{
	counter+= 1;
	GeneratePerspectiveMatrix(_d, (float(bitmap.GetWidth()) / float(bitmap.GetHeight())));
	GenerateViewMatrix(_d, bitmap.GetWidth(), bitmap.GetHeight());
}
void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	HPEN hLinePen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	HPEN hPenOld = (HPEN)SelectObject(hdc, hLinePen);
	vector<Polygon3D> polygons = _model.GetPolygons();
	for (Polygon3D& poly : polygons)
	{
		if (poly.ToBeCulled())
		{
			DrawBresenhamLine(hdc, int(_model.GetTransVert(poly.GetIndex(2)).GetX()), int(_model.GetTransVert(poly.GetIndex(2)).GetY()), int(_model.GetTransVert(poly.GetIndex(0)).GetX()), int(_model.GetTransVert(poly.GetIndex(0)).GetY()), poly.GetColor());
			DrawBresenhamLine(hdc, int(_model.GetTransVert(poly.GetIndex(0)).GetX()), int(_model.GetTransVert(poly.GetIndex(0)).GetY()), int(_model.GetTransVert(poly.GetIndex(1)).GetX()), int(_model.GetTransVert(poly.GetIndex(1)).GetY()), poly.GetColor());
			DrawBresenhamLine(hdc, int(_model.GetTransVert(poly.GetIndex(1)).GetX()), int(_model.GetTransVert(poly.GetIndex(1)).GetY()), int(_model.GetTransVert(poly.GetIndex(2)).GetX()), int(_model.GetTransVert(poly.GetIndex(2)).GetY()), poly.GetColor());
		}
	}
}
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	float tempArr[16] = { (d / aspectRatio), 0.0f, 0.0f, 0.0f,
						0.0f, d, 0.0f, 0.0f,
						0.0f, 0.0f, d, 0.0f,
						0.0f, 0.0f, d, 0.0f };
	_perspMatrix = Matrix(tempArr);
}
void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	float tempArr[16] =
	{
		width / 2.0f, 0.0f, 0.0f, width / 2.0f,
		0.0f, -height / 2.0f, 0.0f, height / 2.0f,
		0.0f, 0.0f, d / 2, d / 2,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	_screenMatrix = Matrix(tempArr);
};
void Rasteriser::DrawSolidFlatGouraud(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	for (Polygon3D& poly : _model.GetPolygons())
	{

		if (poly.ToBeCulled())
		{
			Vertex vertex1 = _model.GetTransVert(poly.GetIndex(0));
			Vertex vertex2 = _model.GetTransVert(poly.GetIndex(1));
			Vertex vertex3 = _model.GetTransVert(poly.GetIndex(2));
			COLORREF color = poly.GetColor();
			if (vertex1.GetY() > vertex2.GetY())
			{
				std::swap(vertex1, vertex2);
			}
			if (vertex2.GetY() > vertex3.GetY())
			{
				std::swap(vertex2, vertex3);
			}
			if (vertex1.GetY() > vertex2.GetY())
			{
				std::swap(vertex1, vertex2);
			}

			if (vertex2.GetY() == vertex3.GetY())
			{
				if (vertex2.GetX() < vertex3.GetX())
				{
					fillBottomFlatTriangleGouraud(hdc, vertex1, vertex2, vertex3);
				}
				else
				{
					fillBottomFlatTriangleGouraud(hdc, vertex1, vertex3, vertex2);
				}
			}
			else if (vertex1.GetY() == vertex2.GetY())
			{
				if (vertex1.GetX() < vertex2.GetX())
				{
					fillTopFlatTriangleGouraud(hdc, vertex1, vertex2, vertex3);
				}
				else
				{
					fillTopFlatTriangleGouraud(hdc, vertex2, vertex1, vertex3);
				}
			}
			else
			{
				Vertex vertex4 = Vertex((vertex1.GetX() + ((vertex2.GetY() - vertex1.GetY()) / (vertex3.GetY() - vertex1.GetY())) * (vertex3.GetX() - vertex1.GetX())), vertex2.GetY(), 1);
				float r = 0;
				float g = 0;
				float b = 0;
				if (vertex3.GetR() == vertex1.GetR())
				{
					r = (float)vertex3.GetR();
				}
				else
				{
					r = (float)vertex1.GetR() + ((vertex2.GetY() - vertex1.GetY()) / ((vertex3.GetY() - vertex1.GetY()) * (float)(vertex3.GetR() - vertex1.GetR())));
				}
				if (vertex3.GetG() == vertex1.GetG())
				{
					g = (float)vertex3.GetG();
				}
				else
				{
					g = (float)vertex1.GetG() + ((vertex2.GetY() - vertex1.GetY()) / ((vertex3.GetY() - vertex1.GetY()) * (float)(vertex3.GetG() - vertex1.GetG())));
				}

				if (vertex3.GetB() == vertex1.GetB())
				{
					b = (float)vertex3.GetB();
				}
				else
				{
					b = (float)vertex1.GetB() + ((vertex2.GetY() - vertex1.GetY()) / ((vertex3.GetY() - vertex1.GetY()) * (float)(vertex1.GetB() - vertex1.GetB())));
				
				}
				vertex4.SetColor(RGB(int(r), int(g), int(b)));
				fillBottomFlatTriangleGouraud(hdc, vertex1, vertex2, vertex4);
				fillTopFlatTriangleGouraud(hdc, vertex2, vertex4, vertex3);
			}
		}
	}
}
void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();

	for (Polygon3D& poly : _model.GetPolygons())
	{
		if (poly.ToBeCulled())
		{
			Vertex vertex1 = _model.GetTransVert(poly.GetIndex(0));
			Vertex vertex2 = _model.GetTransVert(poly.GetIndex(1));
			Vertex vertex3 = _model.GetTransVert(poly.GetIndex(2));
			COLORREF color = poly.GetColor();
	


			if (vertex1.GetY() < vertex2.GetY())
			{
				std::swap(vertex1, vertex2);
			}
			if (vertex2.GetY() < vertex3.GetY())
			{
				std::swap(vertex2, vertex3);
			}
			if (vertex1.GetY() < vertex2.GetY())
			{
				std::swap(vertex1, vertex2);
			}

			if ((int)roundf(vertex2.GetY()) == (int)roundf(vertex3.GetY()))
			{
				if (vertex2.GetX() < vertex3.GetX())
				{
					fillTopFlatTriangle(hdc, vertex1, vertex2, vertex3, color);
			
				}
				else if (vertex2.GetX() > vertex3.GetX())
				{
					fillTopFlatTriangle(hdc, vertex1, vertex3, vertex2, color);
				}
			}
			else if ((int)roundf(vertex1.GetY()) == (int)roundf(vertex2.GetY()))
			{
				if (vertex1.GetX() < vertex2.GetX())
				{
					fillBottomFlatTriangle(hdc, vertex1, vertex2, vertex3, color);
				}
				else if (vertex1.GetX() > vertex2.GetX())
				{
					fillBottomFlatTriangle(hdc, vertex2, vertex1, vertex3, color);
				}
			}
			else
			{
				Vertex vertex4;
				float x = vertex1.GetX() + ((vertex2.GetY() - vertex1.GetY()) / (vertex3.GetY() - vertex1.GetY())) * (vertex3.GetX() - vertex1.GetX());
				vertex4.SetX(x);
				vertex4.SetY(vertex2.GetY());

				if (vertex2.GetX() > vertex4.GetX())
				{
					fillTopFlatTriangle(hdc, vertex1, vertex4, vertex2, color);
					fillBottomFlatTriangle(hdc, vertex4, vertex2, vertex3, color);

				}
				else if (vertex2.GetX() < vertex4.GetX())
				{
					fillTopFlatTriangle(hdc, vertex1, vertex2, vertex4, color);
					fillBottomFlatTriangle(hdc, vertex2, vertex4, vertex3, color);
				}
		
			}
		}
		
	}
	
}
void Rasteriser::fillTopFlatTriangle(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3, COLORREF color)
{
	float invslope1 = (vertex1.GetX() - vertex2.GetX()) / (vertex1.GetY() - vertex2.GetY());
	float invslope2 = (vertex1.GetX() - vertex3.GetX()) / (vertex1.GetY() - vertex3.GetY());
	float curx1 = vertex1.GetX();
	float curx2 = vertex1.GetX();
	for (int scanlineY = int(vertex1.GetY()); scanlineY > int(vertex3.GetY()); scanlineY--)
	{
		SetPixel(hdc, (int)curx1, scanlineY, color);
		for (int x = (int)curx1; x <= int(curx2); x++)
		{
			SetPixel(hdc, x, scanlineY, color);
		}
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
	for (int x = int(vertex2.GetX()); x <= int(vertex3.GetX()); x++)
	{
		SetPixel(hdc, x, int(vertex3.GetY()), color);
	}
}
void Rasteriser::fillBottomFlatTriangle(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3, COLORREF color)
{
	float invslope1 = (vertex1.GetX() - vertex3.GetX()) / (vertex1.GetY() - vertex3.GetY());
	float invslope2 = (vertex2.GetX() - vertex3.GetX()) / (vertex2.GetY() - vertex3.GetY());
	float curx1 = vertex3.GetX();
	float curx2 = vertex3.GetX();

	for (int scanlineY = int(vertex3.GetY()); scanlineY < int(vertex1.GetY()); scanlineY++)
	{
		SetPixel(hdc, (int)curx1, scanlineY, color);
		for (int x = (int)curx1; x <= int(curx2); x++)
		{
			SetPixel(hdc, x, scanlineY, color);
		}
		curx1 += invslope1;
		curx2 += invslope2;
	}
	for (int x = int(vertex1.GetX()); x <= int(vertex2.GetX()); x++)
	{
		SetPixel(hdc, x, int(vertex2.GetY()), color);
	}
}
void Rasteriser::fillTopFlatTriangleGouraud(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3)
{
	float invslope1 = (vertex3.GetX() - vertex1.GetX()) / (vertex3.GetY() - vertex1.GetY());
	float invslope2 = (vertex3.GetX() - vertex2.GetX()) / (vertex3.GetY() - vertex2.GetY());

	float curx1 = vertex3.GetX();
	float curx2 = vertex3.GetX() + 0.5f;


	float ver3Ver1diff = vertex3.GetY() - vertex1.GetY();
	float rLSlope = (float)(vertex3.GetR() - vertex1.GetR()) / ver3Ver1diff;
	float gLSlope = (float)(vertex3.GetG() - vertex1.GetG()) / ver3Ver1diff;
	float bLSlope = (float)(vertex3.GetB() - vertex1.GetB()) / ver3Ver1diff;

	float ver1Ver3diff = vertex3.GetY() - vertex2.GetY();
	float rRSlope = (float)(vertex3.GetR() - vertex2.GetR()) / ver1Ver3diff;
	float gRSlope = (float)(vertex3.GetG() - vertex2.GetG()) / ver1Ver3diff;
	float bRSlope = (float)(vertex3.GetB() - vertex2.GetB()) / ver1Ver3diff;

	float rVer1 = (float)vertex3.GetR();
	float gVer1 = (float)vertex3.GetG();
	float bVer1 = (float)vertex3.GetB();

	float rVer2 = (float)vertex3.GetR();
	float gVer2 = (float)vertex3.GetG();
	float bVer2 = (float)vertex3.GetB();

	if (invslope1 < invslope2)
	{
		swap(invslope1, invslope2);
		swap(rLSlope, rRSlope);
		swap(gLSlope, gRSlope);
		swap(bLSlope, bRSlope);
	}

	for (int scanlineY = int(vertex3.GetY()); scanlineY > int(vertex1.GetY()); scanlineY--)
	{

		for (int x = int(ceilf(curx1)); x < int(curx2); x++)
		{

			float fraction = (x - curx1) / (curx2 - curx1);
			int r = int((1.0f - fraction) * rVer1 + fraction * rVer2);
			int g = int((1.0f - fraction) * gVer1 + fraction * gVer2);
			int b = int((1.0f - fraction) * bVer1 + fraction * bVer2);
			SetPixel(hdc, x, scanlineY, RGB(r, g, b));
		}
		curx1 -= invslope1;
		curx2 -= invslope2;
		rVer1 -= rLSlope;
		gVer1 -= gLSlope;
		bVer1 -= bLSlope;
		rVer2 -= rRSlope;
		gVer2 -= gRSlope;
		bVer2 -= bRSlope;
	}	
}

void Rasteriser::fillBottomFlatTriangleGouraud(HDC hdc, Vertex vertex1, Vertex vertex2, Vertex vertex3)
{
	float invslope1 = (vertex2.GetX() - vertex1.GetX()) / (vertex2.GetY() - vertex1.GetY());
	float invslope2 = (vertex3.GetX() - vertex1.GetX()) / (vertex3.GetY() - vertex1.GetY());

	float curx1 = vertex1.GetX();
	float curx2 = vertex1.GetX() + 0.5f;

	float ver3Ver1diff = vertex2.GetY() - vertex1.GetY();
	float rLSlope = (float)(vertex2.GetR() - vertex1.GetR()) / ver3Ver1diff;
	float gLSlope = (float)(vertex2.GetG() - vertex1.GetG()) / ver3Ver1diff;
	float bLSlope = (float)(vertex2.GetB() - vertex1.GetB()) / ver3Ver1diff;


	float ver3Ver2diff = vertex3.GetY() - vertex1.GetY();
	float rRSlope = (float)(vertex3.GetR() - vertex1.GetR()) / ver3Ver2diff;
	float gRSlope = (float)(vertex3.GetG() - vertex1.GetG()) / ver3Ver2diff;
	float bRSlope = (float)(vertex3.GetB() - vertex1.GetB()) / ver3Ver2diff;

	float rVer1 = (float)vertex1.GetR();
	float gVer1 = (float)vertex1.GetG();
	float bVer1 = (float)vertex1.GetB();

	float rVer2 = (float)vertex1.GetR();
	float gVer2 = (float)vertex1.GetG();
	float bVer2 = (float)vertex1.GetB();

	if (invslope2 < invslope1)
	{
		swap(invslope1, invslope2);
		swap(rLSlope, rRSlope);
		swap(gLSlope, gRSlope);
		swap(bLSlope, bRSlope);
	}
	for (int scanlineY = int(vertex1.GetY()); scanlineY <= int(vertex2.GetY()); scanlineY++)
	{
		for (int x = (int)ceilf(curx1); x < int(curx2); x++)
		{
			float fraction = (x - curx1) / (curx2 - curx1);
			int r = int((1 - fraction) * rVer1 + fraction * rVer2);
			int g = int((1 - fraction) * gVer1 + fraction * gVer2);
			int b = int((1 - fraction) * bVer1 + fraction * bVer2);
			SetPixel(hdc, x, scanlineY, RGB(r, g, b));
		}
		curx1 += invslope1;
		curx2 += invslope2;
		rVer1 += rLSlope;
		gVer1 += gLSlope;
		bVer1 += bLSlope;
		rVer2 += rRSlope;
		gVer2 += gRSlope;
		bVer2 += bRSlope;
	}
}
void Rasteriser::DrawBresenhamLine(HDC hdc, int x0, int y0, int x1, int y1, COLORREF color)
{

	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	//calculating range for line between start and end point
	int dx = x1 - x0;
	int dy = y1 - y0;

	int x = x0;
	int y = y0;
	if (y0 < y1)
	{
		//this is the case when slope(m) < 1
		if (x0 == x1)
		{
			SetPixel(hdc, x, y, color);
			for (int i = y0; i < y1; i++)
			{
				y++;
				SetPixel(hdc, x, y, color);
			}
		}
		else if (abs(dx) > abs(dy))
		{
			SetPixel(hdc, x, y, color);    //this putpixel is for very first pixel of the line
			int pk = (2 * abs(dy)) - abs(dx);

			for (int i = 0; i < abs(dx); i++)
			{
				x = x + 1;
				if (pk < 0)
				{
					pk = pk + (2 * abs(dy));
				}
				else
				{
					y = y + 1;
					pk = pk + (2 * abs(dy)) - (2 * abs(dx));
				}
				SetPixel(hdc, x, y, color);

			}

		}
		else
		{
			//this is the case when slope is greater than or equal to 1  i.e: m>=1
			SetPixel(hdc, x, y, color);    //this putpixel is for very first pixel of the line
			int pk = (2 * abs(dx)) - abs(dy);

			for (int i = 0; i < abs(dy); i++)
			{
				y = y + 1;
				if (pk < 0)
				{
					pk = pk + (2 * abs(dx));
				}
				else
				{
					x = x + 1;
					pk = pk + (2 * abs(dx)) - (2 * abs(dy));
				}

				SetPixel(hdc, x, y, color);    // display pixel at coordinate (x, y)

			}
		}
	}
	else
	{
		if (y0 == y1)
		{
			SetPixel(hdc, x, y, color);
			for (int i = x0; i < x1; i++)
			{
				x++;
				SetPixel(hdc, x, y, color);
			}
		}
		else if (abs(dx) > abs(dy))
		{
			SetPixel(hdc, x, y, color);    //this putpixel is for very first pixel of the line
			int pk = (2 * dy) - dx;

			for (int i = 0; i < dx; i++)
			{
				x = x + 1;
				if (pk < 0)
				{
					pk = pk - (2 * dy);
				}
				else
				{
					y = y - 1;
					pk = pk - (2 * dy) - (2 * dx);
				}
				SetPixel(hdc, x, y, color);

			}

		}
		else
		{
			//this is the case when slope is greater than or equal to 1  i.e: m>=1
			SetPixel(hdc, x, y, color);    //this putpixel is for very first pixel of the line
			int pk = (2 * abs(dx)) - abs(dy);

			for (int i = 0; i > dy; i--)
			{
				y = y - 1;
				if (pk > 0)
					pk = pk - (2 * abs(dx));
				else
				{
					x = x + 1;
					pk = pk - (2 * abs(dx)) + (2 * abs(dy));
				}

				SetPixel(hdc, x, y, color);    // display pixel at coordinate (x, y)

			}
		}
	}
}

void Rasteriser::FillSolidTextured(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	for (Polygon3D& poly : _model.GetPolygons())
	{

		if (poly.ToBeCulled())
		{
			Vertex vertex1 = _model.GetTransVert(poly.GetIndex(0));
			Vertex vertex2 = _model.GetTransVert(poly.GetIndex(1));
			Vertex vertex3 = _model.GetTransVert(poly.GetIndex(2));
			COLORREF color = poly.GetColor();
			if (vertex1.GetY() > vertex2.GetY())
			{
				std::swap(vertex1, vertex2);
			}
			if (vertex2.GetY() > vertex3.GetY())
			{
				std::swap(vertex2, vertex3);
			}
			if (vertex1.GetY() > vertex2.GetY())
			{
				std::swap(vertex1, vertex2);
			}

			if (vertex2.GetY() == vertex3.GetY())
			{
				if (vertex2.GetX() < vertex3.GetX())
				{
					fillBottomFlatTriangleGouraud(hdc, vertex1, vertex2, vertex3);
				}
				else
				{
					fillBottomFlatTriangleGouraud(hdc, vertex1, vertex3, vertex2);
				}
			}
			else if (vertex1.GetY() == vertex2.GetY())
			{
				if (vertex1.GetX() < vertex2.GetX())
				{
					fillTopFlatTriangleGouraud(hdc, vertex1, vertex2, vertex3);
				}
				else
				{
					fillTopFlatTriangleGouraud(hdc, vertex2, vertex1, vertex3);
				}
			}
			else
			{
				Vertex vertex4 = Vertex((vertex1.GetX() + ((vertex2.GetY() - vertex1.GetY()) / (vertex3.GetY() - vertex1.GetY())) * (vertex3.GetX() - vertex1.GetX())), vertex2.GetY(), 1);
				float r = 0;
				float g = 0;
				float b = 0;
				if (vertex3.GetR() == vertex1.GetR())
				{
					r = (float)vertex3.GetR();
				}
				else
				{
					r = (float)vertex1.GetR() + ((vertex2.GetY() - vertex1.GetY()) / ((vertex3.GetY() - vertex1.GetY()) * (float)(vertex3.GetR() - vertex1.GetR())));
				}
				if (vertex3.GetG() == vertex1.GetG())
				{
					g = (float)vertex3.GetG();
				}
				else
				{
					g = (float)vertex1.GetG() + ((vertex2.GetY() - vertex1.GetY()) / ((vertex3.GetY() - vertex1.GetY()) * (float)(vertex3.GetG() - vertex1.GetG())));
				}

				if (vertex3.GetB() == vertex1.GetB())
				{
					b = (float)vertex3.GetB();
				}
				else
				{
					b = (float)vertex1.GetB() + ((vertex2.GetY() - vertex1.GetY()) / ((vertex3.GetY() - vertex1.GetY()) * (float)(vertex1.GetB() - vertex1.GetB())));

				}
				vertex4.SetColor(RGB(int(r), int(g), int(b)));
				fillBottomFlatTriangleGouraud(hdc, vertex1, vertex2, vertex4);
				fillTopFlatTriangleGouraud(hdc, vertex2, vertex4, vertex3);
			}
		}
	}
}
