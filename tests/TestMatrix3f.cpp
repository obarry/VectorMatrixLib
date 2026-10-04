//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestMatrix3.java

#include <vector>
#include "TestFramework.h"
#include "Matrix3f.h"
#include "Vector3f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(Matrix3f, Matrix3_0)
{
	Matrix3f A;
	Matrix3f B(0.0f);
	Matrix3f C(7.0f);
	(void)C;

	CHECK(A == B);
}

TEST(Matrix3f, array_0)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = 0;

	Matrix3f A(array);
	Matrix3f B;

	CHECK(A == B);
}

TEST(Matrix3f, array_value)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = 5;
	array[1][2] = 22.3f;

	Matrix3f A(array);
	Matrix3f B(5.0f);
	B.set(1, 2, 22.3f);

	CHECK(A == B);
}

TEST(Matrix3f, plus)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = static_cast<float>(i + j);

	Matrix3f A(array);
	Matrix3f B(5.0f);
	Matrix3f C = A + B;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			CHECK(C.get(i, j) == static_cast<float>(i + j + 5));
}

TEST(Matrix3f, minus)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = static_cast<float>(i + j);

	Matrix3f A(array);
	Matrix3f B(2.0f);
	Matrix3f C = A - B;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			CHECK(C.get(i, j) == static_cast<float>(i + j - 2));
}

TEST(Matrix3f, plusEquals)
{
	float array1[3][3];
	float array2[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			array1[i][j] = static_cast<float>(i + j);
			array2[i][j] = static_cast<float>(i - j + 7);
		}

	Matrix3f A(array1);
	Matrix3f B(array2);
	A += B;

	CHECK(A.get(0, 0) == 7.0f && A.get(0, 1) == 7.0f && A.get(0, 2) == 7.0f);
	CHECK(A.get(1, 0) == 9.0f && A.get(1, 1) == 9.0f && A.get(1, 2) == 9.0f);
	CHECK(A.get(2, 0) == 11.0f && A.get(2, 1) == 11.0f && A.get(2, 2) == 11.0f);
}

TEST(Matrix3f, minusEquals)
{
	float array1[3][3];
	float array2[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			array1[i][j] = static_cast<float>(i + j);
			array2[i][j] = static_cast<float>(i - j + 7);
		}

	Matrix3f A(array1);
	Matrix3f B(array2);
	A -= B;

	CHECK(A.get(0, 0) == -7.0f && A.get(0, 1) == -5.0f && A.get(0, 2) == -3.0f);
	CHECK(A.get(1, 0) == -7.0f && A.get(1, 1) == -5.0f && A.get(1, 2) == -3.0f);
	CHECK(A.get(2, 0) == -7.0f && A.get(2, 1) == -5.0f && A.get(2, 2) == -3.0f);
}

TEST(Matrix3f, times)
{
	float array1[3][3];
	float array2[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			array1[i][j] = static_cast<float>(i + j);
			array2[i][j] = static_cast<float>(i - j + 7);
		}

	Matrix3f A(array1);
	Matrix3f B(array2);
	Matrix3f C = A * B;

	CHECK(C.get(0, 0) == 26.0f && C.get(0, 1) == 23.0f && C.get(0, 2) == 20.0f);
	CHECK(C.get(1, 0) == 50.0f && C.get(1, 1) == 44.0f && C.get(1, 2) == 38.0f);
	CHECK(C.get(2, 0) == 74.0f && C.get(2, 1) == 65.0f && C.get(2, 2) == 56.0f);
}

TEST(Matrix3f, transpose1)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = static_cast<float>(i - j + 2);

	Matrix3f A(array);
	Matrix3f B = A.transpose();
	Matrix3f C = B.transpose();
	CHECK(A == C);
}

TEST(Matrix3f, transpose2)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = static_cast<float>(i - j + 2);

	Matrix3f A(array);
	Matrix3f B(A); // Keep image of A before transposition
	A.transposeEquals();
	Matrix3f C = A.transpose(); // Do not modify A for this transposition
	CHECK(B == C);
}

