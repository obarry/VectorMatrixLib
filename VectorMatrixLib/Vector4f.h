//#pragma once

#ifndef VECTOR4F_H
#define VECTOR4F_H
#include <iostream>

namespace vectormatrix
{
	class Vector4f
	{
	public:
		Vector4f();
		Vector4f(float a);
		Vector4f(float x, float y, float z, float w);
		Vector4f(float array[4]);

		Vector4f operator+(const Vector4f& v);
		Vector4f operator-(const Vector4f& v);
		Vector4f operator*(const Vector4f& v);


		float get(int i);
		void set(int i, float v);
		Vector4f times(float a);
		void timesEquals(float a);
		float dot(Vector4f& v);

		float length();
		Vector4f normalize();

	private:
		float x;
		float y;
		float z;
		float w;
		friend std::ostream& operator<<(std::ostream&, const Vector4f&);

	};
}

#endif VECTOR4F_H