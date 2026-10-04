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

#include <array>
#include <iostream>
#include <optional>
#include <vector>
#include "Vector3f.h"

namespace vectormatrix
{
	class Matrix4f;

	class Vector4f
	{
	public:

		// Static vectors and point (a new copy is returned each time)
		static Vector4f xAxis();
		static Vector4f yAxis();
		static Vector4f zAxis();
		static Vector4f xOppAxis();
		static Vector4f yOppAxis();
		static Vector4f zOppAxis();
		static Vector4f zeroVector();
		static Vector4f zeroPoint();

		// Constructors
		Vector4f();
		explicit Vector4f(float a);
		Vector4f(float x, float y, float z, float w);
		explicit Vector4f(const float array[4]);
		// Throws VectorArrayWrongSizeException if the array has less than 4 elements
		explicit Vector4f(const std::vector<float>& array);
		// w is set to 0 (vector, not point)
		explicit Vector4f(const Vector3f& v);
		// Vector ab from 2 points a and b (w = 0 if a and b are points)
		Vector4f(const Vector4f& a, const Vector4f& b);
		// Row r of matrix A
		Vector4f(int r, const Matrix4f& A);
		// Column c of matrix A
		Vector4f(const Matrix4f& A, int c);

		// Operators
		Vector4f operator+(const Vector4f& v) const;
		Vector4f& operator+=(const Vector4f& v);
		Vector4f operator-(const Vector4f& v) const;
		Vector4f& operator-=(const Vector4f& v);
		// Add or subtract a Vector3f to x, y, z (w is unchanged)
		Vector4f operator+(const Vector3f& v) const;
		Vector4f operator-(const Vector3f& v) const;
		// Cross product (same as cross(), assuming vectors, w forced to 0)
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
		// Cross product V^W assuming vectors (w forced to 0), cross returns a new vector, crossEquals modifies this vector
		Vector4f cross(const Vector4f& v) const;
		Vector4f& crossEquals(const Vector4f& v);
		// Equality within EPSILON tolerance
		bool operator==(const Vector4f& v) const;
		bool operator!=(const Vector4f& v) const;

		// getter and setter (get and set throw IndexOutOfBoundException if i is out of bound)
		float get(int i) const;
		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;
		// Coordinates of the 3D point (x/w, y/w, z/w)
		float get3DX() const;
		float get3DY() const;
		float get3DZ() const;
		// 3D point (x/w, y/w, z/w), or nothing if w is 0 (Java returns null)
		std::optional<Vector3f> get3DPoint() const;

		void set(int i, float v);
		void set(float x, float y, float z, float w);
		void setX(float v);
		void setY(float v);
		void setZ(float v);
		void setW(float v);

		// Point or vector (w != 0 or w == 0)
		bool isVector() const;
		bool isPoint() const;
		void point();
		void vector();

		// Other methods
		float length() const;
		float lengthSquared() const;
		float distance(const Vector4f& v) const;
		float distanceSquared(const Vector4f& v) const;
		// Normalize this vector (modified) and return it
		Vector4f& normalize();
		Vector3f V3() const;
		std::array<float, 4> toArray() const;
		// Copy the coordinates in dest (at least 4 elements) and return dest
		float* toArray(float* dest) const;

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
