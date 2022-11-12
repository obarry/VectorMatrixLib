//
// MIT License
// Copyright(c) 2021 - 2022 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <iostream>

namespace vectormatrix
{
	class Matrix4f;
	class Vector3f;

	class Vector4f
	{
		friend class Matrix4f; // To allow private members of Vector4f to be accessed in Matrix4f

	public:

		// Constructors
		Vector4f();
		Vector4f(float a);
		Vector4f(float x, float y, float z, float w);
		Vector4f(float array[4]);
		Vector4f(Vector3f v);

		// Operators
		void operator=(const Vector4f& v);
		Vector4f operator+(const Vector4f& v);
		void operator+=(const Vector4f& v);
		Vector4f operator-(const Vector4f& v);
		void operator-=(const Vector4f& v);
		Vector4f operator*(const Vector4f& v);
		Vector4f operator*(const Matrix4f& m);
		void operator*=(const Matrix4f& m);
		Vector4f operator*(float a);
		void operator*=(float a);
		Vector4f operator/(float a);
		void operator/=(float a);
		// dot operator cannot use * operator as same signature than operator*(const Vector4f& v) except return type but that is not sufficient
		float dot(const Vector4f& v);

		// getter and setter
		float get(int i);
		float getX();
		float getY();
		float getZ();
		float getW();

		void set(int i, float v);
		void setX(float v);
		void setY(float v);
		void setZ(float v);
		void setW(float v);

		// Other methods
		float length();
		Vector4f normalize();

		// Static methods
		static Vector4f interpolate(Vector4f& v1, Vector4f& v2, float t);

	private:
		float x;
		float y;
		float z;
		float w;
		friend std::ostream& operator<<(std::ostream&, const Vector4f&);

	};
}

#endif VECTOR4F_H