//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <iostream>
#include <vector>
#include "Vector4f.h"

namespace vectormatrix
{
	class Matrix3f;

	class Matrix4f
	{
	public:
		// Constants
		static const int SIZE4 = 4;

		// Identity matrix (a new copy is returned each time)
		static Matrix4f identity();

		// Constructors
		Matrix4f();
		explicit Matrix4f(float a);
		explicit Matrix4f(const float array[SIZE4][SIZE4]);
		explicit Matrix4f(const Matrix3f& b);

		// Operators
		Matrix4f operator+(const Matrix4f& m) const;
		Matrix4f& operator+=(const Matrix4f& m);
		Matrix4f operator-(const Matrix4f& m) const;
		Matrix4f& operator-=(const Matrix4f& m);
		Matrix4f operator*(const Matrix4f& m) const;
		Matrix4f& operator*=(const Matrix4f& m);
		Matrix4f operator*(float a) const;
		Matrix4f& operator*=(float a);
		// W = A.V
		Vector4f operator*(const Vector4f& v) const;
		// Equality within EPSILON tolerance
		bool operator==(const Matrix4f& m) const;
		bool operator!=(const Matrix4f& m) const;

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);
		void setDiagonal(float v);
		// Rows and columns (throw IndexOutOfBoundException if the index is out of bound)
		Vector4f getRow(int r) const;
		Vector4f getColumn(int c) const;
		void setRow(int r, const Vector4f& v);
		void setColumn(int c, const Vector4f& v);
		// Copy of the elements, and set from an array (throws MatrixArrayWrongSizeException if not 4x4)
		std::vector<std::vector<float>> getArray() const;
		void setArray(const std::vector<std::vector<float>>& a);
		// Upper-left 3x3 part of this matrix
		Matrix3f getMatrix3() const;
		// Other methods
		float trace() const;
		bool isIdentity() const;
		float determinant() const;
		Matrix4f transpose() const;
		Matrix4f& transposeEquals();
		// Throws NotInvertibleMatrixException if this matrix is singular
		Matrix4f inverse() const;

	private:
		float array_[SIZE4][SIZE4];
		friend std::ostream& operator<<(std::ostream&, const Matrix4f&);
	};
}

#endif // MATRIX4F_H
