//
// MIT License
// Copyright(c) 2021 - 2023 Olivier BARRY
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
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = 0;
	}

	Matrix4f::Matrix4f(float a)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = a;
	}

	Matrix4f::Matrix4f(float array[SIZE4][SIZE4])
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = array[i][j];
	}

	Matrix4f::Matrix4f(const Matrix4f& m)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				this->array_[i][j] = m.array_[i][j];
	}

	Matrix4f::Matrix4f(Matrix3f& b)
	{
		// Copy 3 first columns and rows of Matrix3 into Matrix4
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = b.get(i, j);

		// Then omplete the MatrixSIZE4 with 0 in latest row and column
		for (int k = 0; k < SIZE4; k++)
		{
			array_[k][3] = 0;
			if (k < 3) array_[3][k] = 0;
		}
	}

	void Matrix4f::operator=(const Matrix4f& m)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				this->array_[i][j] = m.array_[i][j];
	}

	Matrix4f Matrix4f::operator+(const Matrix4f& m)
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r.array_[i][j] = this->array_[i][j] + m.array_[i][j];

		return r;
	}

	void Matrix4f::operator+=(const Matrix4f& m)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				this->array_[i][j] +=  m.array_[i][j];
	}

	Matrix4f Matrix4f::operator-(const Matrix4f& m)
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r.array_[i][j] = this->array_[i][j] - m.array_[i][j];

		return r;
	}

	void Matrix4f::operator-=(const Matrix4f& m)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				this->array_[i][j] -= m.array_[i][j];
	}

	Matrix4f Matrix4f::operator*(const Matrix4f& m)
	{
		Matrix4f* r = new Matrix4f();
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r->array_[i][j] = array_[i][0] * m.array_[0][j] + array_[i][1] * m.array_[1][j] + array_[i][2] * m.array_[2][j] + array_[i][3] * m.array_[3][j];

		return *r;
	}

	void Matrix4f::operator*=(const Matrix4f& m)
	{
		Matrix4f* r = new Matrix4f();
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r->array_[i][j] = array_[i][0] * m.array_[0][j] + array_[i][1] * m.array_[1][j] + array_[i][2] * m.array_[2][j] + array_[i][3] * m.array_[3][j];
		*this = *r;
	}

	Matrix4f Matrix4f::operator*(float a)
	{
		Matrix4f *r = new Matrix4f();
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r->array_[i][j] = this->array_[i][j] * a;

		return *r;
	}

	void Matrix4f::operator*=(float a)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < 4; j++)
				array_[i][j] *= a;
	}

	Vector4f Matrix4f::operator*(Vector4f& v)
	{
		return v * *this;
	}

	float Matrix4f::get(int x, int y) const
	{
		return array_[x][y];
	}

	void Matrix4f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix4f& m) {
		strm << "Matrix4f(" << std::endl;
		for (int i = 0; i < Matrix4f::SIZE4; i++)
		{
			for (int j = 0; j < Matrix4f::SIZE4; j++)
			{
				strm << m.array_[i][j] << " ";
			}
			strm << std::endl;
		}
		return strm << ")";
	}
}
