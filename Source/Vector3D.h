#pragma once
#include <math.h>


class Vector3D
{

public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& other);

	// Accessors

	float GetX();
	float GetY();
	float GetZ();
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);

	// Assignment operator
	Vector3D& operator=(const Vector3D& rhs);
	bool operator==(const Vector3D& rhs) const;
	const Vector3D operator-(const Vector3D& rhs) const;
	const Vector3D operator+(const Vector3D& rhs) const;
	const Vector3D operator*(const Vector3D& rhs) const;
	float VectorLength();
	void NormalizeVector();

	//Static Methods
	static float DotProduct(Vector3D vect1, Vector3D vect2);
	static Vector3D CrossProduct(Vector3D vect1, Vector3D vect2);

private:
	float _x;
	float _y;
	float _z;
};

