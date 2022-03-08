#include "Vector3D.h"
#include "Vertex.h"

Vector3D::Vector3D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	_x = other._x;
	_y = other._y;
	_z = other._z;
}

float Vector3D::GetX()
{
	return _x;
}

float Vector3D::GetY()
{
	return _y;
}

float Vector3D::GetZ()
{
	return _z;
}

void Vector3D::SetX(float x)
{
	_x = x;
}

void Vector3D::SetY(float y)
{
	_y = y;
}

void Vector3D::SetZ(float z)
{
	_z = z;
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	if (this != &rhs)
	{
		_x = rhs._x;
		_y = rhs._y;
		_z = rhs._z;
	}
	return *this;
}

bool Vector3D::operator==(const Vector3D& rhs) const
{
	if (_x != rhs._x || _y != rhs._y || _z != rhs._z)
	{
		return false;
	}
	return true;
}

const Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D(_x - rhs._x, _y - rhs._y, _z - rhs._z);
}

const Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(_x + rhs._x, _y + rhs._y, _z + rhs._z);
}


const Vector3D Vector3D::operator*(const Vector3D& rhs) const
{
	return Vector3D(_x * rhs._x, _y * rhs._y, _z * rhs._z);
}
float Vector3D::VectorLength()
{
	return sqrtf((_x * _x) + (_y * _y) + (_z * _z));
}
void Vector3D::NormalizeVector()
{
	float magnitude = VectorLength();
	_x /= magnitude;
	_y /= magnitude;
	_z /= magnitude;
}

float Vector3D::DotProduct(Vector3D vect1, Vector3D vect2)
{
	return((vect1.GetX() * vect2.GetX()) + (vect1.GetY() * vect2.GetY()) + (vect1.GetZ() * vect2.GetZ()));
}

Vector3D Vector3D::CrossProduct(Vector3D vect1, Vector3D vect2)
{
	Vector3D crossProduct = Vector3D
	(
		(vect1.GetY() * vect2.GetZ() - vect1.GetZ() * vect2.GetY()),
		(vect1.GetZ() * vect2.GetX() - vect1.GetX() * vect2.GetZ()),
		(vect1.GetX() * vect2.GetY() - vect1.GetY() * vect2.GetX())
	);
	return crossProduct;
}
