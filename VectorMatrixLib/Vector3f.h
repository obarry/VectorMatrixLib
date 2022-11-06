//#pragma once
#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>

namespace vectormatrix
{
	class Vector3f
	{
		friend class Matrix3f;

	public:
		Vector3f();
		Vector3f(float a);
		Vector3f(float x, float y, float z);
		Vector3f(float array[3]);

		Vector3f operator+(const Vector3f& v);
		Vector3f operator-(const Vector3f& v);
		Vector3f operator*(const Vector3f& v);

		float get(int i);
		void set(int i, float v);

		Vector3f times(float a);
		void timesEquals(float a);
		float dot(Vector3f& v);

		float length();
		Vector3f normalize();

	private:
		float x;
		float y;
		float z;
		friend std::ostream& operator<<(std::ostream&, const Vector3f&);
	};
}

#endif VECTOR3F_H