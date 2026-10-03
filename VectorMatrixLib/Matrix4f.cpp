//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include <iostream>
#include "Matrix3f.h"
#include "Matrix4f.h"

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

	Matrix4f::Matrix4f(const float array[SIZE4][SIZE4])
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = array[i][j];
	}

	Matrix4f::Matrix4f(const Matrix3f& b)
	{
		// Copy the Matrix3f in the upper-left 3x3 part, then fill the last row and column with 0
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = (i < Matrix3f::SIZE3 && j < Matrix3f::SIZE3) ? b.get(i, j) : 0;
	}

	Matrix4f Matrix4f::operator+(const Matrix4f& m) const
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r.array_[i][j] = array_[i][j] + m.array_[i][j];
		return r;
	}

	Matrix4f& Matrix4f::operator+=(const Matrix4f& m)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] += m.array_[i][j];
		return *this;
	}

	Matrix4f Matrix4f::operator-(const Matrix4f& m) const
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r.array_[i][j] = array_[i][j] - m.array_[i][j];
		return r;
	}

	Matrix4f& Matrix4f::operator-=(const Matrix4f& m)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] -= m.array_[i][j];
		return *this;
	}

	Matrix4f Matrix4f::operator*(const Matrix4f& m) const
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				for (int k = 0; k < SIZE4; k++)
					r.array_[i][j] += array_[i][k] * m.array_[k][j];
		return r;
	}

	Matrix4f& Matrix4f::operator*=(const Matrix4f& m)
	{
		*this = *this * m;
		return *this;
	}

	Matrix4f Matrix4f::operator*(float a) const
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r.array_[i][j] = array_[i][j] * a;
		return r;
	}

	Matrix4f& Matrix4f::operator*=(float a)
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] *= a;
		return *this;
	}

	Vector4f Matrix4f::operator*(const Vector4f& v) const
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

	std::ostream& operator<<(std::ostream& strm, const Matrix4f& m)
	{
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
