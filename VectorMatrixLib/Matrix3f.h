#pragma once
#include <iostream>

class Matrix3f
{
public:
	Matrix3f();
	Matrix3f(float a);
	Matrix3f(float array[3][3]);
	float get(int x, int y);
	void set(int x, int y, float a);
	Matrix3f times(Matrix3f m);

private:
	float array_[3][3];
	friend std::ostream& operator<<(std::ostream&, const Matrix3f&);
};