TEST(Matrix3f, inverse1)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = (i > j) ? 0.0f : static_cast<float>(10 - 2 * i - j);

	Matrix3f A(array);
	Matrix3f B;
	bool invertible = true;
	try
	{
		B = A.inverse(); // Calculate inverse
	}
	catch (const NotInvertibleMatrixException&)
	{
		invertible = false;
	}
	CHECK(invertible);
	try
	{
		Matrix3f C = B.inverse(); // Inverse the inverse
		CHECK(A == C);
	}
	catch (const NotInvertibleMatrixException&)
	{
		CHECK(!"Not invertible Matrix B");
	}
}

TEST(Matrix3f, inverse2)
{
	float array[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			array[i][j] = (i > j) ? 0.0f : static_cast<float>(10 - 2 * i - j);

	Matrix3f A(array);
	try
	{
		Matrix3f B = A.inverse(); // Calculate inverse
		Matrix3f C = B * A; // inverse(A).A = I
		CHECK(C == Matrix3f::identity());
	}
	catch (const NotInvertibleMatrixException&)
	{
		CHECK(!"Not invertible Matrix");
	}
}

TEST(Matrix3f, inverse3)
{
	Matrix3f A(Matrix3f::identity());
	try
	{
		Matrix3f B = A.inverse(); // Calculate inverse
		CHECK(B == Matrix3f::identity());
	}
	catch (const NotInvertibleMatrixException&)
	{
		CHECK(!"Not invertible Matrix");
	}
}

// ----- Additional tests (bounds regressions, new methods, singular matrix) -----

TEST(Matrix3f, getRow_invalidIndex_throws)
{
	Matrix3f m(Matrix3f::identity());
	CHECK_THROWS(m.getRow(3), IndexOutOfBoundException); // valid indices are 0..2
}

TEST(Matrix3f, getColumn_invalidIndex_throws)
{
	Matrix3f m(Matrix3f::identity());
	CHECK_THROWS(m.getColumn(3), IndexOutOfBoundException); // valid indices are 0..2
}

// Not ported: timesRow_invalidIndex_throws (timesRow is a protected Java helper, absent from the C++ API)

TEST(Matrix3f, setRow_setColumn)
{
	Matrix3f m(0.0f);
	m.setRow(1, Vector3f(1.0f, 2.0f, 3.0f));
	CHECK_NEAR_TOL(m.get(1, 0), 1.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 1), 2.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 2), 3.0f, 0.0f);

	m.setColumn(2, Vector3f(7.0f, 8.0f, 9.0f));
	CHECK_NEAR_TOL(m.get(0, 2), 7.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 2), 8.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(2, 2), 9.0f, 0.0f);

	// round-trip: what we just set via setRow/setColumn must be readable via getRow/getColumn
	Vector3f col2 = m.getColumn(2);
	CHECK_NEAR_TOL(col2.getX(), 7.0f, 0.0f);
	CHECK_NEAR_TOL(col2.getY(), 8.0f, 0.0f);
	CHECK_NEAR_TOL(col2.getZ(), 9.0f, 0.0f);
}

TEST(Matrix3f, setRow_invalidIndex_throws)
{
	Matrix3f m(0.0f);
	CHECK_THROWS(m.setRow(3, Vector3f::zeroVector()), IndexOutOfBoundException);
}

TEST(Matrix3f, setColumn_invalidIndex_throws)
{
	Matrix3f m(0.0f);
	CHECK_THROWS(m.setColumn(3, Vector3f::zeroVector()), IndexOutOfBoundException);
}

TEST(Matrix3f, getArray_isDefensiveCopy)
{
	Matrix3f m(Matrix3f::identity());
	std::vector<std::vector<float>> arr = m.getArray();
	arr[0][0] = 999.0f; // mutate the returned array

	// The Matrix itself must be unaffected
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix3f, trace)
{
	CHECK_NEAR_TOL(Matrix3f::identity().trace(), 3.0f, 0.00001f);

	const float array[3][3] = {
		{ 2.0f, 0.0f, 0.0f },
		{ 0.0f, 5.0f, 0.0f },
		{ 0.0f, 0.0f, 9.0f }
	};
	Matrix3f m(array);
	CHECK_NEAR_TOL(m.trace(), 16.0f, 0.00001f);
}

