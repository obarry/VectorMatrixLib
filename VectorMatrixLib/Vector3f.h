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

#include <array>
#include <iostream>
#include <vector>

namespace vectormatrix
{
	class Matrix3f;
	class Vector4f;

	class Vector3f
	{
	public:

		// Static vectors (a new copy is returned each time)
		static Vector3f xAxis();
		static Vector3f yAxis();
		static Vector3f zAxis();
		static Vector3f xOppAxis();
		static Vector3f yOppAxis();
		static Vector3f zOppAxis();
		static Vector3f zeroVector();

		// Constructors
		Vector3f();
		explicit Vector3f(float a);
		Vector3f(float x, float y, float z);
		explicit Vector3f(const float array[3]);
		// Throws VectorArrayWrongSizeException if the array has less than 3 elements
		explicit Vector3f(const std::vector<float>& array);
		// The 3 first coordinates of v (w is ignored)
		explicit Vector3f(const Vector4f& v);
		// Vector ab from 2 points a and b (w is ignored)
		Vector3f(const Vector4f& a, const Vector4f& b);
		// Row r of matrix A
		Vector3f(int r, const Matrix3f& A);
		// Column c of matrix A
		Vector3f(const Matrix3f& A, int c);

		// Operators
		Vector3f operator+(const Vector3f& v) const;
		Vector3f& operator+=(const Vector3f& v);
		Vector3f operator-(const Vector3f& v) const;
		Vector3f& operator-=(const Vector3f& v);
		// Cross product (same as cross())
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
		// Cross product V^W, cross returns a new vector, crossEquals modifies this vector
		Vector3f cross(const Vector3f& v) const;
		Vector3f& crossEquals(const Vector3f& v);
		// Equality within EPSILON tolerance
		bool operator==(const Vector3f& v) const;
		bool operator!=(const Vector3f& v) const;

		// getter and setter (get and set throw IndexOutOfBoundException if i is out of bound)
		float get(int i) const;
		float getX() const;
		float getY() const;
		float getZ() const;

		void set(int i, float v);
		void set(float nx, float ny, float nz);
		void setX(float v);
		void setY(float v);
		void setZ(float v);

		// Other methods
		float length() const;
		float lengthSquared() const;
		float distance(const Vector3f& v) const;
		float distanceSquared(const Vector3f& v) const;
		// Normalize this vector (modified) and return it
		Vector3f& normalize();
		Vector4f V4() const;
		std::array<float, 3> toArray() const;
		// Copy the coordinates in dest (at least 3 elements) and return dest
		float* toArray(float* dest) const;

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
