//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <array>
#include <iostream>
#include <vector>

namespace vectormatrix
{
	class Matrix2f;

	class Vector2f
	{
	public:

		// Constructors
		Vector2f();
		explicit Vector2f(float a);
		Vector2f(float x, float y);
		explicit Vector2f(const float array[2]);
		// Throws VectorArrayWrongSizeException if the array has less than 2 elements
		explicit Vector2f(const std::vector<float>& array);

		// Operators
		Vector2f operator+(const Vector2f& v) const;
		Vector2f& operator+=(const Vector2f& v);
		Vector2f operator-(const Vector2f& v) const;
		Vector2f& operator-=(const Vector2f& v);
		// W = A.V (same semantic as Java Vector2.times(Matrix2))
		Vector2f operator*(const Matrix2f& m) const;
		Vector2f& operator*=(const Matrix2f& m);
		Vector2f operator*(float a) const;
		Vector2f& operator*=(float a);
		Vector2f operator/(float a) const;
		Vector2f& operator/=(float a);
		float dot(const Vector2f& v) const;
		// Equality within EPSILON tolerance
		bool operator==(const Vector2f& v) const;
		bool operator!=(const Vector2f& v) const;

		// getter and setter (get and set throw IndexOutOfBoundException if i is out of bound)
		float get(int i) const;
		float getX() const;
		float getY() const;

		void set(int i, float v);
		void setX(float v);
		void setY(float v);

		// Other methods
		float length() const;
		float lengthSquared() const;
		float distance(const Vector2f& v) const;
		float distanceSquared(const Vector2f& v) const;
		// Normalize this vector (modified) and return it
		Vector2f& normalize();
		std::array<float, 2> toArray() const;
		// Copy the coordinates in dest (at least 2 elements) and return dest
		float* toArray(float* dest) const;

		// Static methods
		static Vector2f interpolate(const Vector2f& v1, const Vector2f& v2, float t);

	private:
		float x;
		float y;
		friend std::ostream& operator<<(std::ostream&, const Vector2f&);
	};
}

#endif // VECTOR2F_H
