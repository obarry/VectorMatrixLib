#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <iostream>

namespace vectormatrix
{
	class Matrix4f;

	class Vector4f
	{
		friend class Matrix4f;

	public:
		Vector4f();
		Vector4f(float a);
		Vector4f(float x, float y, float z, float w);
		Vector4f(float array[4]);

		Vector4f operator+(const Vector4f& v);
		Vector4f operator-(const Vector4f& v);
		Vector4f operator*(const Vector4f& v);
		Vector4f operator*(Matrix4f& m);
		void operator*=(Matrix4f& m);
		Vector4f operator*(float a);
		void operator*=(float a);
		float operator*(Vector4f& v);

		float get(int i);
		void set(int i, float v);
		//float dot(Vector4f& v);

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