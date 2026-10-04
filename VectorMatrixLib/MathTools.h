//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef MATHTOOLS_H
#define MATHTOOLS_H

#include <cmath>
#include "Constants.h"

namespace vectormatrix
{
	class MathTools
	{
	public:
		// true if a and b are equal within EPSILON tolerance
		static bool equals(float a, float b)
		{
			return std::fabs(a - b) <= EPSILON;
		}
	};
}

#endif // MATHTOOLS_H
