#include "Matrix.h"
#include "Vertex.h"

Matrix::Matrix() : _m{ 0 }
{

};
// Constructor that initialises all elements.
Matrix::Matrix(float arrFl[])
{
	int k = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = arrFl[k];
			k++;
		}
	}
}
// Copy constructor
Matrix::Matrix(const Matrix& other) noexcept
{
	Copy(other);
}

Matrix::~Matrix() noexcept
{

}

Matrix::Matrix(std::initializer_list<float> list) : _m{ 0 }
{
	// Check that the initialiser list is the same size as the 
	// size of the array
	if (list.size() != ROWS * COLS)
	{
		// If not, throw an exception
		throw "Insufficient values supplied";
	}
	// Use iterator to work through the initialiser list, 
	// retrieving each value in turn.
	auto iterator = list.begin();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = *iterator++;
		}
	}
}
// Copy constructor
/*Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = other.GetM(i, j);
		}
	}
}*/
// Retrieve value in matrix at specified row and column
float Matrix::GetM(const int row, const int column) const
{
	return _m[row][column];
};
// Set value in matrix at specified row and column
void Matrix::SetM(const int row, const int column, const float value)
{
	_m[row][column] = value;
}

Matrix Matrix::ScaleMatrix(float scaleValue)
{
	float matrixScaleValues[16] = { scaleValue , 0.0f, 0.0f, 0.0f,
								0.0f, scaleValue, 0.0f, 0.0f,
								0.0f, 0.0f, scaleValue , 0.0f,
								0.0f, 0.0f, 0.0f, 1.0f };
	return Matrix(matrixScaleValues);
}
Matrix Matrix::RotationZMatrix(float degrees)
{

	float rad = degrees * 3.14f / 180.0f;
	float tempArr[16] = { cosf(rad), -sinf(rad), 0.0f, 0.0f,
								sinf(rad) , cosf(rad), 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 1.0f };
	return Matrix(tempArr);
}
Matrix Matrix::RotationXMatrix(float degrees)
{
	float rad = degrees * 3.14f / 180.0f;
	float tempArr[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, cosf(rad), -sinf(rad), 0.0f,
							0.0f, sinf(rad) , cosf(rad), 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f };
	return Matrix(tempArr);
}
Matrix Matrix::RotationYMatrix(float degrees)
{
	float rad = degrees * 3.14f / 180.0f;
	float tempArr[16] = { cosf(rad), 0.0f, sinf(rad), 0.0f,
							0.0f , 1.0f, 0.0f, 0.0f,
							-sinf(rad), 0.0f,  cosf(rad), 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f };
	return Matrix(tempArr);
}
Matrix Matrix::GenerateTranslationMatrix(Vertex coords)
{
	float tempArr[16] = { 1.0f, 0.0f, 0.0f, coords.GetX(),
						0.0f, 1.0f, 0.0f, coords.GetY(),
						0.0f, 0.0f, 1.0f, coords.GetZ(),
						0.0f, 0.0f, 0.0f,  1.0f };
	return Matrix(tempArr);
}
Matrix& Matrix::operator= (const Matrix& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
};
// Test for two matrices being equivalent;
bool Matrix::operator==(const Matrix& other) const
{

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (_m[i][j] != other.GetM(i, j))
			{
				return false;
			}
		}
	}
	return true;

};
// Multiply two matrices together
const Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix newMatrix;
	float value = { 0 };

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			float sum = 0;
			for (int k = 0; k < COLS; k++)
			{
				sum += _m[i][k] * other.GetM(k, j);
			}
			newMatrix.SetM(i, j, sum);
		}
	}

	return newMatrix;

};
// Multiply a matrix by a vertex, returning a vertex
const Vertex Matrix::operator*(Vertex& other) const
{
	Vertex tempVert = other;
	tempVert.SetX(_m[0][0] * other.GetX() + _m[0][1] * other.GetY() + _m[0][2] * other.GetZ() + _m[0][3] * other.GetW());
	tempVert.SetY(_m[1][0] * other.GetX() + _m[1][1] * other.GetY() + _m[1][2] * other.GetZ() + _m[1][3] * other.GetW());
	tempVert.SetZ(_m[2][0] * other.GetX() + _m[2][1] * other.GetY() + _m[2][2] * other.GetZ() + _m[2][3] * other.GetW());
	tempVert.SetW(_m[3][0] * other.GetX() + _m[3][1] * other.GetY() + _m[3][2] * other.GetZ() + _m[3][3] * other.GetW());
	return tempVert;
	
		
}


void Matrix::Copy(const Matrix& other)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_m[i][j] = other.GetM(i, j);
		}
	}
}
