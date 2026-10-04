//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include <iostream>
#include <cmath>
#include <string>
#include "Vector2f.h"
#include "Matrix2f.h"
#include "Exceptions.h"
#include "MathTools.h"

namespace vectormatrix
{
	Vector2f::Vector2f() : x(0), y(0)
	{
	}

	Vector2f::Vector2f(float a) : x(a), y(a)
	{
	}

	Vector2f::Vector2f(float x, float y) : x(x), y(y)
	{
	}

	Vector2f::Vector2f(const float array[2]) : x(array[0]), y(array[1])
	{
	}

	Vector2f::Vector2f(const std::vector<float>& array)
	{
		if (array.size() < 2) throw VectorArrayWrongSizeException("Array passed in parameter of Vector2f constructor is out of bound: " + std::to_string(array.size()));
		x = array[0];
		y = array[1];
	}

	Vector2f Vector2f::operator+(const Vector2f& v) const
	{
		return Vector2f(x + v.x, y + v.y);
	}

	Vector2f& Vector2f::operator+=(const Vector2f& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2f Vector2f::operator-(const Vector2f& v) const
	{
		return Vector2f(x - v.x, y - v.y);
	}

	Vector2f& Vector2f::operator-=(const Vector2f& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2f Vector2f::operator*(const Matrix2f& m) const
	{
		return Vector2f(
			x * m.get(0, 0) + y * m.get(0, 1),
			x * m.get(1, 0) + y * m.get(1, 1));
	}

	Vector2f& Vector2f::operator*=(const Matrix2f& m)
	{
		*this = *this * m;
		return *this;
	}

	Vector2f Vector2f::operator*(float a) const
	{
		return Vector2f(x * a, y * a);
	}

	Vector2f& Vector2f::operator*=(float a)
	{
		x *= a;
		y *= a;
		return *this;
	}

	Vector2f Vector2f::operator/(float a) const
	{
		return Vector2f(x / a, y / a);
	}

	Vector2f& Vector2f::operator/=(float a)
	{
		x /= a;
		y /= a;
		return *this;
	}

	float Vector2f::dot(const Vector2f& v) const
	{
		return x * v.x + y * v.y;
	}

	bool Vector2f::operator==(const Vector2f& v) const
	{
		return MathTools::equals(x, v.x) && MathTools::equals(y, v.y);
	}

	bool Vector2f::operator!=(const Vector2f& v) const
	{
		return !(*this == v);
	}

	float Vector2f::get(int i) const
	{
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		default:
			throw IndexOutOfBoundException("Index out of bound while getting coordinate (" + std::to_string(i) + ") of Vector2f");
		}
	}

	float Vector2f::getX() const
	{
		return x;
	}

	float Vector2f::getY() const
	{
		return y;
	}

	void Vector2f::set(int i, float a)
	{
		switch (i) {
		case 0:
			x = a;
			break;
		case 1:
			y = a;
			break;
		default:
			throw IndexOutOfBoundException("Index out of bound while setting coordinate (" + std::to_string(i) + ") of Vector2f");
		}
	}

	void Vector2f::setX(float v)
	{
		x = v;
	}

	void Vector2f::setY(float v)
	{
		y = v;
	}

	float Vector2f::length() const
	{
		return std::sqrt(x * x + y * y);
	}

	float Vector2f::lengthSquared() const
	{
		return x * x + y * y;
	}

	float Vector2f::distance(const Vector2f& v) const
	{
		return std::sqrt(distanceSquared(v));
	}

	float Vector2f::distanceSquared(const Vector2f& v) const
	{
		float dx = x - v.x, dy = y - v.y;
		return dx * dx + dy * dy;
	}

	Vector2f& Vector2f::normalize()
	{
		float length = this->length();
		x /= length;
		y /= length;
		return *this;
	}

	std::array<float, 2> Vector2f::toArray() const
	{
		return { x, y };
	}

	float* Vector2f::toArray(float* dest) const
	{
		dest[0] = x;
		dest[1] = y;
		return dest;
	}

	// static member function (see declaration)
	Vector2f Vector2f::interpolate(const Vector2f& v1, const Vector2f& v2, float t)
	{
		return v1 * (1 - t) + v2 * t;
	}

	std::ostream& operator<<(std::ostream& strm, const Vector2f& v)
	{
		strm << "Vector2f(" << std::endl;
		strm << v.x << " ";
		strm << v.y << " ";
		strm << std::endl;
		return strm << ")";
	}
}
