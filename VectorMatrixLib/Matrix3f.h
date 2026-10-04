//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef MATRIX3F_H
#define MATRIX3F_H

#include <iostream>
#include <vector>
#include "Vector3f.h"

namespace vectormatrix
{
	class Matrix4f;

	class Matrix3f
	{
	public:
		// Constants
		static const int SIZE3 = 3;

		// Identity matrix (a new copy is returned each time)
		static Matrix3f identity();

		// Constructors
		Matrix3f();
		explicit Matrix3f(float a);
		explicit Matrix3f(const float array[SIZE3][SIZE3]);
		explicit Matrix3f(const Matrix4f& b);

		// Operators
		Matrix3f operator+(const Matrix3f& m) const;
		Matrix3f& operator+=(const Matrix3f& m);
		Matrix3f operator-(const Matrix3f& m) const;
		Matrix3f& operator-=(const Matrix3f& m);
		Matrix3f operator*(const Matrix3f& m) const;
		Matrix3f& operator*=(const Matrix3f& m);
		Matrix3f operator*(float a) const;
		Matrix3f& operator*=(float a);
		// W = A.V
		Vector3f operator*(const Vector3f& v) const;
		// Equality within EPSILON tolerance
		bool operator==(const Matrix3f& m) const;
		bool operator!=(const Matrix3f& m) const;

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);
		void setDiagonal(float v);
		// Rows and columns (throw IndexOutOfBoundException if the index is out of bound)
		Vector3f getRow(int r) const;
		Vector3f getColumn(int c) const;
		void setRow(int r, const Vector3f& v);
		void setColumn(int c, const Vector3f& v);
		// Copy of the elements, and set from an array (throws MatrixArrayWrongSizeException if not 3x3)
		std::vector<std::vector<float>> getArray() const;
		void setArray(const std::vector<std::vector<float>>& a);
		// Other methods
		float trace() const;
		bool isIdentity() const;
		float determinant() const;
		Matrix3f transpose() const;
		Matrix3f& transposeEquals();
		// Throws NotInvertibleMatrixException if this matrix is singular
		Matrix3f inverse() const;

	private:
		float array_[SIZE3][SIZE3];
		friend std::ostream& operator<<(std::ostream&, const Matrix3f&);
	};
}

#endif // MATRIX3F_H
