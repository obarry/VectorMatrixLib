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

	bool Matrix4f::operator==(const Matrix4f& m) const
	{
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				if (!MathTools::equals(array_[i][j], m.array_[i][j])) return false;
		return true;
	}

	bool Matrix4f::operator!=(const Matrix4f& m) const
	{
		return !(*this == m);
	}

	float Matrix4f::get(int x, int y) const
	{
		return array_[x][y];
	}

	void Matrix4f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	Matrix4f Matrix4f::identity()
	{
		Matrix4f r;
		r.setDiagonal(1);
		return r;
	}

	void Matrix4f::setDiagonal(float v)
	{
		for (int i = 0; i < SIZE4; i++)
			array_[i][i] = v;
	}

	Vector4f Matrix4f::getRow(int r) const
	{
		if (r < 0 || r >= SIZE4) throw IndexOutOfBoundException("Index out of bound while getting Row (" + std::to_string(r) + ") of Matrix4f");
		return Vector4f(r, *this);
	}

	Vector4f Matrix4f::getColumn(int c) const
	{
		if (c < 0 || c >= SIZE4) throw IndexOutOfBoundException("Index out of bound while getting Column (" + std::to_string(c) + ") of Matrix4f");
		return Vector4f(*this, c);
	}

	void Matrix4f::setRow(int r, const Vector4f& v)
	{
		if (r < 0 || r >= SIZE4) throw IndexOutOfBoundException("Index out of bound while setting Row (" + std::to_string(r) + ") of Matrix4f");
		for (int j = 0; j < SIZE4; j++)
			array_[r][j] = v.get(j);
	}

	void Matrix4f::setColumn(int c, const Vector4f& v)
	{
		if (c < 0 || c >= SIZE4) throw IndexOutOfBoundException("Index out of bound while setting Column (" + std::to_string(c) + ") of Matrix4f");
		for (int i = 0; i < SIZE4; i++)
			array_[i][c] = v.get(i);
	}

	std::vector<std::vector<float>> Matrix4f::getArray() const
	{
		std::vector<std::vector<float>> a(SIZE4, std::vector<float>(SIZE4));
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				a[i][j] = array_[i][j];
		return a;
	}

	void Matrix4f::setArray(const std::vector<std::vector<float>>& a)
	{
		if (a.size() != SIZE4) throw MatrixArrayWrongSizeException("Wrong array row size (" + std::to_string(a.size()) + ") while setting Matrix4f from array");
		for (int i = 0; i < SIZE4; i++)
			if (a[i].size() != SIZE4) throw MatrixArrayWrongSizeException("Wrong array column size (" + std::to_string(a[i].size()) + ") while setting Matrix4f from array");
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				array_[i][j] = a[i][j];
	}

	Matrix3f Matrix4f::getMatrix3() const
	{
		return Matrix3f(*this);
	}

	float Matrix4f::trace() const
	{
		float t = 0;
		for (int i = 0; i < SIZE4; i++)
			t += array_[i][i];
		return t;
	}

	bool Matrix4f::isIdentity() const
	{
		return *this == identity();
	}

	float Matrix4f::determinant() const
	{
		// Cofactor expansion along the first row
		float det = 0;
		for (int col = 0; col < SIZE4; col++)
		{
			// 3x3 minor obtained by removing row 0 and column col
			Matrix3f minor;
			for (int i = 1; i < SIZE4; i++)
			{
				int mj = 0;
				for (int j = 0; j < SIZE4; j++)
				{
					if (j == col) continue;
					minor.set(i - 1, mj++, array_[i][j]);
				}
			}
			float sign = (col % 2 == 0) ? 1.0f : -1.0f;
			det += sign * array_[0][col] * minor.determinant();
		}
		return det;
	}

	Matrix4f Matrix4f::transpose() const
	{
		Matrix4f r;
		for (int i = 0; i < SIZE4; i++)
			for (int j = 0; j < SIZE4; j++)
				r.array_[i][j] = array_[j][i];
		return r;
	}

	Matrix4f& Matrix4f::transposeEquals()
	{
		*this = transpose();
		return *this;
	}

	Matrix4f Matrix4f::inverse() const
	{
		Matrix4f r;
		GaussJordanSolver::invert<SIZE4>(array_, r.array_, EPSILON);
		return r;
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
