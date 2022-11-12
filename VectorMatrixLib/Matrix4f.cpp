//
// MIT License
// Copyright(c) 2021 - 2022 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include <iostream>
#include "Matrix4f.h"
#include "Matrix3f.h"

namespace vectormatrix
{
	Matrix4f::Matrix4f()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				array_[i][j] = 0;
	}

	Matrix4f::Matrix4f(float a)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				array_[i][j] = a;
	}

	Matrix4f::Matrix4f(float array[4][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				array_[i][j] = array[i][j];
	}

	Matrix4f::Matrix4f(Matrix3f& b)
	{
		// Copy 3 first columns and rows of Matrix3 into Matrix4
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				array_[i][j] = b.get(i, j);

		// Then omplete the Matrix4 with 0 in latest row and column
		for (int k = 0; k < 4; k++)
		{
			array_[k][3] = 0;
			if (k < 3) array_[3][k] = 0;
		}
	}

	Matrix4f Matrix4f::operator+(const Matrix4f& m)
	{
		Matrix4f r;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				r.array_[i][j] = this->array_[i][j] + m.array_[i][j];

		return r;
	}

	Matrix4f Matrix4f::operator-(const Matrix4f& m)
	{
		Matrix4f r;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				r.array_[i][j] = this->array_[i][j] - m.array_[i][j];

		return r;
	}


	float Matrix4f::get(int x, int y) const
	{
		return array_[x][y];
	}

	void Matrix4f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	Matrix4f Matrix4f::times(Matrix4f& b)
	{
		Matrix4f r;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				r.set(i, j, get(i, 0) * b.get(0, j) + get(i, 1) * b.get(1, j) + get(i, 2) * b.get(2, j) + get(i, 3) * b.get(3, j));

		return r;
	}

	void Matrix4f::times(float a)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				array_[i][j] *= a;
	}

	Vector4f Matrix4f::times(Vector4f& v)
	{
		return Vector4f();
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix4f& m) {
		strm << "Matrix4f(" << std::endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				strm << m.array_[i][j] << " ";
			}
			strm << std::endl;
		}
		return strm << ")";
	}
}
