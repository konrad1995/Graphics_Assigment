#include "AmbientLight.h"


AmbientLight::AmbientLight()
{
	_red = 0;
	_green = 0;
	_blue = 0;
}

AmbientLight::AmbientLight(int red, int green, int blue)
{
	_red = red;
	_green = green;
	_blue = blue;

}
AmbientLight::AmbientLight(const AmbientLight& other)
{
	_red = other._red;
	_green = other._green;
	_blue = other._blue;
}
AmbientLight& AmbientLight::operator=(const AmbientLight& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_red = rhs._red;
		_green = rhs._green;
		_blue = rhs._blue;
	}
	return *this;
}
int AmbientLight::GetRed()
{
	return _red;
}

int AmbientLight::GetGreen()
{
	return _green;
}

int AmbientLight::GetBlue()
{
	return _blue;
}

void AmbientLight::SetRed(int red)
{
	_red = red;
}

void AmbientLight::SetGreen(int green)
{
	_green = green;
}

void AmbientLight::SetBlue(int blue)
{
	_blue = blue;
}



