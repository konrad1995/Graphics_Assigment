#pragma once
#include "Vector3D.h"
class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(int red, int green, int blue);
	AmbientLight(const AmbientLight& other);
	AmbientLight& operator=(const AmbientLight& rhs);
	int GetRed();
	int GetGreen();
	int GetBlue();
	void SetRed(int red);
	void SetGreen(int green);
	void SetBlue(int blue);

private:
	int _red;
	int _green;
	int _blue;

};

