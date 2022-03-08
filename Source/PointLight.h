#pragma once
#include "Vertex.h"

class PointLight
{
public:
	PointLight();
	PointLight(int red, int green, int blue, Vertex position);
	PointLight(const PointLight& other);
	PointLight& operator=(const PointLight& rhs);
	int GetRed();
	int GetGreen();
	int GetBlue();
	void SetRed(int red);
	void SetGreen(int green);
	void SetBlue(int blue);
	Vertex GetPosition();
	void SetPosition(Vertex vector);
	
private:
	int _red;
	int _green;
	int _blue;
	Vertex _position;
};

