#pragma once
#include "Vertex.h"
#include <math.h>

const int ROWS = 4;
const int COLS = 4;

#include <initializer_list>

class Matrix
{
public:
	// Default constructor
	Matrix();
	// Constructor that initialises all elements.
	Matrix(float arrFl[]);
	// Constructor that initialises all elements.  Note that an initialiser list is used
	// to pass in the values.  This is a new C++ feature.
	Matrix(std::initializer_list<float> list);
	// Destructor
	~Matrix() noexcept;
	// Copy constructor
	Matrix(const Matrix& other) noexcept;
	// Retrieve value in matrix at specified row and column
	float GetM(const int row, const int column) const;
	// Set value in matrix at specified row and column
	void SetM(const int row, const int column, const float value);
	void Copy(const Matrix& other);
	static Matrix RotationZMatrix(float degrees);
	static Matrix RotationXMatrix(float degrees);
	static Matrix RotationYMatrix(float degrees);
	static Matrix GenerateTranslationMatrix(Vertex coords);
	static Matrix ScaleMatrix(float scaleValue);
	// Assignment operator
	Matrix& operator= (const Matrix& rhs);
	// Test for two matrices being equivalent;
	bool operator==(const Matrix& other) const;
	// Multiply two matrices together
	const Matrix operator*(const Matrix& other) const;
	// Multiply a matrix by a vertex, returning a vertex
	const Vertex operator*(Vertex& other) const;

private:
	float _m[ROWS][COLS];


};
