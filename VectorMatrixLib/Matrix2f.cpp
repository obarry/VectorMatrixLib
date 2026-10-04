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
#include "Matrix2f.h"
#include "Vector2f.h"
#include "MathTools.h"
#include "Exceptions.h"
#include "GaussJordanSolver.h"

namespace vectormatrix
{
	Matrix2f::Matrix2f()
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] = 0;
	}

	Matrix2f::Matrix2f(float a)
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] = a;
	}

	Matrix2f::Matrix2f(const float array[SIZE2][SIZE2])
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] = array[i][j];
	}

	Matrix2f Matrix2f::operator+(const Matrix2f& m) const
	{
		Matrix2f r;
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				r.array_[i][j] = array_[i][j] + m.array_[i][j];
		return r;
	}

	Matrix2f& Matrix2f::operator+=(const Matrix2f& m)
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] += m.array_[i][j];
		return *this;
	}

	Matrix2f Matrix2f::operator-(const Matrix2f& m) const
	{
		Matrix2f r;
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				r.array_[i][j] = array_[i][j] - m.array_[i][j];
		return r;
	}

	Matrix2f& Matrix2f::operator-=(const Matrix2f& m)
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] -= m.array_[i][j];
		return *this;
	}

	Matrix2f Matrix2f::operator*(const Matrix2f& m) const
	{
		Matrix2f r;
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				for (int k = 0; k < SIZE2; k++)
					r.array_[i][j] += array_[i][k] * m.array_[k][j];
		return r;
	}

	Matrix2f& Matrix2f::operator*=(const Matrix2f& m)
	{
		*this = *this * m;
		return *this;
	}

	Matrix2f Matrix2f::operator*(float a) const
	{
		Matrix2f r;
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				r.array_[i][j] = array_[i][j] * a;
		return r;
	}

	Matrix2f& Matrix2f::operator*=(float a)
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] *= a;
		return *this;
	}

	Vector2f Matrix2f::operator*(const Vector2f& v) const
	{
		return v * *this;
	}

	bool Matrix2f::operator==(const Matrix2f& m) const
	{
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				if (!MathTools::equals(array_[i][j], m.array_[i][j])) return false;
		return true;
	}

	bool Matrix2f::operator!=(const Matrix2f& m) const
	{
		return !(*this == m);
	}

	float Matrix2f::get(int x, int y) const
	{
		return array_[x][y];
	}

	void Matrix2f::set(int x, int y, float a)
	{
		array_[x][y] = a;
	}

	Matrix2f Matrix2f::identity()
	{
		Matrix2f r;
		r.setDiagonal(1);
		return r;
	}

	void Matrix2f::setDiagonal(float v)
	{
		for (int i = 0; i < SIZE2; i++)
			array_[i][i] = v;
	}

	Vector2f Matrix2f::getRow(int r) const
	{
		if (r < 0 || r >= SIZE2) throw IndexOutOfBoundException("Index out of bound while getting Row (" + std::to_string(r) + ") of Matrix2f");
		return Vector2f(array_[r][0], array_[r][1]);
	}

	Vector2f Matrix2f::getColumn(int c) const
	{
		if (c < 0 || c >= SIZE2) throw IndexOutOfBoundException("Index out of bound while getting Column (" + std::to_string(c) + ") of Matrix2f");
		return Vector2f(array_[0][c], array_[1][c]);
	}

	void Matrix2f::setRow(int r, const Vector2f& v)
	{
		if (r < 0 || r >= SIZE2) throw IndexOutOfBoundException("Index out of bound while setting Row (" + std::to_string(r) + ") of Matrix2f");
		for (int j = 0; j < SIZE2; j++)
			array_[r][j] = v.get(j);
	}

	void Matrix2f::setColumn(int c, const Vector2f& v)
	{
		if (c < 0 || c >= SIZE2) throw IndexOutOfBoundException("Index out of bound while setting Column (" + std::to_string(c) + ") of Matrix2f");
		for (int i = 0; i < SIZE2; i++)
			array_[i][c] = v.get(i);
	}

	std::vector<std::vector<float>> Matrix2f::getArray() const
	{
		std::vector<std::vector<float>> a(SIZE2, std::vector<float>(SIZE2));
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				a[i][j] = array_[i][j];
		return a;
	}

	void Matrix2f::setArray(const std::vector<std::vector<float>>& a)
	{
		if (a.size() != SIZE2) throw MatrixArrayWrongSizeException("Wrong array row size (" + std::to_string(a.size()) + ") while setting Matrix2f from array");
		for (int i = 0; i < SIZE2; i++)
			if (a[i].size() != SIZE2) throw MatrixArrayWrongSizeException("Wrong array column size (" + std::to_string(a[i].size()) + ") while setting Matrix2f from array");
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				array_[i][j] = a[i][j];
	}

	float Matrix2f::trace() const
	{
		float t = 0;
		for (int i = 0; i < SIZE2; i++)
			t += array_[i][i];
		return t;
	}

	bool Matrix2f::isIdentity() const
	{
		return *this == identity();
	}

	float Matrix2f::determinant() const
	{
		return array_[0][0] * array_[1][1] - array_[0][1] * array_[1][0];
	}

	Matrix2f Matrix2f::transpose() const
	{
		Matrix2f r;
		for (int i = 0; i < SIZE2; i++)
			for (int j = 0; j < SIZE2; j++)
				r.array_[i][j] = array_[j][i];
		return r;
	}

	Matrix2f& Matrix2f::transposeEquals()
	{
		*this = transpose();
		return *this;
	}

	Matrix2f Matrix2f::inverse() const
	{
		Matrix2f r;
		GaussJordanSolver::invert<SIZE2>(array_, r.array_, EPSILON);
		return r;
	}

	std::ostream& operator<<(std::ostream& strm, const Matrix2f& m)
	{
		strm << "Matrix2f(" << std::endl;
		for (int i = 0; i < Matrix2f::SIZE2; i++)
		{
			for (int j = 0; j < Matrix2f::SIZE2; j++)
			{
				strm << m.array_[i][j] << " ";
			}
			strm << std::endl;
		}
		return strm << ")";
	}
}
