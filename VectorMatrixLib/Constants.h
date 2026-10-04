//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace vectormatrix
{
	// Sizes of the vectors and matrices
	constexpr int SIZE_2 = 2;
	constexpr int SIZE_3 = 3;
	constexpr int SIZE_4 = 4;

	// Indices of the axes
	constexpr int X_AXIS = 0;
	constexpr int Y_AXIS = 1;
	constexpr int Z_AXIS = 2;

	// Tolerance used to compare floats (same value as Aventura Constants.EPSILON)
	constexpr float EPSILON = 1.0E-4f;
}

#endif // CONSTANTS_H
