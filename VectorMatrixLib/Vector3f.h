//
// MIT License
// Copyright(c) 2021 - 2022 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include "Matrix3f.h"
#include "Vector4f.h"

namespace vectormatrix
{
	class Matrix3f;

	class Vector3f
	{
		friend class Matrix3f; // To allow private members of Vector3f to be accessed in Matrix3f
		friend class Vector4f; // To allow private members of Vector3f to be accessed in Vector4f

	public:

		// Constructors
		Vector3f();
		Vector3f(float a);
		Vector3f(float x, float y, float z);
		Vector3f(float array[3]);

		// Operators
		Vector3f operator+(const Vector3f& v);
		void operator+=(const Vector3f& v);
		Vector3f operator-(const Vector3f& v);
		void operator-=(const Vector3f& v);
		Vector3f operator*(const Vector3f& v);
		Vector3f operator*(const Matrix3f& m);
		void operator*=(const Matrix3f& m);
		Vector3f operator*(float a);
		void operator*=(float a);
		Vector3f operator/(float a);
		void operator/=(float a);
		// dot operator cannot use * operator as same signature than operator*(const Vector4f& v) except return type but that is not sufficient
		float dot(const Vector3f& v);

		// getter and setter
		float get(int i);
		float getX();
		float getY();
		float getZ();

		// Other methods
		void set(int i, float v);
		void setX(float v);
		void setY(float v);
		void setZ(float v);

		// Other methods
		float length();
		Vector3f normalize();
		Vector4f V4();

		// Static methods
		static Vector3f interpolate(Vector3f& v1, Vector3f& v2, float t);

	private:
		float x;
		float y;
		float z;
		friend std::ostream& operator<<(std::ostream&, const Vector3f&);
	};
}

#endif VECTOR3F_H