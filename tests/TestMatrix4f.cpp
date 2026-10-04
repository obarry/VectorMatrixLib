//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestMatrix4.java

#include <vector>
#include "TestFramework.h"
#include "Vector4f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(Matrix4f, Matrix4_0)
{
	Matrix4f A;
	Matrix4f B(0.0f);
	Matrix4f C(7.0f);
	(void)C;

	CHECK_EQUAL(A, B);
}

TEST(Matrix4f, array_0)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = 0;

	Matrix4f A(array);
	Matrix4f B;

	CHECK_EQUAL(A, B);
}

TEST(Matrix4f, array_value)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = 5;
	array[1][2] = 22.3f;

	Matrix4f A(array);
	Matrix4f B(5.0f);
	B.set(1, 2, 22.3f);

	CHECK_EQUAL(A, B);
}

TEST(Matrix4f, plus)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = static_cast<float>(i + j);

	Matrix4f A(array);
	Matrix4f B(5.0f);
	Matrix4f C = A + B;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			CHECK_EQUAL(C.get(i, j), static_cast<float>(i + j + 5));
}

TEST(Matrix4f, minus)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = static_cast<float>(i + j);

	Matrix4f A(array);
	Matrix4f B(2.0f);
	Matrix4f C = A - B;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			CHECK_EQUAL(C.get(i, j), static_cast<float>(i + j - 2));
}

TEST(Matrix4f, plusEquals)
{
	float array1[4][4];
	float array2[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			array1[i][j] = static_cast<float>(i + j);
			array2[i][j] = static_cast<float>(i - j + 7);
		}
	}

	Matrix4f A(array1);
	Matrix4f B(array2);
	A += B;

	CHECK(A.get(0, 0) == 7.0f && A.get(0, 1) == 7.0f && A.get(0, 2) == 7.0f);
	CHECK(A.get(1, 0) == 9.0f && A.get(1, 1) == 9.0f && A.get(1, 2) == 9.0f);
	CHECK(A.get(2, 0) == 11.0f && A.get(2, 1) == 11.0f && A.get(2, 2) == 11.0f);
}

TEST(Matrix4f, minusEquals)
{
	float array1[4][4];
	float array2[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			array1[i][j] = static_cast<float>(i + j);
			array2[i][j] = static_cast<float>(i - j + 7);
		}
	}

	Matrix4f A(array1);
	Matrix4f B(array2);
	A -= B;

	CHECK(A.get(0, 0) == -7.0f && A.get(0, 1) == -5.0f && A.get(0, 2) == -3.0f);
	CHECK(A.get(1, 0) == -7.0f && A.get(1, 1) == -5.0f && A.get(1, 2) == -3.0f);
	CHECK(A.get(2, 0) == -7.0f && A.get(2, 1) == -5.0f && A.get(2, 2) == -3.0f);
}

TEST(Matrix4f, times)
{
	float array1[4][4];
	float array2[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			array1[i][j] = static_cast<float>(i + j);
			array2[i][j] = static_cast<float>(i - j + 7);
		}
	}

	Matrix4f A(array1);
	Matrix4f B(array2);
	Matrix4f C = A * B;

	CHECK(C.get(0, 0) == 56.0f && C.get(0, 1) == 50.0f && C.get(0, 2) == 44.0f && C.get(0, 3) == 38.0f);
	CHECK(C.get(1, 0) == 90.0f && C.get(1, 1) == 80.0f && C.get(1, 2) == 70.0f && C.get(1, 3) == 60.0f);
	CHECK(C.get(2, 0) == 124.0f && C.get(2, 1) == 110.0f && C.get(2, 2) == 96.0f && C.get(2, 3) == 82.0f);
	CHECK(C.get(3, 0) == 158.0f && C.get(3, 1) == 140.0f && C.get(3, 2) == 122.0f && C.get(3, 3) == 104.0f);
}

TEST(Matrix4f, transpose1)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = static_cast<float>(i - j + 3);

	Matrix4f A(array);
	Matrix4f B = A.transpose();
	Matrix4f C = B.transpose();

	CHECK_EQUAL(A, C);
}

TEST(Matrix4f, transpose2)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = static_cast<float>(i - j + 2);

	Matrix4f A(array);
	Matrix4f B(A); // Keep image of A before transposition
	A.transposeEquals();
	Matrix4f C = A.transpose(); // Do not modify A for this transposition

	CHECK_EQUAL(B, C);
}

