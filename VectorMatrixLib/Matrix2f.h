//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef MATRIX2F_H
#define MATRIX2F_H

#include <iostream>
#include <vector>
#include "Vector2f.h"

namespace vectormatrix
{
	class Matrix2f
	{
	public:
		// Constants
		static const int SIZE2 = 2;

		// Identity matrix (a new copy is returned each time)
		static Matrix2f identity();

		// Constructors
		Matrix2f();
		explicit Matrix2f(float a);
		explicit Matrix2f(const float array[SIZE2][SIZE2]);

		// Operators
		Matrix2f operator+(const Matrix2f& m) const;
		Matrix2f& operator+=(const Matrix2f& m);
		Matrix2f operator-(const Matrix2f& m) const;
		Matrix2f& operator-=(const Matrix2f& m);
		Matrix2f operator*(const Matrix2f& m) const;
		Matrix2f& operator*=(const Matrix2f& m);
		Matrix2f operator*(float a) const;
		Matrix2f& operator*=(float a);
		// W = A.V
		Vector2f operator*(const Vector2f& v) const;
		// Equality within EPSILON tolerance
		bool operator==(const Matrix2f& m) const;
		bool operator!=(const Matrix2f& m) const;

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);
		void setDiagonal(float v);
		// Rows and columns (throw IndexOutOfBoundException if the index is out of bound)
		Vector2f getRow(int r) const;
		Vector2f getColumn(int c) const;
		void setRow(int r, const Vector2f& v);
		void setColumn(int c, const Vector2f& v);
		// Copy of the elements, and set from an array (throws MatrixArrayWrongSizeException if not 2x2)
		std::vector<std::vector<float>> getArray() const;
		void setArray(const std::vector<std::vector<float>>& a);
		// Other methods
		float trace() const;
		bool isIdentity() const;
		float determinant() const;
		Matrix2f transpose() const;
		Matrix2f& transposeEquals();
		// Throws NotInvertibleMatrixException if this matrix is singular
		Matrix2f inverse() const;

	private:
		float array_[SIZE2][SIZE2];
		friend std::ostream& operator<<(std::ostream&, const Matrix2f&);
	};
}

#endif // MATRIX2F_H
