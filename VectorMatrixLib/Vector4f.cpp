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
#include "Vector4f.h"
#include "Exceptions.h"
#include "MathTools.h"
#include "Vector3f.h"
#include "Matrix4f.h"

namespace vectormatrix
{
	Vector4f::Vector4f() : x(0), y(0), z(0), w(0)
	{
	}

	Vector4f::Vector4f(float a) : x(a), y(a), z(a), w(a)
	{
	}

	Vector4f::Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{
	}

	Vector4f::Vector4f(const float array[4]) : x(array[0]), y(array[1]), z(array[2]), w(array[3])
	{
	}

	Vector4f::Vector4f(const Vector3f& v) : x(v.getX()), y(v.getY()), z(v.getZ()), w(0)
	{
	}

	Vector4f Vector4f::operator+(const Vector4f& v) const
	{
		return Vector4f(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	Vector4f& Vector4f::operator+=(const Vector4f& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vector4f Vector4f::operator-(const Vector4f& v) const
	{
		return Vector4f(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vector4f& Vector4f::operator-=(const Vector4f& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	Vector4f Vector4f::operator*(const Vector4f& v) const
	{
		// w = 0: assuming Vector, not Point
		return Vector4f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 0);
	}

	Vector4f Vector4f::operator*(const Matrix4f& m) const
	{
		return Vector4f(
			x * m.get(0, 0) + y * m.get(0, 1) + z * m.get(0, 2) + w * m.get(0, 3),
			x * m.get(1, 0) + y * m.get(1, 1) + z * m.get(1, 2) + w * m.get(1, 3),
			x * m.get(2, 0) + y * m.get(2, 1) + z * m.get(2, 2) + w * m.get(2, 3),
			x * m.get(3, 0) + y * m.get(3, 1) + z * m.get(3, 2) + w * m.get(3, 3));
	}

	Vector4f& Vector4f::operator*=(const Matrix4f& m)
	{
		*this = *this * m;
		return *this;
	}

	Vector4f Vector4f::operator*(float a) const
	{
		return Vector4f(x * a, y * a, z * a, w * a);
	}

	Vector4f& Vector4f::operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;
		return *this;
	}

	Vector4f Vector4f::operator/(float a) const
	{
		return Vector4f(x / a, y / a, z / a, w / a);
	}

	Vector4f& Vector4f::operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
		w /= a;
		return *this;
	}

	float Vector4f::dot(const Vector4f& v) const
	{
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	bool Vector4f::operator==(const Vector4f& v) const
	{
		return MathTools::equals(x, v.x) && MathTools::equals(y, v.y) && MathTools::equals(z, v.z) && MathTools::equals(w, v.w);
	}

	bool Vector4f::operator!=(const Vector4f& v) const
	{
		return !(*this == v);
	}

	float Vector4f::get(int i) const
	{
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			throw IndexOutOfBoundException("Index out of bound while getting coordinate (" + std::to_string(i) + ") of Vector4f");
		}
	}

	float Vector4f::getX() const
	{
		return x;
	}

	float Vector4f::getY() const
	{
		return y;
	}

	float Vector4f::getZ() const
	{
		return z;
	}

	float Vector4f::getW() const
	{
		return w;
	}

	void Vector4f::set(int i, float a)
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
		case 3:
			w = a;
			break;
		default:
			throw IndexOutOfBoundException("Index out of bound while setting coordinate (" + std::to_string(i) + ") of Vector4f");
		}
	}

	void Vector4f::setX(float v)
	{
		x = v;
	}

	void Vector4f::setY(float v)
	{
		y = v;
	}

	void Vector4f::setZ(float v)
	{
		z = v;
	}

	void Vector4f::setW(float v)
	{
		w = v;
	}

	float Vector4f::length() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	Vector4f& Vector4f::normalize()
	{
		float length = this->length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
		return *this;
	}

	// static member function (see declaration)
	Vector4f Vector4f::interpolate(const Vector4f& v1, const Vector4f& v2, float t)
	{
		return v1 * (1 - t) + v2 * t;
	}

	std::ostream& operator<<(std::ostream& strm, const Vector4f& v)
	{
		strm << "Vector4f(" << std::endl;
		strm << v.x << " ";
		strm << v.y << " ";
		strm << v.z << " ";
		strm << v.w << " ";
		strm << std::endl;
		return strm << ")";
	}
}
