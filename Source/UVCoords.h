#pragma once
class UVCoords
{
public:
	UVCoords();
	UVCoords(float u, float v);
	float GetU();
	float GetV();
	void SetU(float u);
	void SetV(float v);
private:
	float _u;
	float _v;
};