TEST(Matrix3f, isIdentity)
{
	CHECK(Matrix3f::identity().isIdentity());
	CHECK(Matrix3f(Matrix3f::identity()).isIdentity());
	CHECK(!Matrix3f(0.0f).isIdentity());
	CHECK(!Matrix3f(1.0f).isIdentity()); // all-ones is not the Identity
}

TEST(Matrix3f, equals_negativeCase)
{
	Matrix3f a(1.0f);
	Matrix3f b(2.0f);
	CHECK(!(a == b));
}

TEST(Matrix3f, times_isNotCommutative)
{
	const float arrayA[3][3] = {
		{ 1.0f, 2.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};
	const float arrayB[3][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 3.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f }
	};
	Matrix3f a(arrayA);
	Matrix3f b(arrayB);

	Matrix3f ab = a * b;
	Matrix3f ba = b * a;
	CHECK(!(ab == ba));
}

TEST(Matrix3f, inverse_singularMatrix_throws)
{
	// Third row is a linear combination (sum) of the first two: this matrix is singular (determinant 0).
	const float array[3][3] = {
		{ 1.0f, 2.0f, 3.0f },
		{ 4.0f, 5.0f, 6.0f },
		{ 5.0f, 7.0f, 9.0f }
	};
	Matrix3f singular(array);
	CHECK_THROWS(singular.inverse(), NotInvertibleMatrixException);
}

TEST(Matrix3f, inverse_precision_generalCase)
{
	const float array[3][3] = {
		{ 4.0f, 7.0f, 2.0f },
		{ 3.0f, 5.0f, 1.0f },
		{ 2.0f, 3.0f, 1.0f }
	};
	Matrix3f a(array);
	Matrix3f invA = a.inverse();
	Matrix3f product = a * invA;
	CHECK(product == Matrix3f::identity());
}

TEST(Matrix3f, constructor_array_isDefensiveCopy)
{
	float source[3][3] = {
		{ 1.0f, 2.0f, 3.0f },
		{ 4.0f, 5.0f, 6.0f },
		{ 7.0f, 8.0f, 9.0f }
	};
	Matrix3f m(source);

	// Mutate the source array after construction: the Matrix must be unaffected.
	source[0][0] = 999.0f;
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix3f, setArray_isDefensiveCopy)
{
	Matrix3f m(0.0f);
	std::vector<std::vector<float>> source = {
		{ 1.0f, 2.0f, 3.0f },
		{ 4.0f, 5.0f, 6.0f },
		{ 7.0f, 8.0f, 9.0f }
	};
	m.setArray(source);

	source[0][0] = 999.0f;
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix3f, determinant)
{
	CHECK_NEAR_TOL(Matrix3f::identity().determinant(), 1.0f, 0.00001f);

	const float diagonal[3][3] = {
		{ 2.0f, 0.0f, 0.0f },
		{ 0.0f, 3.0f, 0.0f },
		{ 0.0f, 0.0f, 4.0f }
	};
	Matrix3f m(diagonal);
	CHECK_NEAR_TOL(m.determinant(), 24.0f, 0.00001f); // diagonal matrix: det = product of diagonal

	// A known singular matrix (third row = row1+row2) must have determinant 0
	const float singularArray[3][3] = {
		{ 1.0f, 2.0f, 3.0f },
		{ 4.0f, 5.0f, 6.0f },
		{ 5.0f, 7.0f, 9.0f }
	};
	Matrix3f singular(singularArray);
	CHECK_NEAR_TOL(singular.determinant(), 0.0f, 0.00001f);
}

// Not ported: equalsObject_and_hashCode (Java equals(Object)/null/other type and hashCode only)

TEST(Matrix3f, identity_isFreshIndependentCopyEachCall)
{
	// The Java reference-identity check (i1 != i2) is meaningless by value; the value semantics are kept.
	Matrix3f i1 = Matrix3f::identity();
	Matrix3f i2 = Matrix3f::identity();
	CHECK(i1 == i2);

	// Mutating one call's result must never affect a later call's result
	i1.set(0, 0, 999.0f);
	Matrix3f i3 = Matrix3f::identity();
	CHECK_NEAR_TOL(i3.get(0, 0), 1.0f, 0.0f);
}

// Not ported: swapRows_timesRow_areProtected_notPublicApi (Java protected visibility test; swapRows absent from the C++ API)