TEST(Matrix4f, inverse1)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = (i > j) ? 0.0f : static_cast<float>(10 - 2 * i - j);

	Matrix4f A(array);
	Matrix4f B;
	Matrix4f C;

	CHECK_NO_THROW(B = A.inverse()); // Calculate inverse
	CHECK_NO_THROW(C = B.inverse()); // Inverse the inverse
	CHECK_EQUAL(A, C);
}

TEST(Matrix4f, inverse2)
{
	float array[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			array[i][j] = (i > j) ? 0.0f : static_cast<float>(10 - 2 * i - j);

	Matrix4f A(array);
	Matrix4f B;

	CHECK_NO_THROW(B = A.inverse()); // Calculate inverse
	Matrix4f C = B * A; // inverse(A).A = I
	CHECK_EQUAL(C, Matrix4f::identity());
}

TEST(Matrix4f, inverse3)
{
	Matrix4f A(Matrix4f::identity());
	Matrix4f B;

	CHECK_NO_THROW(B = A.inverse()); // Calculate inverse
	CHECK_EQUAL(B, Matrix4f::identity());
}

TEST(Matrix4f, setDiagonal_regression_lastElement)
{
	Matrix4f m(0.0f);
	m.setDiagonal(7.0f);
	CHECK_NEAR_TOL(m.get(0, 0), 7.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 1), 7.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(2, 2), 7.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(3, 3), 7.0f, 0.0f); // this element was left at 0 before the fix
}

TEST(Matrix4f, getRow_invalidIndex_throws)
{
	Matrix4f m(Matrix4f::identity());
	CHECK_THROWS(m.getRow(4), IndexOutOfBoundException); // valid indices are 0..3
}

TEST(Matrix4f, getColumn_invalidIndex_throws)
{
	Matrix4f m(Matrix4f::identity());
	CHECK_THROWS(m.getColumn(4), IndexOutOfBoundException); // valid indices are 0..3
}

// Not ported: testMatrix4_timesRow_invalidIndex_throws (timesRow is protected in Java, absent from the C++ API)

TEST(Matrix4f, setRow_invalidIndex_throws)
{
	Matrix4f m(0.0f);
	CHECK_THROWS(m.setRow(4, Vector4f::zeroVector()), IndexOutOfBoundException);
}

TEST(Matrix4f, setColumn_invalidIndex_throws)
{
	Matrix4f m(0.0f);
	CHECK_THROWS(m.setColumn(4, Vector4f::zeroVector()), IndexOutOfBoundException);
}

