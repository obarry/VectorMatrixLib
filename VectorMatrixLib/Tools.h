//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef TOOLS_H
#define TOOLS_H

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace vectormatrix
{
	// Linear interpolation helpers (same as Aventura Tools).
	// interpolate(a, b, t) = a*(1-t) + b*t, so t=0 gives a, t=1 gives b,
	// and t outside [0,1] extrapolates on the (ab) line.
	class Tools
	{
	public:
		static Vector4f interpolate(const Vector4f& a, const Vector4f& b, float t)
		{
			return Vector4f::interpolate(a, b, t);
		}

		static Vector3f interpolate(const Vector3f& a, const Vector3f& b, float t)
		{
			return Vector3f::interpolate(a, b, t);
		}

		static Vector2f interpolate(const Vector2f& a, const Vector2f& b, float t)
		{
			return Vector2f::interpolate(a, b, t);
		}

		static double interpolate(double a, double b, double t)
		{
			return a * (1 - t) + b * t;
		}

		static float interpolate(float a, float b, float t)
		{
			return a * (1 - t) + b * t;
		}
	};
}

#endif // TOOLS_H
