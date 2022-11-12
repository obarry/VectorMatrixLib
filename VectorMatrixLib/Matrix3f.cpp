//
// MIT License
// Copyright(c) 2021 - 2022 Olivier BARRY
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

	Matrix3f::Matrix3f(float array[SIZE3][SIZE3])
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = array[i][j];
	}

	Matrix3f::Matrix3f(const Matrix3f& m)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				this->array_[i][j] = m.array_[i][j];
	}

	Matrix3f::Matrix3f(Matrix4f& b)
	{
		// Copy 3 first columns and rows of Matrix3 into Matrix4
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = b.get(i, j);
	}

	void Matrix3f::operator=(const Matrix3f& m)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				this->array_[i][j] = m.array_[i][j];
	}

	Matrix3f Matrix3f::operator+(const Matrix3f& m)
	{
		Matrix3f* r = new Matrix3f();
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r->array_[i][j] = this->array_[i][j] + m.array_[i][j];

		return *r;
	}

	void Matrix3f::operator+=(const Matrix3f& m)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				this->array_[i][j] += m.array_[i][j];
	}

	Matrix3f Matrix3f::operator-(const Matrix3f& m)
	{
		Matrix3f* r = new Matrix3f();
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r->array_[i][j] = this->array_[i][j] - m.array_[i][j];

		return *r;
	}

	void Matrix3f::operator-=(const Matrix3f& m)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				this->array_[i][j] += m.array_[i][j];
	}

	Matrix3f Matrix3f::operator*(const Matrix3f& m)
	{
		Matrix3f* r = new Matrix3f();
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r->array_[i][j] = array_[i][0] * m.array_[0][j] + array_[i][1] * m.array_[1][j] + array_[i][2] * m.array_[2][j];

		return *r;
	}

	void Matrix3f::operator*=(const Matrix3f& m)
	{
		Matrix3f* r = new Matrix3f();
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r->array_[i][j] = array_[i][0] * m.array_[0][j] + array_[i][1] * m.array_[1][j] + array_[i][2] * m.array_[2][j];
		*this = *r;
	}

	Matrix4f Matrix3f::operator*(float a)
	{
		Matrix3f* r = new Matrix3f();
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r->array_[i][j] = this->array_[i][j] * a;

		return *r;
	}

	void Matrix3f::operator*=(float a)
	{
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] *= a;
	}

	Vector3f Matrix3f::operator*(Vector3f& v)
	{
		return v * *this;
	}

	float Matrix3f::get(int x, int y) const
	{
		return array_[x][y];
	}

	void Matrix3f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix3f& m) {
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