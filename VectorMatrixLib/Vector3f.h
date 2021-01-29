#pragma once
#include <iostream>

class Vector3f
{
public:
	Vector3f();
	Vector3f(float a);
	Vector3f(float x, float y, float z);
	Vector3f(float array[3]);
	float get(int i);
	void set(int i, float v);
	Vector3f times(float a);
	void timesEquals(float a);

private:
	float x;
	float y;
	float z;
	friend std::ostream& operator<<(std::ostream&, const Vector3f&);
};