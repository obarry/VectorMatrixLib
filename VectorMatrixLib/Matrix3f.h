#pragma once
//#ifndef MATRIX3F_H
//#define MATRIX3F_H

#include <iostream>
#include "Matrix4f.h"
#include "Vector3f.h"

namespace vectormatrix
{
	class Matrix4f;

	class Matrix3f
	{
	public:
		Matrix3f();
		Matrix3f(float a);
		Matrix3f(float array[3][3]);
		Matrix3f(vectormatrix::Matrix4f& b);

		Matrix3f operator+(const Matrix3f& m);
		Matrix3f operator-(const Matrix3f& m);

		float get(int x, int y);
		void set(int x, int y, float a);
		Matrix3f times(Matrix3f& m);
		void times(float f);
		Vector3f times(vectormatrix::Vector3f& v);

	private:
		float array_[3][3];
		friend std::ostream& operator<<(std::ostream&, const Matrix3f&);
	};
}

//#endif MATRIX3F_H