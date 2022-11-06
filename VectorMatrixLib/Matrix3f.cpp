#include <iostream>
#include "Matrix3f.h"
#include "Matrix4f.h"

namespace vectormatrix
{

	Matrix3f::Matrix3f()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				array_[i][j] = 0;
	}

	Matrix3f::Matrix3f(float a)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				array_[i][j] = a;
	}

	Matrix3f::Matrix3f(float array[3][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				array_[i][j] = array[i][j];
	}

	Matrix3f::Matrix3f(Matrix4f& b)
	{
		// Copy 3 first columns and rows of Matrix3 into Matrix4
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				array_[i][j] = b.get(i, j);
	}

	Matrix3f Matrix3f::operator+(const Matrix3f& m)
	{
		Matrix3f r;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				r.array_[i][j] = this->array_[i][j] + m.array_[i][j];

		return r;
	}

	Matrix3f Matrix3f::operator-(const Matrix3f& m)
	{
		Matrix3f r;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				r.array_[i][j] = this->array_[i][j] - m.array_[i][j];

		return r;
	}

	float Matrix3f::get(int x, int y)
	{
		return array_[x][y];
	}

	void Matrix3f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	Matrix3f Matrix3f::times(Matrix3f& b)
	{
		Matrix3f r;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				r.array_[i][j] = array_[i][0] * b.array_[0][j] + array_[i][1] * b.array_[1][j] + array_[i][2] * b.array_[2][j];

		return r;
	}

	void Matrix3f::times(float a)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				array_[i][j] *= a;
	}

	Vector3f Matrix3f::times(Vector3f& v)
	{
		Vector3f r;
		for (int i = 0; i < 3; i++)
			r.set(i, array_[i][0] * v.x + array_[i][1] * v.y + array_[i][2] * v.z);
		return r;
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix3f& m) {
		strm << "Matrix3f(" << std::endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				strm << m.array_[i][j] << " ";
			}
			strm << std::endl;
		}
		return strm << ")";
	}
}