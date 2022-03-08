#pragma once
#include "Model.h"



Model::Model()
{
	_kdRed = 0.5f;
	_kdGreen = 0.5f;
	_kdBlue = 0.5f;
	 _kaRed = 0.5f;
	 _kaGreen = 0.5f;
	 _kaBlue = 0.5f;
	 _a = 0.5f;
	 _b = 0.5f;
	 _c = 0.5f;
}
Model::~Model()
{

}
std::vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}
Polygon3D Model::GetPolygon(int index)
{
	return _polygons.at(index);
}
std::vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}
Vertex Model::GetTransVert(int index)
{
	return _transformedVertices.at(index);
}
std::vector<Vertex>& Model::GetTransVertices()
{
	return _transformedVertices;
}

std::vector<UVCoords>& Model::GetUVCoords()
{
	return _uvcoords;
}

Texture& Model::GetTexture()
{
	return _texture;
}

void Model::DrawSolidTextured()
{
	for (Polygon3D poly : _polygons)
	{
		for (int i = 0; i < 3; i++)
		{
			_transformedVertices.at(poly.GetIndex(i)).SetU(_uvcoords.at(poly.GetUVIndices(i)).GetU());
			_transformedVertices.at(poly.GetIndex(i)).SetV(_uvcoords.at(poly.GetUVIndices(i)).GetV());
		}
	}
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{
	for (int i = 0; i < GetVertexCount(); i++)
	{
		_transformedVertices.at(i) = transform * _vertices.at(i);
	}
}
void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (Vertex& vert : _transformedVertices)
	{
		vert = transform * vert;
	}
}
void Model::dehomogenizeVertecies()
{
	for (Vertex& vert : _transformedVertices)
	{
		vert.DehomogenizeVertex();
	}
}
void Model::CalculateBackfaces(Camera cam)
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		Vector3D a = _transformedVertices.at(_polygons.at(i).GetIndex(0)) - _transformedVertices.at(_polygons.at(i).GetIndex(1));
		Vector3D b = _transformedVertices.at(_polygons.at(i).GetIndex(0)) - _transformedVertices.at(_polygons.at(i).GetIndex(2));
		_polygons.at(i).SetNormalVector(Vector3D::CrossProduct(a, b));
		Vector3D normalizedVector = _polygons.at(i).GetNormalVector();
		normalizedVector.NormalizeVector();
		_polygons.at(i).SetNormalVector(normalizedVector);
		Vector3D normalizedEyeVector = _transformedVertices.at(_polygons.at(i).GetIndex(0)) - cam.GetCameraCoords();
		normalizedEyeVector.NormalizeVector();
		float dot = Vector3D::DotProduct(normalizedVector, normalizedEyeVector);
		if (dot > 0)
		{
			_polygons.at(i).SetToBeCulled(false);
		}
		else
		{
			_polygons.at(i).SetToBeCulled(true);
		}
	}
}
int Model::ClampNumber(int number, int min, int max)
{
	if (number < min)
	{
		return min;
	}
	else if (number > max)
	{
		return max;
	}
	return number;
}
void Model::GenerateNormalVectorForVertex()
{
	
	for (Vertex& ver : _transformedVertices)
	{
		ver.SetNormalVector(Vector3D(0.0f, 0.0f, 0.0f));
		ver.ResetCount();
	}
	for (Polygon3D& poly : _polygons)
	{
		for (int i = 0; i < 3; i++)
		{
			Vector3D normalVector = _transformedVertices.at(poly.GetIndex(i)).GetNormalVector();
			normalVector = normalVector + poly.GetNormalVector();
			_transformedVertices.at(poly.GetIndex(i)).SetNormalVector(normalVector);
			_transformedVertices.at(poly.GetIndex(i)).AddToCounter();
		}	
	}
	for (Vertex& ver : _transformedVertices)
	{
		Vector3D temp = ver.GetNormalVector();
		temp.SetX(temp.GetX() / ver.GetCount());
		temp.SetY(temp.GetY() / ver.GetCount());
		temp.SetZ(temp.GetZ() / ver.GetCount());
		
		temp.NormalizeVector();
		ver.SetNormalVector(temp);
	}
}
void Model::CalculatePointLight(vector<PointLight> lights)
{
	int tempR, tempG, tempB;
	int totalR = 0;
	int totalG = 0;
	int totalB = 0;
	float dot = 0;
	float atten = 1;
	
	for (Vertex& ver : _transformedVertices)
	{
		COLORREF oldColor = ver.GetColor();
		totalR = GetRValue(oldColor);
		totalG = GetGValue(oldColor);
		totalB = GetBValue(oldColor);

		for (PointLight& light : lights)
		{
			tempR = int((float)light.GetRed() * 1.0f);
			tempG = int((float)light.GetGreen() * 1.0f);
			tempB = int((float)light.GetBlue() * 1.0f);
			Vector3D vectorToLight = ver - light.GetPosition();
			float vectorDistance = vectorToLight.VectorLength();
			atten = 1.0f / (0.0f + (0.1f * vectorDistance) + (0.0f * vectorDistance * vectorDistance));
			vectorToLight.NormalizeVector();
			Vector3D tempVec = ver.GetNormalVector();

			dot = Vector3D::DotProduct(vectorToLight, tempVec);
			if (dot > 0)
			{
				totalR = ClampNumber(totalR + int((float)tempR * atten * dot), 0, 255);
				totalG = ClampNumber(totalG + int((float)tempG * atten * dot), 0, 255);
				totalB = ClampNumber(totalB + int((float)tempB * atten * dot), 0, 255);
				COLORREF totalSum = RGB(totalR, totalG, totalB);
				ver.SetColor(totalSum);
			}
		}
	}
}
void Model::CalculatePointLightForPolygons(vector<PointLight> lights)
{
	int tempR, tempG, tempB;
	int totalR = 0;
	int totalG = 0;
	int totalB = 0;
	float dot = 0;
	float atten = 1;

	for (Polygon3D& poly : _polygons)
	{
		if (poly.ToBeCulled())
		{
			COLORREF oldColor = poly.GetColor();
			totalR = GetRValue(oldColor);
			totalG = GetGValue(oldColor);
			totalB = GetBValue(oldColor);

			for (PointLight& light : lights)
			{
				tempR = int((float)light.GetRed() * 1.0f);
				tempG = int((float)light.GetGreen() * 1.0f);
				tempB = int((float)light.GetBlue() * 1.0f);
				Vector3D vectorToLight = _transformedVertices.at(poly.GetIndex(0)) - light.GetPosition();
				float vectorDistance = vectorToLight.VectorLength();
				atten = 1.0f / (0.0f + (0.1f * vectorDistance) + (0.0f * vectorDistance * vectorDistance));
				vectorToLight.NormalizeVector();
				Vector3D tempVec = poly.GetNormalVector();

				dot = Vector3D::DotProduct(vectorToLight, tempVec) * -1.0f;
				if (dot > 0)
				{
					totalR = ClampNumber(totalR + int((float)tempR * atten * dot), 0, 255);
					totalG = ClampNumber(totalG + int((float)tempG * atten * dot), 0, 255);
					totalB = ClampNumber(totalB + int((float)tempB * atten * dot), 0, 255);
					COLORREF totalSum = RGB(totalR, totalG, totalB);
					poly.SetColor(totalSum);
				}
			}
		}
	}
}
void Model::CalculateAmbientLight(AmbientLight light)
{
	int tempR, tempG, tempB;
	int totalR = 0;
	int totalG = 0;
	int totalB = 0;
	for (Polygon3D& poly : _polygons)
	{
		if (poly.ToBeCulled())
		{
			totalR = 0;
			totalG = 0;
			totalB = 0;

			tempR = int((float)light.GetRed() * _kaRed);
			tempG = int((float)light.GetGreen() * _kaGreen);
			tempB = int((float)light.GetBlue() * _kaBlue);
			totalR = ClampNumber(totalR + (int)tempR, 0, 255);
			totalG = ClampNumber(totalG + (int)tempG, 0, 255);
			totalB = ClampNumber(totalB + (int)tempB, 0, 255);
			COLORREF totalSum = RGB(totalR, totalG, totalB);
			poly.SetColor(totalSum);
			_transformedVertices.at(poly.GetIndex(0)).SetColor(RGB(totalR, totalG, totalB));
			_transformedVertices.at(poly.GetIndex(1)).SetColor(RGB(totalR, totalG, totalB));
			_transformedVertices.at(poly.GetIndex(2)).SetColor(RGB(totalR, totalG, totalB));
		}
	}
}
void Model::CalculateLightingDirectional(vector<DirLight> lights)
{
	int tempR, tempG, tempB;
	int totalR = 0;
	int totalG = 0;
	int totalB = 0;
	float dot = 0;

	for (Polygon3D& poly : _polygons)
	{
		if (poly.ToBeCulled())
		{
			COLORREF oldColor = poly.GetColor();
			totalR = GetRValue(oldColor);
			totalG = GetGValue(oldColor);
			totalB = GetBValue(oldColor);
			for (int i = 0; i < 3; i++)
			{
				for (DirLight& light : lights)
				{
					Vector3D lightVector = light.GetVector();
					lightVector.NormalizeVector();
					Vector3D tempVec = _transformedVertices.at(poly.GetIndex(i)).GetNormalVector();

					dot = Vector3D::DotProduct(lightVector, tempVec);
					if (dot > 0)
					{
						tempR = int((float)light.GetRed() * _kdRed);
						tempG = int((float)light.GetGreen() * _kdGreen);
						tempB = int((float)light.GetBlue() * _kdBlue);
						totalR = ClampNumber(totalR + (int)((float)tempR * dot), 0, 255);
						totalG = ClampNumber(totalG + (int)((float)tempG * dot), 0, 255);
						totalB = ClampNumber(totalB + (int)((float)tempB * dot), 0, 255);
						_transformedVertices.at(poly.GetIndex(i)).SetColor(RGB(totalR, totalG, totalB));
						poly.SetColor(RGB(totalR, totalG, totalB));
					}
				}
			}

		}

	}
}
bool  Model::sortByZAvg(const Polygon3D& lhs, const Polygon3D& rhs)
{
	return (lhs.GetAvgZ() < rhs.GetAvgZ());
}
void Model::Sort()
{
	CalculateAvgZ();
	std::sort(_polygons.begin(), _polygons.end(), sortByZAvg);
}
void Model::CalculateAvgZ()
{
	for (int i = 0; i < GetPolygonCount(); i++)
	{
		float sum = _transformedVertices.at(_polygons.at(i).GetIndex(0)).GetZ() +
			_transformedVertices.at(_polygons.at(i).GetIndex(1)).GetZ() +
			_transformedVertices.at(_polygons.at(i).GetIndex(2)).GetZ();
		float avg = sum / 3.0f;
		_polygons.at(i).SetAvgZ(avg);
	}
}
size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}
size_t Model::GetVertexCount() const
{
	return _vertices.size();
}
void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
	_transformedVertices.push_back(Vertex(x, y, z));
}
void Model::AddPolygon(int i0, int i1, int i2, int uv0, int uv1, int uv2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2, uv0, uv1, uv2));
	
}
void Model::AddTextureUV(float u, float v)
{
	_uvcoords.push_back(UVCoords(u,v));
}