#include "PointLight.h"


PointLight::PointLight()
{
	_red = 0;
	_green = 0;
	_blue = 0;
}

PointLight::PointLight(int red, int green, int blue, Vertex position)
{
	_red = red;
	_green = green;
	_blue = blue;
	_position = position;

}
PointLight::PointLight(const PointLight& other)
{
	_red = other._red;
	_green = other._green;
	_blue = other._blue;
	_position = other._position;
}
PointLight& PointLight::operator=(const PointLight& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_red = rhs._red;
		_green = rhs._green;
		_blue = rhs._blue;
		_position = rhs._position;
	}
	return *this;
}
int PointLight::GetRed()
{
	return _red;
}

int PointLight::GetGreen()
{
	return _green;
}

int PointLight::GetBlue()
{
	return _blue;
}

void PointLight::SetRed(int red)
{
	_red = red;
}

void PointLight::SetGreen(int green)
{
	_green = green;
}

void PointLight::SetBlue(int blue)
{
	_blue = blue;
}

Vertex PointLight::GetPosition()
{
	return _position;
}

void PointLight::SetPosition(Vertex postition)
{
	_position = postition;
}
