//
// MIT License
// Copyright(c) 2021 - 2022 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include <iostream>
#include <math.h>
#include "Vector3f.h"
#include "Matrix3f.h"

namespace vectormatrix
{
	Vector3f::Vector3f()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3f::Vector3f(float a)
	{
		x = a;
		y = a;
		z = a;
	}

	Vector3f::Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3f::Vector3f(float array[3])
	{
		this->x = array[0];
		this->y = array[1];
		this->z = array[2];
	}

	Vector3f Vector3f::operator+(const Vector3f& v)
	{
		Vector3f* r = new Vector3f();
		r->x = this->x + v.x;
		r->y = this->y + v.y;
		r->z = this->z + v.z;

		return *r;
	}

	void Vector3f::operator+=(const Vector3f& v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}

	Vector3f Vector3f::operator-(const Vector3f& v)
	{
		Vector3f* r = new Vector3f();
		r->x = this->x - v.x;
		r->y = this->y - v.y;
		r->z = this->z - v.z;

		return *r;
	}

	void Vector3f::operator-=(const Vector3f& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}

	Vector3f Vector3f::operator*(const Vector3f& v)
	{
		Vector3f* r = new Vector3f();
		r->x = this->y * v.z - this->z * v.y;
		r->y = this->z * v.x - this->x * v.z;
		r->z = this->x * v.y - this->y * v.x;

		return *r;
	}

	Vector3f Vector3f::operator*(const Matrix3f& m)
	{
		Vector3f* r = new Vector3f();
		r->x = this->x * m.get(0, 0) + this->y * m.get(0, 1) + this->z * m.get(0, 2);
		r->y = this->x * m.get(1, 0) + this->y * m.get(1, 1) + this->z * m.get(1, 2);
		r->z = this->x * m.get(2, 0) + this->y * m.get(2, 1) + this->z * m.get(2, 2);

		return *r;
	}

	void Vector3f::operator*=(const Matrix3f& m)
	{
		Vector3f* r = new Vector3f();
		r->x = this->x * m.get(0, 0) + this->y * m.get(0, 1) + this->z * m.get(0, 2);
		r->y = this->x * m.get(1, 0) + this->y * m.get(1, 1) + this->z * m.get(1, 2);
		r->z = this->x * m.get(2, 0) + this->y * m.get(2, 1) + this->z * m.get(2, 2);

		this->x = r->x;
		this->y = r->y;
		this->z = r->z;
	}

	Vector3f Vector3f::operator/(float a)
	{
		Vector3f* vec = new Vector3f();
		vec->x = this->x / a;
		vec->y = this->y / a;
		vec->z = this->z / a;
		return *vec;
	}

	void Vector3f::operator/=(float a)
	{
		this->x /= a;
		this->y /= a;
		this->z /= a;
	}

	Vector3f Vector3f::operator*(float a)
	{
		Vector3f* vec = new Vector3f();
		vec->x = this->x * a;
		vec->y = this->y * a;
		vec->z = this->z * a;
		return *vec;
	}

	void Vector3f::operator*=(float a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
	}

	float Vector3f::dot(const Vector3f& v)
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}


	float Vector3f::get(int i)
	{
		switch (i) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			return NAN;
		}
	}

	float Vector3f::getX()
	{
		return this->x;
	}
	float Vector3f::getY()
	{
		return this->y;
	}
	float Vector3f::getZ()
	{
		return this->z;
	}


	void Vector3f::set(int i, float a)
	{
		switch (i) {
		case 0:
			this->x = a;
			break;
		case 1:
			this->y = a;
			break;
		case 2:
			this->z = a;
			break;
		default:
			break;
		}
	}

	void Vector3f::setX(float v) {
		this->x = v;
	}
	void Vector3f::setY(float v) {
		this->y = v;
	}
	void Vector3f::setZ(float v)
	{
		this->z = v;
	}

	float Vector3f::length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3f Vector3f::normalize()
	{
		float length = this->length();
		this->x /= length;
		this->y /= length;
		this->z /= length;

		return *this;
	}

	Vector4f Vector3f::V4()
	{
		Vector4f* r = new Vector4f(*this);
		return *r;
	}

	// static member function (see declatation)
	Vector3f Vector3f::interpolate(Vector3f& v1, Vector3f& v2, float t) {

		Vector3f* r = new Vector3f();

		*r = v1 * (1 - t) + v2 * t;

		return *r;
	}

	std::ostream& operator<<(std::ostream& strm, const Vector3f& v) {
		strm << "Vector3f(" << std::endl;
		strm << v.x << " ";
		strm << v.y << " ";
		strm << v.z << " ";
		strm << std::endl;
		return strm << ")";
	}
}