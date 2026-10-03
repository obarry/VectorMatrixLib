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
#include "Vector3f.h"

namespace vectormatrix
{
	class Matrix4f;

	class Matrix3f
	{
	public:
		// Constants
		static const int SIZE3 = 3;

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

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);

	private:
		float array_[SIZE3][SIZE3];
		friend std::ostream& operator<<(std::ostream&, const Matrix3f&);
	};
}

#endif // MATRIX3F_H
