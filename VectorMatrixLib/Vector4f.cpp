#include <math.h>
#include "Vector4f.h"
#include "Matrix4f.h"

namespace vectormatrix
{
	Vector4f::Vector4f()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4f::Vector4f(float a)
	{
		x = a;
		y = a;
		z = a;
		w = a;
	}

	Vector4f::Vector4f(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4f::Vector4f(float array[4])
	{
		this->x = array[0];
		this->y = array[1];
		this->z = array[2];
		this->w = array[3];
	}

	Vector4f Vector4f::operator+(const Vector4f& v)
	{
		Vector4f r;
		r.x = this->x + v.x;
		r.y = this->y + v.y;
		r.z = this->z + v.z;
		r.w = this->w + v.w;

		return r;
	}

	Vector4f Vector4f::operator-(const Vector4f& v)
	{
		Vector4f r;
		r.x = this->x - v.x;
		r.y = this->y - v.y;
		r.z = this->z - v.z;
		r.w = this->w - v.w;

		return r;
	}

	Vector4f Vector4f::operator*(const Vector4f& v)
	{
		Vector4f r;
		r.x = this->y * v.z - this->z * v.y;
		r.y = this->z * v.x - this->x * v.z;
		r.z = this->x * v.y - this->y * v.x;
		r.w = 0; // Assuming Vector, not Point

		return r;
	}

	Vector4f Vector4f::operator*(Matrix4f& m)
	{
		Vector4f* r = new Vector4f();
		r->x = this->x * m.get(0, 0) + this->y * m.get(0, 1) + this->z * m.get(0, 2) + this->w * m.get(0, 3);
		r->y = this->x * m.get(1, 0) + this->y * m.get(1, 1) + this->z * m.get(1, 2) + this->w * m.get(1, 3);
		r->z = this->x * m.get(2, 0) + this->y * m.get(2, 1) + this->z * m.get(2, 2) + this->w * m.get(2, 3);
		r->w = this->x * m.get(3, 0) + this->y * m.get(3, 1) + this->z * m.get(3, 2) + this->w * m.get(3, 3);

		return *r;
	}

	void Vector4f::operator*=(Matrix4f& m)
	{
		Vector4f* r = new Vector4f();
		r->x = this->x * m.get(0, 0) + this->y * m.get(0, 1) + this->z * m.get(0, 2) + this->w * m.get(0, 3);
		r->y = this->x * m.get(1, 0) + this->y * m.get(1, 1) + this->z * m.get(1, 2) + this->w * m.get(1, 3);
		r->z = this->x * m.get(2, 0) + this->y * m.get(2, 1) + this->z * m.get(2, 2) + this->w * m.get(2, 3);
		r->w = this->x * m.get(3, 0) + this->y * m.get(3, 1) + this->z * m.get(3, 2) + this->w * m.get(3, 3);

		this->x = r->x;
		this->y = r->y;
		this->z = r->z;
		this->w = r->w;
	}

	Vector4f Vector4f::operator*(float a)
	{
		Vector4f* vec = new Vector4f;
		vec->x = this->x * a;
		vec->y = this->y * a;
		vec->z = this->z * a;
		vec->w = this->w * a;
		return *vec;
	}

	void Vector4f::operator*=(float a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
		this->w *= a;
	}

	float Vector4f::operator*(Vector4f& v)
	{
		return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
	}


	float Vector4f::get(int i)
	{
		switch (i) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		default:
			return NAN;
		}
	}

	void Vector4f::set(int i, float a)
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
		case 3:
			this->w = a;
		default:
			break;
		}
	}

	//Vector4f Vector4f::times(float a)
	//{
	//	Vector4f* vec = new Vector4f;
	//	vec->x = this->x * a;
	//	vec->y = this->y * a;
	//	vec->z = this->z * a;
	//	vec->w = this->w * a;
	//	return *vec;
	//}

	//void Vector4f::timesEquals(float a)
	//{
	//	this->x *= a;
	//	this->y *= a;
	//	this->z *= a;
	//	this->w *= a;
	//}

	//Vector4f Vector4f::times(Matrix4f& m)
	//{
	//	Vector4f* r = new Vector4f();
	//	r->x = this->x * m.get(0, 0) + this->y * m.get(0, 1) + this->z * m.get(0, 2) + this->w * m.get(0, 3);
	//	r->y = this->x * m.get(1, 0) + this->y * m.get(1, 1) + this->z * m.get(1, 2) + this->w * m.get(1, 3);
	//	r->z = this->x * m.get(2, 0) + this->y * m.get(2, 1) + this->z * m.get(2, 2) + this->w * m.get(2, 3);
	//	r->w = this->x * m.get(3, 0) + this->y * m.get(3, 1) + this->z * m.get(3, 2) + this->w * m.get(3, 3);

	//	return *r;
	//}


	//float Vector4f::dot(Vector4f& v)
	//{
	//	return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
	//}

	float Vector4f::length()
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	Vector4f Vector4f::normalize()
	{
		float length = this->length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
		this->w /= length;

		return *this;
	}

	std::ostream& operator<<(std::ostream& strm, const Vector4f& v) {
		strm << "Vector4f(" << std::endl;
		strm << v.x << " ";
		strm << v.y << " ";
		strm << v.z << " ";
		strm << v.w << " ";
		strm << std::endl;
		return strm << ")";
	}
}