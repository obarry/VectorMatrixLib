#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include "Matrix3f.h"
#include "Vector4f.h"

namespace vectormatrix
{
	class Matrix3f;

	class Vector3f
	{
		friend class Matrix3f;
		friend class Vector4f;

	public:
		Vector3f();
		Vector3f(float a);
		Vector3f(float x, float y, float z);
		Vector3f(float array[3]);

		Vector3f operator+(const Vector3f& v);
		Vector3f operator-(const Vector3f& v);
		Vector3f operator*(const Vector3f& v);
		Vector3f operator*(Matrix3f& m);
		void operator*=(Matrix3f& m);
		Vector3f operator*(float a);
		void operator*=(float a);
		float operator*(Vector3f& v);

		float get(int i);
		float getX();
		float getY();
		float getZ();
		void set(int i, float v);
		void setX(float v);
		void setY(float v);
		void setZ(float v);

		float length();
		Vector3f normalize();
		Vector4f V4();

	private:
		float x;
		float y;
		float z;
		friend std::ostream& operator<<(std::ostream&, const Vector3f&);
	};
}

#endif VECTOR3F_H