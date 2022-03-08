#include "UVCoords.h"

UVCoords::UVCoords()
{
	_u = 0;
	_v = 0;
}

UVCoords::UVCoords(float u, float v)
{
	_u = u;
	_v = v;
}

float UVCoords::GetU()
{
	return _u;
}

float UVCoords::GetV()
{
	return _v;
}

void UVCoords::SetU(float u)
{
	_u = u;
}

void UVCoords::SetV(float v)
{
	_u = v;
}
