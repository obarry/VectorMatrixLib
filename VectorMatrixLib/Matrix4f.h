//
// MIT License
// Copyright(c) 2021 - 2022 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <iostream>
#include "Matrix3f.h"
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
		Matrix4f(float a);
		Matrix4f(float array[SIZE4][SIZE4]);
		Matrix4f(const Matrix4f& m);
		Matrix4f(vectormatrix::Matrix3f& b);

		// Operators
		void operator=(const Matrix4f& m);
		Matrix4f operator+(const Matrix4f& m);
		void operator+=(const Matrix4f& m);
		Matrix4f operator-(const Matrix4f& m);
		void operator-=(const Matrix4f& m);
		Matrix4f operator*(const Matrix4f& m);
		void operator*=(const Matrix4f& m);
		Matrix4f operator*(float a);
		void operator*=(float a);
		Vector4f operator*(Vector4f& v);

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);

	private:
		float array_[SIZE4][SIZE4];
		friend std::ostream& operator<<(std::ostream&, const Matrix4f&);
	};
}
#endif MATRIX4F_H

