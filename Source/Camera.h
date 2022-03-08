#pragma once
#include "Vertex.h"
#include "Matrix.h"
class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	const Vertex GetCameraCoords();
	Matrix GetCameraMatrix();
	void GenerateCameraMatrix();
private:
	Matrix _cameraMatrix;
	Vertex _cameraCord;
	float _xRot;
	float _yRot;
	float _zRot;
};

