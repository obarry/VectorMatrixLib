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
#include "Vector4f.h"

namespace vectormatrix
{
	class Matrix3f;

	class Matrix4f
	{
	public:
		// Constants
		static const int SIZE4 = 4;

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

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);

	private:
		float array_[SIZE4][SIZE4];
		friend std::ostream& operator<<(std::ostream&, const Matrix4f&);
	};
}

#endif // MATRIX4F_H