TEST(Matrix4f, setRow_setColumn_roundTrip)
{
	Matrix4f m(0.0f);
	m.setRow(2, Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
	Vector4f row2 = m.getRow(2);
	CHECK_NEAR_TOL(row2.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(row2.getW(), 4.0f, 0.0f);

	m.setColumn(3, Vector4f(5.0f, 6.0f, 7.0f, 8.0f));
	Vector4f col3 = m.getColumn(3);
	CHECK_NEAR_TOL(col3.getX(), 5.0f, 0.0f);
	CHECK_NEAR_TOL(col3.getW(), 8.0f, 0.0f);
}

TEST(Matrix4f, getMatrix3_subMatrix)
{
	const float array[4][4] = {
		{ 1.0f, 2.0f, 3.0f, 99.0f },
		{ 4.0f, 5.0f, 6.0f, 99.0f },
		{ 7.0f, 8.0f, 9.0f, 99.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	Matrix4f m(array);
	Matrix3f sub = m.getMatrix3();
	CHECK_NEAR_TOL(sub.get(0, 0), 1.0f, 0.0f);
	CHECK_NEAR_TOL(sub.get(1, 1), 5.0f, 0.0f);
	CHECK_NEAR_TOL(sub.get(2, 2), 9.0f, 0.0f);
	CHECK_NEAR_TOL(sub.get(2, 1), 8.0f, 0.0f);
}

TEST(Matrix4f, trace)
{
	CHECK_NEAR_TOL(Matrix4f::identity().trace(), 4.0f, 0.00001f);

	const float array[4][4] = {
		{ 2.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 3.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 4.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 5.0f }
	};
	Matrix4f m(array);
	CHECK_NEAR_TOL(m.trace(), 14.0f, 0.00001f);
}

TEST(Matrix4f, isIdentity)
{
	CHECK(Matrix4f::identity().isIdentity());
	CHECK(Matrix4f(Matrix4f::identity()).isIdentity());
	CHECK(!Matrix4f(0.0f).isIdentity());
}

TEST(Matrix4f, equals_negativeCase)
{
	Matrix4f a(1.0f);
	Matrix4f b(2.0f);
	CHECK(!(a == b));
}

TEST(Matrix4f, times_isNotCommutative)
{
	const float arrayA[4][4] = {
		{ 1.0f, 2.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	const float arrayB[4][4] = {
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 3.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	Matrix4f a(arrayA);
	Matrix4f b(arrayB);

	Matrix4f ab = a * b;
	Matrix4f ba = b * a;
	CHECK(!(ab == ba));
}

TEST(Matrix4f, inverse_singularMatrix_throws)
{
	// Last row is entirely 0: this matrix is singular (determinant 0).
	const float array[4][4] = {
		{ 1.0f, 2.0f, 3.0f, 4.0f },
		{ 5.0f, 6.0f, 7.0f, 8.0f },
		{ 9.0f, 10.0f, 11.0f, 12.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f }
	};
	Matrix4f singular(array);
	CHECK_THROWS(singular.inverse(), NotInvertibleMatrixException);
}

TEST(Matrix4f, inverse_precision_generalCase)
{
	const float array[4][4] = {
		{ 4.0f, 7.0f, 2.0f, 1.0f },
		{ 3.0f, 5.0f, 1.0f, 2.0f },
		{ 2.0f, 3.0f, 1.0f, 0.0f },
		{ 1.0f, 0.0f, 2.0f, 3.0f }
	};
	Matrix4f a(array);
	Matrix4f invA = a.inverse();
	Matrix4f product = a * invA;
	CHECK_EQUAL(product, Matrix4f::identity());
}

TEST(Matrix4f, constructor_array_isDefensiveCopy)
{
	float source[4][4] = {
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	Matrix4f m(source);

	source[0][0] = 999.0f;
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix4f, setArray_isDefensiveCopy)
{
	Matrix4f m(0.0f);
	std::vector<std::vector<float>> source = {
		{ 1.0f, 2.0f, 3.0f, 4.0f },
		{ 5.0f, 6.0f, 7.0f, 8.0f },
		{ 9.0f, 10.0f, 11.0f, 12.0f },
		{ 13.0f, 14.0f, 15.0f, 16.0f }
	};
	m.setArray(source);

	source[0][0] = 999.0f;
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix4f, getArray_isDefensiveCopy)
{
	Matrix4f m(Matrix4f::identity());
	std::vector<std::vector<float>> arr = m.getArray();
	arr[0][0] = 999.0f;

	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix4f, determinant)
{
	CHECK_NEAR_TOL(Matrix4f::identity().determinant(), 1.0f, 0.00001f);

	const float array[4][4] = {
		{ 2.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 3.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 4.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 5.0f }
	};
	Matrix4f m(array);
	CHECK_NEAR_TOL(m.determinant(), 120.0f, 0.0001f); // diagonal matrix: det = product of diagonal

	// Last row all zero -> singular -> determinant 0
	const float arraySingular[4][4] = {
		{ 1.0f, 2.0f, 3.0f, 4.0f },
		{ 5.0f, 6.0f, 7.0f, 8.0f },
		{ 9.0f, 10.0f, 11.0f, 12.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f }
	};
	Matrix4f singular(arraySingular);
	CHECK_NEAR_TOL(singular.determinant(), 0.0f, 0.0001f);
}

TEST(Matrix4f, setArrayOfGetArray_realWorldPattern)
{
	// Mirrors the pattern used in LookAt: combine two matrices, then adopt the result's array
	// into a third matrix via getArray()/setArray().
	const float arrayB[4][4] = {
		{ 1.0f, 0.0f, 0.0f, 2.0f },
		{ 0.0f, 1.0f, 0.0f, 3.0f },
		{ 0.0f, 0.0f, 1.0f, 4.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	Matrix4f b(arrayB);
	Matrix4f c(Matrix4f::identity());

	Matrix4f a(0.0f);
	a.setArray((b * c).getArray());

	CHECK_EQUAL(a, b);
}

// Not ported: testMatrix4_equalsObject_and_hashCode (Java-only equals(Object)/null/other type and hashCode)

TEST(Matrix4f, identity_isFreshIndependentCopyEachCall)
{
	// The Java reference-identity check (i1 != i2) is not applicable to C++ values; the by-value part is ported.
	Matrix4f i1 = Matrix4f::identity();
	Matrix4f i2 = Matrix4f::identity();
	CHECK_EQUAL(i1, i2);

	// Mutating one call's result must never affect a later call's result
	i1.set(0, 0, 999.0f);
	Matrix4f i3 = Matrix4f::identity();
	CHECK_NEAR_TOL(i3.get(0, 0), 1.0f, 0.0f);
}

// Not ported: testMatrix4_swapRows_timesRow_areProtected_notPublicApi (protected API visibility test, swapRows absent from the C++ API)
