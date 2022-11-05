#include "Vector3f.h"

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

	Vector3f Vector3f::times(float a)
	{
		Vector3f* vec = new Vector3f;
		vec->x = this->x * a;
		vec->y = this->y * a;
		vec->z = this->z * a;
		return *vec;
	}

	void Vector3f::timesEquals(float a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
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