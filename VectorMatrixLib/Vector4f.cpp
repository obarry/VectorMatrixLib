#include "Vector4f.h"

namespace vectormatrix
{
	Vector4f::Vector4f()
	{
		x = 0;
		y = 0;
		z = 0;
		t = 0;
	}

	Vector4f::Vector4f(float a)
	{
		x = a;
		y = a;
		z = a;
		t = a;
	}

	Vector4f::Vector4f(float x, float y, float z, float t)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->t = t;
	}

	Vector4f::Vector4f(float array[4])
	{
		this->x = array[0];
		this->y = array[1];
		this->z = array[2];
		this->t = array[3];
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
			return this->t;
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
			this->t = a;
		default:
			break;
		}
	}

	Vector4f Vector4f::times(float a)
	{
		Vector4f* vec = new Vector4f;
		vec->x = this->x * a;
		vec->y = this->y * a;
		vec->z = this->z * a;
		vec->t = this->t * a;
		return *vec;
	}

	void Vector4f::timesEquals(float a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
		this->t *= a;
	}

	std::ostream& operator<<(std::ostream& strm, const Vector4f& v) {
		strm << "Vector4f(" << std::endl;
		strm << v.x << " ";
		strm << v.y << " ";
		strm << v.z << " ";
		strm << v.t << " ";
		strm << std::endl;
		return strm << ")";
	}
}