//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
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
	public:

		// Constructors
		Vector4f();
		explicit Vector4f(float a);
		Vector4f(float x, float y, float z, float w);
		explicit Vector4f(const float array[4]);
		// w is set to 0 (vector, not point)
		explicit Vector4f(const Vector3f& v);

		// Operators
		Vector4f operator+(const Vector4f& v) const;
		Vector4f& operator+=(const Vector4f& v);
		Vector4f operator-(const Vector4f& v) const;
		Vector4f& operator-=(const Vector4f& v);
		// Cross product (assuming vectors, w forced to 0)
		Vector4f operator*(const Vector4f& v) const;
		// W = A.V (same semantic as Java Vector4.times(Matrix4))
		Vector4f operator*(const Matrix4f& m) const;
		Vector4f& operator*=(const Matrix4f& m);
		Vector4f operator*(float a) const;
		Vector4f& operator*=(float a);
		Vector4f operator/(float a) const;
		Vector4f& operator/=(float a);
		// dot operator cannot use * operator as same signature than operator*(const Vector4f& v) except return type but that is not sufficient
		float dot(const Vector4f& v) const;

		// getter and setter
		float get(int i) const;
		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		void set(int i, float v);
		void setX(float v);
		void setY(float v);
		void setZ(float v);
		void setW(float v);

		// Other methods
		float length() const;
		// Normalize this vector (modified) and return it
		Vector4f& normalize();

		// Static methods
		static Vector4f interpolate(const Vector4f& v1, const Vector4f& v2, float t);

	private:
		float x;
		float y;
		float z;
		float w;
		friend std::ostream& operator<<(std::ostream&, const Vector4f&);
	};
}

#endif // VECTOR4F_H
