#pragma once
#include "Vector3D.h"
class DirLight
{
public:
	DirLight();
	DirLight(int red, int green, int blue, Vector3D lightSource);
	int GetRed();
	int GetGreen();
	int GetBlue();
	Vector3D GetVector();

	void SetRed(int red);
	void SetGreen(int green);
	void SetBlue(int blue);
	void SetVector(Vector3D lightSource);
private:
	int _red;
	int _green;
	int _blue;
	Vector3D _lightSource;
};

