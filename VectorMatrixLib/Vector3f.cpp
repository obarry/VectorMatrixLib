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
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix3f.h"

namespace vectormatrix
{
	Vector3f::Vector3f() : x(0), y(0), z(0)
	{
	}

	Vector3f::Vector3f(float a) : x(a), y(a), z(a)
	{
	}

	Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	Vector3f::Vector3f(const float array[3]) : x(array[0]), y(array[1]), z(array[2])
	{
	}

	Vector3f Vector3f::operator+(const Vector3f& v) const
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f& Vector3f::operator+=(const Vector3f& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3f Vector3f::operator-(const Vector3f& v) const
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f& Vector3f::operator-=(const Vector3f& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3f Vector3f::operator*(const Vector3f& v) const
	{
		// a=(a1,a2,a3) and b=(b1,b2,b3) then a^b=(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	Vector3f Vector3f::operator*(const Matrix3f& m) const
	{
		return Vector3f(
			x * m.get(0, 0) + y * m.get(0, 1) + z * m.get(0, 2),
			x * m.get(1, 0) + y * m.get(1, 1) + z * m.get(1, 2),
			x * m.get(2, 0) + y * m.get(2, 1) + z * m.get(2, 2));
	}

	Vector3f& Vector3f::operator*=(const Matrix3f& m)
	{
		*this = *this * m;
		return *this;
	}

	Vector3f Vector3f::operator/(float a) const
	{
		return Vector3f(x / a, y / a, z / a);
	}

	Vector3f& Vector3f::operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

	Vector3f Vector3f::operator*(float a) const
	{
		return Vector3f(x * a, y * a, z * a);
	}

	Vector3f& Vector3f::operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	float Vector3f::dot(const Vector3f& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	float Vector3f::get(int i) const
	{
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return NAN;
		}
	}

	float Vector3f::getX() const
	{
		return x;
	}

	float Vector3f::getY() const
	{
		return y;
	}

	float Vector3f::getZ() const
	{
		return z;
	}

	void Vector3f::set(int i, float a)
	{
		switch (i) {
		case 0:
			x = a;
			break;
		case 1:
			y = a;
			break;
		case 2:
			z = a;
			break;
		default:
			break;
		}
	}

	void Vector3f::setX(float v)
	{
		x = v;
	}

	void Vector3f::setY(float v)
	{
		y = v;
	}

	void Vector3f::setZ(float v)
	{
		z = v;
	}

	float Vector3f::length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3f& Vector3f::normalize()
	{
		float length = this->length();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vector4f Vector3f::V4() const
	{
		return Vector4f(*this);
	}

	// static member function (see declaration)
	Vector3f Vector3f::interpolate(const Vector3f& v1, const Vector3f& v2, float t)
	{
		return v1 * (1 - t) + v2 * t;
	}

	std::ostream& operator<<(std::ostream& strm, const Vector3f& v)
	{
		strm << "Vector3f(" << std::endl;
		strm << v.x << " ";
		strm << v.y << " ";
		strm << v.z << " ";
		strm << std::endl;
		return strm << ")";
	}
}
