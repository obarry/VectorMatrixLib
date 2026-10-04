//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>

namespace vectormatrix
{
	class Matrix3f;
	class Vector4f;

	class Vector3f
	{
	public:

		// Constructors
		Vector3f();
		explicit Vector3f(float a);
		Vector3f(float x, float y, float z);
		explicit Vector3f(const float array[3]);

		// Operators
		Vector3f operator+(const Vector3f& v) const;
		Vector3f& operator+=(const Vector3f& v);
		Vector3f operator-(const Vector3f& v) const;
		Vector3f& operator-=(const Vector3f& v);
		// Cross product
		Vector3f operator*(const Vector3f& v) const;
		// W = A.V (same semantic as Java Vector3.times(Matrix3))
		Vector3f operator*(const Matrix3f& m) const;
		Vector3f& operator*=(const Matrix3f& m);
		Vector3f operator*(float a) const;
		Vector3f& operator*=(float a);
		Vector3f operator/(float a) const;
		Vector3f& operator/=(float a);
		// dot operator cannot use * operator as same signature than operator*(const Vector3f& v) except return type but that is not sufficient
		float dot(const Vector3f& v) const;
		// Equality within EPSILON tolerance
		bool operator==(const Vector3f& v) const;
		bool operator!=(const Vector3f& v) const;

		// getter and setter (get and set throw IndexOutOfBoundException if i is out of bound)
		float get(int i) const;
		float getX() const;
		float getY() const;
		float getZ() const;

		void set(int i, float v);
		void setX(float v);
		void setY(float v);
		void setZ(float v);

		// Other methods
		float length() const;
		// Normalize this vector (modified) and return it
		Vector3f& normalize();
		Vector4f V4() const;

		// Static methods
		static Vector3f interpolate(const Vector3f& v1, const Vector3f& v2, float t);

	private:
		float x;
		float y;
		float z;
		friend std::ostream& operator<<(std::ostream&, const Vector3f&);
	};
}

#endif // VECTOR3F_H
