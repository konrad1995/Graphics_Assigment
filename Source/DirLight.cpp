#include "DirLight.h"

DirLight::DirLight()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_lightSource = Vector3D(0.0f, 0.0f, 0.0f);
}

DirLight::DirLight(int red, int green, int blue, Vector3D lightSource)
{
	_red = red;
	_green = green;
	_blue = blue;
	_lightSource = lightSource;
}

int DirLight::GetRed()
{
	return _red;
}

int DirLight::GetGreen()
{
	return _green;
}

int DirLight::GetBlue()
{
	return _blue;
}

Vector3D DirLight::GetVector()
{
	return _lightSource;
}

void DirLight::SetRed(int red)
{
	_red = red;
}

void DirLight::SetGreen(int green)
{
	_green = green;
}

void DirLight::SetBlue(int blue)
{
	_blue = blue;
}

void DirLight::SetVector(Vector3D lightSource)
{
	_lightSource = lightSource;
}


