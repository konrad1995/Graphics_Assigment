#pragma once
#include <stdbool.h>
#include <cmath>
#include "Framework.h"
#include "Vector3D.h"

class Polygon3D
{
public:

	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	Polygon3D(int index0, int index1, int index2, int uvIndex0, int uvIndex1, int uvIndex2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	// Accessor to return index of specified vertex
	bool ToBeCulled();
	int GetIndex(int index) const;
	int GetUVIndices(int index) const;
	float GetAvgZ() const;
	void SetUVIndices(int index0, int index1, int index2);
	void SetColor(COLORREF color);
	void SetAvgZ(float avg);
	void SetToBeCulled(bool val);
	
	void SetNormalVector(Vector3D normal);
	Vector3D GetNormalVector();
	COLORREF GetColor();

	bool operator<(const Polygon3D& other) const;
	bool operator==(const Polygon3D& other);
	Polygon3D& operator=(const Polygon3D& rhs);
	
private:
	int _indices[3];
	int _uvIndices[3];
	float _avgZ;
	bool _toBeCulled;
	Vector3D _normalVector;
	COLORREF _color;
};

