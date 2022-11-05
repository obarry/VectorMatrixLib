#pragma once
#include "Matrix3f.h"
#include "Vector4f.h"
#include <iostream>

#ifndef MATRIX4F_H
#define MATRIX4F_H

namespace vectormatrix
{
	class Matrix4f
	{
	public:
		Matrix4f();
		Matrix4f(float a);
		Matrix4f(float array[4][4]);
		Matrix4f(Matrix3f& b);
		float get(int x, int y);
		void set(int x, int y, float a);
		Matrix4f times(Matrix4f& m);
		void times(float f);
		Vector4f times(Vector4f& v);

	private:
		float array_[4][4];
		friend std::ostream& operator<<(std::ostream&, const Matrix4f&);
	};
}
#endif MATRIX4F_H
