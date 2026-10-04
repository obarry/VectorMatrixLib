//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestGaussJordanSolver.java

#include "TestFramework.h"
#include "GaussJordanSolver.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(GaussJordanSolver, PivotSelection_picksTrueMaxAbsRow_regression)
{
	// Column 0 has abs values [2, 5, 1] starting at pivot row 0: row 1 (value 5) must be selected,
	// not row 0 itself by default (this was the bug: the search never compared against the pivot row).
	const float m[3][3] = {
		{ 2.0f, 1.0f, 1.0f },
		{ 5.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	};
	int chosen = GaussJordanSolver::indiceOfMaxRowInColumn(m, 0, 0);
	CHECK_EQUAL(chosen, 1);

	// And when the pivot row already holds the max value, it must be correctly kept (not overlooked).
	const float m2[3][3] = {
		{ 9.0f, 1.0f, 1.0f },
		{ 5.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	};
	int chosen2 = GaussJordanSolver::indiceOfMaxRowInColumn(m2, 0, 0);
	CHECK_EQUAL(chosen2, 0);
}

TEST(GaussJordanSolver, PivotSelection_searchStartsAtGivenPivot)
{
	const float m[4][4] = {
		{ 9.0f, 1.0f, 1.0f, 1.0f },
		{ 5.0f, 1.0f, 1.0f, 1.0f },
		{ 7.0f, 1.0f, 1.0f, 1.0f },
		{ 2.0f, 1.0f, 1.0f, 1.0f }
	};
	// Starting the search at pivot=2: only rows 2 and 3 are candidates (values 7 and 2), row 2 wins,
	// even though rows 0 and 1 (values 9 and 5) hold larger values overall.
	int chosen = GaussJordanSolver::indiceOfMaxRowInColumn(m, 0, 2);
	CHECK_EQUAL(chosen, 2);
}

TEST(GaussJordanSolver, Invert_3x3_matchesIdentityRoundTrip)
{
	const float a[3][3] = {
		{ 4.0f, 7.0f, 2.0f },
		{ 3.0f, 5.0f, 1.0f },
		{ 2.0f, 3.0f, 1.0f }
	};
	float inv[3][3];
	GaussJordanSolver::invert(a, inv, 1.0E-4f);
	Matrix3f A(a);
	Matrix3f invA(inv);
	CHECK(A * invA == Matrix3f::identity());
}

TEST(GaussJordanSolver, Invert_4x4_matchesIdentityRoundTrip)
{
	const float a[4][4] = {
		{ 2.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 3.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 4.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f }
	};
	float inv[4][4];
	GaussJordanSolver::invert(a, inv, 1.0E-4f);
	Matrix4f A(a);
	Matrix4f invA(inv);
	CHECK(A * invA == Matrix4f::identity());
}

TEST(GaussJordanSolver, Invert_singularMatrix_throws)
{
	// Third row is a linear combination (sum) of the first two: singular (determinant 0).
	const float a[3][3] = {
		{ 1.0f, 2.0f, 3.0f },
		{ 4.0f, 5.0f, 6.0f },
		{ 5.0f, 7.0f, 9.0f }
	};
	float inv[3][3];
	CHECK_THROWS(GaussJordanSolver::invert(a, inv, 1.0E-4f), NotInvertibleMatrixException);
}

TEST(GaussJordanSolver, Invert_doesNotMutateInputArray)
{
	// a is deliberately non-const, so that a mutation would compile and be detected
	float a[2][2] = {
		{ 4.0f, 7.0f },
		{ 2.0f, 6.0f }
	};
	const float original[2][2] = { { 4.0f, 7.0f }, { 2.0f, 6.0f } };
	float inv[2][2];
	GaussJordanSolver::invert(a, inv, 1.0E-4f);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			CHECK_NEAR_TOL(a[i][j], original[i][j], 0.00001f);
}
