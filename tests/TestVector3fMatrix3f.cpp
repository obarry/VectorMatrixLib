//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestVector3Matrix3.java

#include "TestFramework.h"
#include "Vector3f.h"
#include "Matrix3f.h"

using namespace vectormatrix;

TEST(Vector3fMatrix3f, MatrixTimesVector)
{
	float array1[3];
	float array2[3][3];
	for (int i = 0; i < 3; i++)
		array1[i] = (float)(i + 1);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array2[i][j] = (float)(i + j + 1);
	/*
	 * A=[[1.0, 2.0, 3.0]
	 *    [2.0, 3.0, 4.0]
	 *    [3.0, 4.0, 5.0]]
	 */

	Vector3f V1(array1);
	Matrix3f A(array2);
	Vector3f V2 = A * V1;

	CHECK(V2.get(0) == 14.0f && V2.get(1) == 20.0f && V2.get(2) == 26.0f);
}

TEST(Vector3fMatrix3f, MatrixGetVector)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = (float)(i + j + 1);
	/*
	 * A=[[1.0, 2.0, 3.0]
	 *    [2.0, 3.0, 4.0]
	 *    [3.0, 4.0, 5.0]]
	 */

	Matrix3f A(array);
	Vector3f V1 = A.getRow(1); // Second row
	CHECK(V1.get(0) == 2.0f && V1.get(1) == 3.0f && V1.get(2) == 4.0f);

	Vector3f V2 = A.getColumn(2); // Third column
	CHECK(V2.get(0) == 3.0f && V2.get(1) == 4.0f && V2.get(2) == 5.0f);
}
