//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include <iostream>
#include <string>
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "MathTools.h"
#include "Exceptions.h"
#include "GaussJordanSolver.h"

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

	Matrix3f Matrix3f::identity()
	{
		Matrix3f r;
		r.setDiagonal(1);
		return r;
	}

	void Matrix3f::setDiagonal(float v)
	{
		for (int i = 0; i < SIZE3; i++)
			array_[i][i] = v;
	}

	Vector3f Matrix3f::getRow(int r) const
	{
		if (r < 0 || r >= SIZE3) throw IndexOutOfBoundException("Index out of bound while getting Row (" + std::to_string(r) + ") of Matrix3f");
		return Vector3f(r, *this);
	}

	Vector3f Matrix3f::getColumn(int c) const
	{
		if (c < 0 || c >= SIZE3) throw IndexOutOfBoundException("Index out of bound while getting Column (" + std::to_string(c) + ") of Matrix3f");
		return Vector3f(*this, c);
	}

	void Matrix3f::setRow(int r, const Vector3f& v)
	{
		if (r < 0 || r >= SIZE3) throw IndexOutOfBoundException("Index out of bound while setting Row (" + std::to_string(r) + ") of Matrix3f");
		for (int j = 0; j < SIZE3; j++)
			array_[r][j] = v.get(j);
	}

	void Matrix3f::setColumn(int c, const Vector3f& v)
	{
		if (c < 0 || c >= SIZE3) throw IndexOutOfBoundException("Index out of bound while setting Column (" + std::to_string(c) + ") of Matrix3f");
		for (int i = 0; i < SIZE3; i++)
			array_[i][c] = v.get(i);
	}

	std::vector<std::vector<float>> Matrix3f::getArray() const
	{
		std::vector<std::vector<float>> a(SIZE3, std::vector<float>(SIZE3));
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				a[i][j] = array_[i][j];
		return a;
	}

	void Matrix3f::setArray(const std::vector<std::vector<float>>& a)
	{
		if (a.size() != SIZE3) throw MatrixArrayWrongSizeException("Wrong array row size (" + std::to_string(a.size()) + ") while setting Matrix3f from array");
		for (int i = 0; i < SIZE3; i++)
			if (a[i].size() != SIZE3) throw MatrixArrayWrongSizeException("Wrong array column size (" + std::to_string(a[i].size()) + ") while setting Matrix3f from array");
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				array_[i][j] = a[i][j];
	}

	float Matrix3f::trace() const
	{
		float t = 0;
		for (int i = 0; i < SIZE3; i++)
			t += array_[i][i];
		return t;
	}

	bool Matrix3f::isIdentity() const
	{
		return *this == identity();
	}

	float Matrix3f::determinant() const
	{
		return array_[0][0] * (array_[1][1] * array_[2][2] - array_[1][2] * array_[2][1])
			- array_[0][1] * (array_[1][0] * array_[2][2] - array_[1][2] * array_[2][0])
			+ array_[0][2] * (array_[1][0] * array_[2][1] - array_[1][1] * array_[2][0]);
	}

	Matrix3f Matrix3f::transpose() const
	{
		Matrix3f r;
		for (int i = 0; i < SIZE3; i++)
			for (int j = 0; j < SIZE3; j++)
				r.array_[i][j] = array_[j][i];
		return r;
	}

	Matrix3f& Matrix3f::transposeEquals()
	{
		*this = transpose();
		return *this;
	}

	Matrix3f Matrix3f::inverse() const
	{
		Matrix3f r;
		GaussJordanSolver::invert<SIZE3>(array_, r.array_, EPSILON);
		return r;
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
