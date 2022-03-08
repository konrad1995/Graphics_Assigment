#include "Vector3D.h"
#include "Framework.h"
#pragma once

const int vertexSize = 4;

class Vertex
{

public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float w);
	Vertex(const Vertex& other);
	// Accessors

	float GetX();
	float GetY();
	float GetZ();
	float GetW();
	float GetU();
	float GetV();
	int GetR();
	int GetG();
	int GetB();
	COLORREF GetColor();
	Vector3D GetNormalVector();
	void SetNormalVector(Vector3D vector);
	void SetColor(COLORREF color);
	void SetColor(int r, int g, int b);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetW(float w);
	void SetU(float u);
	void SetV(float v);
	int GetCount();

	void ResetCount();
	void AddToCounter();
	void  DehomogenizeVertex();

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;
	const Vertex operator+ (const Vertex& rhs) const;
	const Vertex operator+=(const Vertex& rhs) const;
	const Vector3D operator- (const Vertex& rhs) const;

private:
	int _n;
	float _x;
	float _y;
	float _z;
	float _w;
	int _r;
	int _g;
	int _b;
	float _u;
	float _v;
	COLORREF _color;
	Vector3D _normalVector;

};

