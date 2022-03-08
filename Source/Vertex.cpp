#include "Vertex.h"

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1.0f;
	_n = 0;
	_r = 0;
	_g = 0;
	_b = 0;
	_u = 0;
	_v = 0;
	_color = RGB(0, 0, 0);
	_normalVector = Vector3D(0,0,0);
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1.0f;
	_n = 0;
	_r = 0;
	_g = 0;
	_b = 0;
	_u = 0;
	_v = 0;
	_color = RGB(0, 0, 0);
	_normalVector = Vector3D(0, 0, 0);
}

Vertex::Vertex(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
	_n = 0;
	_r = 0;
	_g = 0;
	_b = 0;
	_u = 0;
	_v = 0;
	_color = RGB(0, 0, 0);
	_normalVector = Vector3D(0, 0, 0);
}

Vertex::Vertex(const Vertex& other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;
	_w = other._w;
	_n = other._n;
	_r = other._r;
	_g = other._g;
	_b = other._b;
	_u = other._u;
	_v = other._v;
	_color = other._color;
	_normalVector = other._normalVector;
}

float Vertex::GetX()
{
	return _x;
}
float Vertex::GetY()
{
	return _y;
}
float Vertex::GetZ()
{
	return _z;
}

float Vertex::GetW()
{
	return _w;
}

float Vertex::GetU()
{
	return _u;
}

float Vertex::GetV()
{
	return _v;
}

int Vertex::GetR()
{
	return _r;
}

int Vertex::GetG()
{
	return _g;
}

int Vertex::GetB()
{
	return _b;
}

COLORREF Vertex::GetColor()
{
	return _color;
}

Vector3D Vertex::GetNormalVector()
{
	return _normalVector;
}

void Vertex::SetNormalVector(Vector3D vector)
{
	_normalVector = vector;
}

void Vertex::SetColor(COLORREF color)
{
	_r = GetRValue(color);
	_g = GetGValue(color);
	_b = GetBValue(color);
	_color = color;
}

void Vertex::SetColor(int r, int g, int b)
{
	_r = r;
	_g = g;
	_b = b;
	_color = RGB(r, g, b);
}

void Vertex::SetX(float x)
{
	_x = x;
}

void Vertex::SetY(float y)
{
	_y = y;
}

void Vertex::SetZ(float z)
{
	_z = z;
}

void Vertex::SetW(float w)
{
	_w = w;
}
void Vertex::SetU(float u)
{
	_u = u;
}
void Vertex::SetV(float v)
{
	_v = v;
}
int Vertex::GetCount()
{
	return _n;
}
void Vertex::ResetCount()
{
	_n = 0;
}
void Vertex:: AddToCounter()
{
	_n += 1;
}

void Vertex::DehomogenizeVertex()
{
	_x = _x / _w;
	_y = _y / _w;
	_z = _z / _w;
	_w = _w / _w;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs._x;
		_y = rhs._y;
		_z = rhs._z;
		_w = rhs._w;
		_r = rhs._r;
		_g = rhs._g;
		_b = rhs._b;
		_n = rhs._n;
		_u = rhs._u;
		_v = rhs._v;
		_color = rhs._color;
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	if (_x != rhs._x || _y != rhs._y || _z != rhs._z || _w != rhs._w)
	{
		return false;
	}
	return true;
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs._x, _y + rhs._y, _z + rhs._z, _w + rhs._w);
}
const Vertex Vertex::operator+=(const Vertex& rhs) const
{
	return Vertex(_x + rhs._x, _y + rhs._y, _z + rhs._z, _w + rhs._w);
}
const Vector3D Vertex::operator-(const Vertex& rhs) const
{
	return Vector3D(_x - rhs._x, _y - rhs._y, _z - rhs._z);
}