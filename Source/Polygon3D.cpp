#include "Polygon3D.h"


Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;
	_avgZ = 0.0f;
	_color = RGB(0, 0, 0);
	_toBeCulled = true;

}
Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_avgZ = 0.0f;
	_color = RGB(0, 0, 0);
	_toBeCulled = true;
}
Polygon3D::Polygon3D(int index0, int index1, int index2, int uvIndex0, int uvIndex1, int uvIndex2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_uvIndices[0] = uvIndex0;
	_uvIndices[1] = uvIndex1;
	_uvIndices[2] = uvIndex2;
	_avgZ = 0.0f;
	_color = RGB(0, 0, 0);
	_toBeCulled = true;
}

Polygon3D::~Polygon3D()
{

}
Polygon3D::Polygon3D(const Polygon3D& p)
{
	_indices[0] = p._indices[0];
	_indices[1] = p._indices[1];
	_indices[2] = p._indices[2];
	_uvIndices[0] = p._uvIndices[0];
	_uvIndices[1] = p._uvIndices[1];
	_uvIndices[2] = p._uvIndices[2];
	_toBeCulled = p._toBeCulled;
	_avgZ = p._avgZ;
	_color = p._color;
}
// Accessor to return index of specified vertex
bool Polygon3D::operator<(const Polygon3D& other) const
{
	return GetAvgZ() < other.GetAvgZ();
}
int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}
int Polygon3D::GetUVIndices(int index) const
{
	return _uvIndices[index];
}
void Polygon3D::SetUVIndices(int index0, int index1, int index2)
{
	_uvIndices[0] = index0;
	_uvIndices[1] = index1;
	_uvIndices[2] = index2;
}
COLORREF Polygon3D::GetColor()
{
	return _color;
}
void Polygon3D::SetColor(COLORREF color)
{
	_color = color;
}
bool Polygon3D::ToBeCulled()
{
	return _toBeCulled;
}
void Polygon3D::SetToBeCulled(bool val)
{
	_toBeCulled = val;
}
Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		_indices[0] = rhs._indices[0];
		_indices[1] = rhs._indices[1];
		_indices[2] = rhs._indices[2];
		_toBeCulled = rhs._toBeCulled;
		_avgZ = rhs._avgZ;
		_color = rhs._color;
	}
	return *this;
}
Vector3D Polygon3D::GetNormalVector()
{
	return _normalVector;
}
void Polygon3D::SetNormalVector(Vector3D normal)
{
	_normalVector = normal;
}
bool Polygon3D::operator==(const Polygon3D& other)
{
	if (_avgZ != other.GetAvgZ())
	{
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
		if (_indices[i] != other._indices[i])
		{
			return false;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (_uvIndices[i] != other._uvIndices[i])
		{
			return false;
		}
	}
	return true;

}
float Polygon3D::GetAvgZ() const
{
	return _avgZ;
}

void Polygon3D::SetAvgZ(float avg)
{
	_avgZ = avg;
}

