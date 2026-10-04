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
#include "MathTools.h"

namespace vectormatrix
{
	Matrix3f::Matrix3f()
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = 0;
	}

	Matrix3f::Matrix3f(float a)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = a;
	}

	Matrix3f::Matrix3f(const float array[SIZE3][SIZE3])
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = array[i][j];
	}

	Matrix3f::Matrix3f(const Matrix4f& b)
	{
		// Keep the upper-left 3x3 part of the Matrix4f
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = b.get(i, j);
	}

	Matrix3f Matrix3f::operator+(const Matrix3f& m) const
	{
		Matrix3f r;
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r.array_[i][j] = array_[i][j] + m.array_[i][j];
		return r;
	}

	Matrix3f& Matrix3f::operator+=(const Matrix3f& m)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] += m.array_[i][j];
		return *this;
	}

	Matrix3f Matrix3f::operator-(const Matrix3f& m) const
	{
		Matrix3f r;
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r.array_[i][j] = array_[i][j] - m.array_[i][j];
		return r;
	}

	Matrix3f& Matrix3f::operator-=(const Matrix3f& m)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] -= m.array_[i][j];
		return *this;
	}

	Matrix3f Matrix3f::operator*(const Matrix3f& m) const
	{
		Matrix3f r;
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				for (int k = 0; k < SIZE3; k++)
					r.array_[i][j] += array_[i][k] * m.array_[k][j];
		return r;
	}

	Matrix3f& Matrix3f::operator*=(const Matrix3f& m)
	{
		*this = *this * m;
		return *this;
	}

	Matrix3f Matrix3f::operator*(float a) const
	{
		Matrix3f r;
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r.array_[i][j] = array_[i][j] * a;
		return r;
	}

	Matrix3f& Matrix3f::operator*=(float a)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] *= a;
		return *this;
	}

	Vector3f Matrix3f::operator*(const Vector3f& v) const
	{
		return v * *this;
	}

	bool Matrix3f::operator==(const Matrix3f& m) const
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				if (!MathTools::equals(array_[i][j], m.array_[i][j])) return false;
		return true;
	}

	bool Matrix3f::operator!=(const Matrix3f& m) const
	{
		return !(*this == m);
	}

	float Matrix3f::get(int x, int y) const
	{
		return array_[x][y];
	}

	void Matrix3f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix3f& m)
	{
		strm << "Matrix3f(" << std::endl;
		for (int i = 0; i < Matrix3f::SIZE3; i++)
		{
			for (int j = 0; j < Matrix3f::SIZE3; j++)
			{
				strm << m.array_[i][j] << " ";
			}
			strm << std::endl;
		}
		return strm << ")";
	}
}
