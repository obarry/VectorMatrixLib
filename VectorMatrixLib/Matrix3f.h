//
// MIT License
// Copyright(c) 2021 - 2023 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef MATRIX3F_H
#define MATRIX3F_H

#include <iostream>
#include "Matrix4f.h"
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
		Matrix3f(float a);
		Matrix3f(float array[SIZE3][SIZE3]);
		Matrix3f(const Matrix3f& m);
		Matrix3f(vectormatrix::Matrix4f& b);

		// Operators
		void operator=(const Matrix3f& m);
		Matrix3f operator+(const Matrix3f& m);
		void operator+=(const Matrix3f& m);
		Matrix3f operator-(const Matrix3f& m);
		void operator-=(const Matrix3f& m);
		Matrix3f operator*(const Matrix3f& m);
		void operator*=(const Matrix3f& m);
		Matrix4f operator*(float a);
		void operator*=(float a);
		Vector3f operator*(Vector3f& v);

		// Getters and Setters
		float get(int x, int y) const;
		void set(int x, int y, float a);

	private:
		float array_[SIZE3][SIZE3];
		friend std::ostream& operator<<(std::ostream&, const vectormatrix::Matrix3f&);
	};
}

#endif MATRIX3F_H