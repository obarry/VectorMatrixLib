#pragma once
#include "Matrix4f.h"
#include <iostream>

#ifndef MATRIX3F_H
#define MATRIX3F_H

namespace vectormatrix
{
	class Matrix3f
	{
	public:
		Matrix3f();
		Matrix3f(float a);
		Matrix3f(float array[3][3]);
		Matrix3f(Matrix4f& b);
		float get(int x, int y);
		void set(int x, int y, float a);
		Matrix3f times(Matrix3f& m);
		void times(float f);

	private:
		float array_[3][3];
		friend std::ostream& operator<<(std::ostream&, const Matrix3f&);
	};
}

#endif MATRIX3F_H