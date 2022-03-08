#include "Camera.h"
#include "Vertex.h"

#include "Matrix.h"

Camera::Camera()
{
	_xRot = 0.0f;
	_yRot = 0.0f;
	_zRot = 0.0f;
	_cameraCord = Vertex(0.0f, 0.0f, -50.0f);
	GenerateCameraMatrix();
}
Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRot = xRotation;
	_yRot = yRotation;
	_zRot = zRotation;
	_cameraCord = position;
	GenerateCameraMatrix();
}

const Vertex Camera::GetCameraCoords()
{
	return _cameraCord;
}

Matrix Camera::GetCameraMatrix()
{
	return _cameraMatrix;
}

void Camera::GenerateCameraMatrix()
{
	float transMatrix[16] = { 1.0f, 0.0f,0.0f, -_cameraCord.GetX(),
							0.0f, 1.0f, 0.0f, -_cameraCord.GetY(),
							0.0f, 0.0f, 1.0f, -_cameraCord.GetZ(),
							0.0f, 0.0f, 0.0f, 1.0f };
	_cameraMatrix = _cameraMatrix.RotationXMatrix(_xRot) * _cameraMatrix.RotationYMatrix(_yRot) * _cameraMatrix.RotationZMatrix(_zRot) * Matrix(transMatrix);
}
