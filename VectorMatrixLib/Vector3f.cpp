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
#include "Vector3f.h"
#include "Exceptions.h"
#include "MathTools.h"
#include "Vector4f.h"
#include "Matrix3f.h"

namespace vectormatrix
{
	Vector3f Vector3f::xAxis()
	{
		return Vector3f(1, 0, 0);
	}

	Vector3f Vector3f::yAxis()
	{
		return Vector3f(0, 1, 0);
	}

	Vector3f Vector3f::zAxis()
	{
		return Vector3f(0, 0, 1);
	}

	Vector3f Vector3f::xOppAxis()
	{
		return Vector3f(-1, 0, 0);
	}

	Vector3f Vector3f::yOppAxis()
	{
		return Vector3f(0, -1, 0);
	}

	Vector3f Vector3f::zOppAxis()
	{
		return Vector3f(0, 0, -1);
	}

	Vector3f Vector3f::zeroVector()
	{
		return Vector3f(0, 0, 0);
	}

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

	Vector3f::Vector3f(const std::vector<float>& array)
	{
		if (array.size() < 3) throw VectorArrayWrongSizeException("Array passed in parameter of Vector3f constructor is out of bound: " + std::to_string(array.size()));
		x = array[0];
		y = array[1];
		z = array[2];
	}

	Vector3f::Vector3f(const Vector4f& v) : x(v.getX()), y(v.getY()), z(v.getZ())
	{
	}

	Vector3f::Vector3f(const Vector4f& a, const Vector4f& b) : x(b.getX() - a.getX()), y(b.getY() - a.getY()), z(b.getZ() - a.getZ())
	{
	}

	Vector3f::Vector3f(int r, const Matrix3f& A) : x(A.get(r, 0)), y(A.get(r, 1)), z(A.get(r, 2))
	{
	}

	Vector3f::Vector3f(const Matrix3f& A, int c) : x(A.get(0, c)), y(A.get(1, c)), z(A.get(2, c))
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
		return cross(v);
	}

	Vector3f Vector3f::cross(const Vector3f& v) const
	{
		// a=(a1,a2,a3) and b=(b1,b2,b3) then a^b=(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	Vector3f& Vector3f::crossEquals(const Vector3f& v)
	{
		*this = cross(v);
		return *this;
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

	bool Vector3f::operator==(const Vector3f& v) const
	{
		return MathTools::equals(x, v.x) && MathTools::equals(y, v.y) && MathTools::equals(z, v.z);
	}

	bool Vector3f::operator!=(const Vector3f& v) const
	{
		return !(*this == v);
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
			throw IndexOutOfBoundException("Index out of bound while getting coordinate (" + std::to_string(i) + ") of Vector3f");
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
			throw IndexOutOfBoundException("Index out of bound while setting coordinate (" + std::to_string(i) + ") of Vector3f");
		}
	}

	void Vector3f::set(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
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

	float Vector3f::lengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	float Vector3f::distance(const Vector3f& v) const
	{
		return std::sqrt(distanceSquared(v));
	}

	float Vector3f::distanceSquared(const Vector3f& v) const
	{
		float dx = x - v.x, dy = y - v.y, dz = z - v.z;
		return dx * dx + dy * dy + dz * dz;
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

	std::array<float, 3> Vector3f::toArray() const
	{
		return { x, y, z };
	}

	float* Vector3f::toArray(float* dest) const
	{
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
		return dest;
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
