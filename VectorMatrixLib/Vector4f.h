#pragma once
#include <iostream>

#ifndef VECTOR4F_H
#define VECTOR4F_H

namespace vectormatrix
{
	class Vector4f
	{
	public:
		Vector4f();
		Vector4f(float a);
		Vector4f(float x, float y, float z, float t);
		Vector4f(float array[4]);
		float get(int i);
		void set(int i, float v);
		Vector4f times(float a);
		void timesEquals(float a);

	private:
		float x;
		float y;
		float z;
		float t;
		friend std::ostream& operator<<(std::ostream&, const Vector4f&);

	};
}

#endif VECTOR4F_H