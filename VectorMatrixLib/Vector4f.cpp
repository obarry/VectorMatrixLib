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
	Vector4f Vector4f::xAxis()
	{
		return Vector4f(1, 0, 0, 0);
	}

	Vector4f Vector4f::yAxis()
	{
		return Vector4f(0, 1, 0, 0);
	}

	Vector4f Vector4f::zAxis()
	{
		return Vector4f(0, 0, 1, 0);
	}

	Vector4f Vector4f::xOppAxis()
	{
		return Vector4f(-1, 0, 0, 0);
	}

	Vector4f Vector4f::yOppAxis()
	{
		return Vector4f(0, -1, 0, 0);
	}

	Vector4f Vector4f::zOppAxis()
	{
		return Vector4f(0, 0, -1, 0);
	}

	Vector4f Vector4f::zeroVector()
	{
		return Vector4f(0, 0, 0, 0);
	}

	Vector4f Vector4f::zeroPoint()
	{
		return Vector4f(0, 0, 0, 1);
	}

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

	Vector4f::Vector4f(const std::vector<float>& array)
	{
		if (array.size() < 4) throw VectorArrayWrongSizeException("Array passed in parameter of Vector4f constructor is out of bound: " + std::to_string(array.size()));
		x = array[0];
		y = array[1];
		z = array[2];
		w = array[3];
	}

	Vector4f::Vector4f(const Vector3f& v) : x(v.getX()), y(v.getY()), z(v.getZ()), w(0)
	{
	}

	Vector4f::Vector4f(const Vector4f& a, const Vector4f& b) : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z), w(b.w - a.w)
	{
	}

	Vector4f::Vector4f(int r, const Matrix4f& A) : x(A.get(r, 0)), y(A.get(r, 1)), z(A.get(r, 2)), w(A.get(r, 3))
	{
	}

	Vector4f::Vector4f(const Matrix4f& A, int c) : x(A.get(0, c)), y(A.get(1, c)), z(A.get(2, c)), w(A.get(3, c))
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

	Vector4f Vector4f::operator+(const Vector3f& v) const
	{
		return Vector4f(x + v.getX(), y + v.getY(), z + v.getZ(), w);
	}

	Vector4f Vector4f::operator-(const Vector3f& v) const
	{
		return Vector4f(x - v.getX(), y - v.getY(), z - v.getZ(), w);
	}

	Vector4f Vector4f::operator*(const Vector4f& v) const
	{
		return cross(v);
	}

	Vector4f Vector4f::cross(const Vector4f& v) const
	{
		// w = 0: assuming Vector, not Point
		return Vector4f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 0);
	}

	Vector4f& Vector4f::crossEquals(const Vector4f& v)
	{
		*this = cross(v);
		return *this;
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

	void Vector4f::set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
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

	float Vector4f::get3DX() const
	{
		return x / w;
	}

	float Vector4f::get3DY() const
	{
		return y / w;
	}

	float Vector4f::get3DZ() const
	{
		return z / w;
	}

	std::optional<Vector3f> Vector4f::get3DPoint() const
	{
		if (w != 0)
			return Vector3f(x / w, y / w, z / w);
		return std::nullopt;
	}

	bool Vector4f::isVector() const
	{
		return w == 0;
	}

	bool Vector4f::isPoint() const
	{
		return w != 0;
	}

	void Vector4f::point()
	{
		w = 1;
	}

	void Vector4f::vector()
	{
		w = 0;
	}

	float Vector4f::length() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	float Vector4f::lengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	float Vector4f::distance(const Vector4f& v) const
	{
		return std::sqrt(distanceSquared(v));
	}

	float Vector4f::distanceSquared(const Vector4f& v) const
	{
		float dx = x - v.x, dy = y - v.y, dz = z - v.z, dw = w - v.w;
		return dx * dx + dy * dy + dz * dz + dw * dw;
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

	Vector3f Vector4f::V3() const
	{
		return Vector3f(*this);
	}

	std::array<float, 4> Vector4f::toArray() const
	{
		return { x, y, z, w };
	}

	float* Vector4f::toArray(float* dest) const
	{
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
		dest[3] = w;
		return dest;
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
