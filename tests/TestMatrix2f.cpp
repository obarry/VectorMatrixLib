//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestMatrix2.java

#include <vector>
#include "TestFramework.h"
#include "Vector2f.h"
#include "Matrix2f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(Matrix2f, Matrix2_0)
{
	Matrix2f A;
	Matrix2f B(0.0f);
	Matrix2f C(7.0f);
	(void)C;

	CHECK_EQUAL(A, B);
}

TEST(Matrix2f, array_0)
{
	float array[2][2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			array[i][j] = 0;
		}
	}

	Matrix2f A(array);
	Matrix2f B;

	CHECK_EQUAL(A, B);
}

TEST(Matrix2f, array_value)
{
	float array[2][2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			array[i][j] = 5;
		}
	}
	array[1][0] = 22.3f;

	Matrix2f A(array);
	Matrix2f B(5.0f);
	B.set(1, 0, 22.3f);

	CHECK_EQUAL(A, B);
}

TEST(Matrix2f, plus)
{
	float array[2][2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			array[i][j] = static_cast<float>(i + j);
		}
	}

	Matrix2f A(array);
	Matrix2f B(5.0f);
	Matrix2f C = A + B;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			CHECK_NEAR_TOL(C.get(i, j), static_cast<float>(i + j + 5), 0.0f);
		}
	}
}

TEST(Matrix2f, minus)
{
	float array[2][2];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			array[i][j] = static_cast<float>(i + j);
		}
	}

	Matrix2f A(array);
	Matrix2f B(2.0f);
	Matrix2f C = A - B;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			CHECK_NEAR_TOL(C.get(i, j), static_cast<float>(i + j - 2), 0.0f);
		}
	}
}

TEST(Matrix2f, plusEquals)
{
	/*
	 * A=[[0.0, 1.0]
	 *    [1.0, 2.0]]
	 *
	 * B=[[7.0, 6.0]
	 *    [8.0, 7.0]]
	 */
	const float array1[2][2] = { { 0.0f, 1.0f }, { 1.0f, 2.0f } };
	const float array2[2][2] = { { 7.0f, 6.0f }, { 8.0f, 7.0f } };

	Matrix2f A(array1);
	Matrix2f B(array2);
	A += B;

	CHECK_NEAR_TOL(A.get(0, 0), 7.0f, 0.0f);
	CHECK_NEAR_TOL(A.get(0, 1), 7.0f, 0.0f);
	CHECK_NEAR_TOL(A.get(1, 0), 9.0f, 0.0f);
	CHECK_NEAR_TOL(A.get(1, 1), 9.0f, 0.0f);
}

TEST(Matrix2f, minusEquals)
{
	const float array1[2][2] = { { 0.0f, 1.0f }, { 1.0f, 2.0f } };
	const float array2[2][2] = { { 7.0f, 6.0f }, { 8.0f, 7.0f } };

	Matrix2f A(array1);
	Matrix2f B(array2);
	A -= B;

	CHECK_NEAR_TOL(A.get(0, 0), -7.0f, 0.0f);
	CHECK_NEAR_TOL(A.get(0, 1), -5.0f, 0.0f);
	CHECK_NEAR_TOL(A.get(1, 0), -7.0f, 0.0f);
	CHECK_NEAR_TOL(A.get(1, 1), -5.0f, 0.0f);
}

TEST(Matrix2f, times)
{
	/*
	 * A=[[0.0, 1.0]
	 *    [1.0, 2.0]]
	 *
	 * B=[[7.0, 6.0]
	 *    [8.0, 7.0]]
	 */
	const float array1[2][2] = { { 0.0f, 1.0f }, { 1.0f, 2.0f } };
	const float array2[2][2] = { { 7.0f, 6.0f }, { 8.0f, 7.0f } };

	Matrix2f A(array1);
	Matrix2f B(array2);
	Matrix2f C = A * B;

	// Row0 = [0,1]: [0*7+1*8, 0*6+1*7] = [8, 7]
	// Row1 = [1,2]: [1*7+2*8, 1*6+2*7] = [23, 20]
	CHECK_NEAR_TOL(C.get(0, 0), 8.0f, 0.0f);
	CHECK_NEAR_TOL(C.get(0, 1), 7.0f, 0.0f);
	CHECK_NEAR_TOL(C.get(1, 0), 23.0f, 0.0f);
	CHECK_NEAR_TOL(C.get(1, 1), 20.0f, 0.0f);
}

TEST(Matrix2f, timesEquals)
{
	const float array1[2][2] = { { 0.0f, 1.0f }, { 1.0f, 2.0f } };
	const float array2[2][2] = { { 7.0f, 6.0f }, { 8.0f, 7.0f } };

	Matrix2f A(array1);
	Matrix2f B(array2);
	Matrix2f expected = A * B;
	A *= B;

	CHECK_EQUAL(A, expected);
}

TEST(Matrix2f, times_scalar)
{
	const float array[2][2] = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
	Matrix2f A(array);
	Matrix2f B = A * 2.0f;
	CHECK_NEAR_TOL(B.get(0, 0), 2.0f, 0.0f);
	CHECK_NEAR_TOL(B.get(0, 1), 4.0f, 0.0f);
	CHECK_NEAR_TOL(B.get(1, 0), 6.0f, 0.0f);
	CHECK_NEAR_TOL(B.get(1, 1), 8.0f, 0.0f);

	A *= 2.0f;
	CHECK_EQUAL(A, B);
}

TEST(Matrix2f, transpose1)
{
	const float array[2][2] = { { 2.0f, 1.0f }, { 3.0f, 2.0f } };
	Matrix2f A(array);
	Matrix2f B = A.transpose();
	Matrix2f C = B.transpose();
	CHECK_EQUAL(C, A);
}

TEST(Matrix2f, transpose2)
{
	const float array[2][2] = { { 2.0f, 1.0f }, { 3.0f, 2.0f } };
	Matrix2f A(array);
	Matrix2f B(A); // Keep image of A before transposition
	A.transposeEquals();
	Matrix2f C = A.transpose(); // Do not modify A for this transposition
	CHECK_EQUAL(C, B);
}

TEST(Matrix2f, inverse1)
{
	const float array[2][2] = { { 10.0f, 9.0f }, { 0.0f, 7.0f } };
	Matrix2f A(array);
	Matrix2f B;

	CHECK_NO_THROW(B = A.inverse());
	Matrix2f C;
	CHECK_NO_THROW(C = B.inverse());
	CHECK_EQUAL(C, A);
}

TEST(Matrix2f, inverse2)
{
	const float array[2][2] = { { 10.0f, 9.0f }, { 0.0f, 7.0f } };
	Matrix2f A(array);
	Matrix2f B;
	CHECK_NO_THROW(B = A.inverse());
	Matrix2f C = B * A; // inverse(A).A = I
	CHECK_EQUAL(C, Matrix2f::identity());
}

TEST(Matrix2f, inverse3)
{
	Matrix2f A(Matrix2f::identity());
	Matrix2f B;
	CHECK_NO_THROW(B = A.inverse());
	CHECK_EQUAL(B, Matrix2f::identity());
}

TEST(Matrix2f, inverse_singularMatrix_throws)
{
	// Second row is 2x the first row: this matrix is singular (determinant 0).
	const float array[2][2] = { { 1.0f, 2.0f }, { 2.0f, 4.0f } };
	Matrix2f singular(array);
	CHECK_THROWS(singular.inverse(), NotInvertibleMatrixException);
}

TEST(Matrix2f, inverse_precision_generalCase)
{
	const float array[2][2] = { { 4.0f, 7.0f }, { 2.0f, 6.0f } };
	Matrix2f a(array);
	Matrix2f invA = a.inverse();
	Matrix2f product = a * invA;
	CHECK_EQUAL(product, Matrix2f::identity());
}

TEST(Matrix2f, getRow_invalidIndex_throws)
{
	Matrix2f m(Matrix2f::identity());
	CHECK_THROWS(m.getRow(2), IndexOutOfBoundException); // valid indices are 0..1
}

TEST(Matrix2f, getColumn_invalidIndex_throws)
{
	Matrix2f m(Matrix2f::identity());
	CHECK_THROWS(m.getColumn(2), IndexOutOfBoundException); // valid indices are 0..1
}

// Not ported: testMatrix2_timesRow_invalidIndex_throws, timesRow is a protected Java helper absent from the C++ API

TEST(Matrix2f, setRow_setColumn)
{
	Matrix2f m(0.0f);
	m.setRow(1, Vector2f(1.0f, 2.0f));
	CHECK_NEAR_TOL(m.get(1, 0), 1.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 1), 2.0f, 0.0f);

	m.setColumn(1, Vector2f(7.0f, 8.0f));
	CHECK_NEAR_TOL(m.get(0, 1), 7.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 1), 8.0f, 0.0f);

	// round-trip: what we just set via setRow/setColumn must be readable via getRow/getColumn
	Vector2f col1 = m.getColumn(1);
	CHECK_NEAR_TOL(col1.getX(), 7.0f, 0.0f);
	CHECK_NEAR_TOL(col1.getY(), 8.0f, 0.0f);
}

TEST(Matrix2f, setRow_invalidIndex_throws)
{
	Matrix2f m(0.0f);
	CHECK_THROWS(m.setRow(2, Vector2f(0.0f, 0.0f)), IndexOutOfBoundException);
}

TEST(Matrix2f, setColumn_invalidIndex_throws)
{
	Matrix2f m(0.0f);
	CHECK_THROWS(m.setColumn(2, Vector2f(0.0f, 0.0f)), IndexOutOfBoundException);
}

TEST(Matrix2f, getArray_isDefensiveCopy)
{
	Matrix2f m(Matrix2f::identity());
	std::vector<std::vector<float>> arr = m.getArray();
	arr[0][0] = 999.0f; // mutate the returned array

	// The Matrix itself must be unaffected
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix2f, trace)
{
	CHECK_NEAR_TOL(Matrix2f::identity().trace(), 2.0f, 0.00001f);

	const float array[2][2] = { { 2.0f, 0.0f }, { 0.0f, 5.0f } };
	Matrix2f m(array);
	CHECK_NEAR_TOL(m.trace(), 7.0f, 0.00001f);
}

TEST(Matrix2f, isIdentity)
{
	CHECK(Matrix2f::identity().isIdentity());
	CHECK(Matrix2f(Matrix2f::identity()).isIdentity());
	CHECK(!Matrix2f(0.0f).isIdentity());
	CHECK(!Matrix2f(1.0f).isIdentity()); // all-ones is not the Identity
}

TEST(Matrix2f, equals_negativeCase)
{
	Matrix2f a(1.0f);
	Matrix2f b(2.0f);
	CHECK(!(a == b));
}

TEST(Matrix2f, times_isNotCommutative)
{
	const float arrayA[2][2] = { { 1.0f, 2.0f }, { 0.0f, 1.0f } };
	const float arrayB[2][2] = { { 1.0f, 0.0f }, { 3.0f, 1.0f } };
	Matrix2f a(arrayA);
	Matrix2f b(arrayB);

	Matrix2f ab = a * b;
	Matrix2f ba = b * a;
	CHECK(!(ab == ba));
}

TEST(Matrix2f, determinant)
{
	CHECK_NEAR_TOL(Matrix2f::identity().determinant(), 1.0f, 0.00001f);

	const float diag[2][2] = { { 2.0f, 0.0f }, { 0.0f, 3.0f } };
	Matrix2f m(diag);
	CHECK_NEAR_TOL(m.determinant(), 6.0f, 0.00001f); // diagonal matrix: det = product of diagonal

	// A known singular matrix (row1 = 2x row0) must have determinant 0
	const float sing[2][2] = { { 1.0f, 2.0f }, { 2.0f, 4.0f } };
	Matrix2f singular(sing);
	CHECK_NEAR_TOL(singular.determinant(), 0.0f, 0.00001f);
}

// Not ported: testMatrix2_equalsObject_and_hashCode, Java-only equals(Object)/hashCode contract

TEST(Matrix2f, identity_isFreshIndependentCopyEachCall)
{
	// The reference identity check (i1 != i2 as Java references) is not meaningful in C++
	Matrix2f i1 = Matrix2f::identity();
	Matrix2f i2 = Matrix2f::identity();
	CHECK_EQUAL(i1, i2);

	// Mutating one call's result must never affect a later call's result.
	i1.set(0, 0, 999.0f);
	Matrix2f i3 = Matrix2f::identity();
	CHECK_NEAR_TOL(i3.get(0, 0), 1.0f, 0.0f);
}

// Not ported: testMatrix2_swapRows_timesRow_areProtected_notPublicApi, protected Java API absent from C++

TEST(Matrix2f, constructor_array_isDefensiveCopy)
{
	float source[2][2] = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
	Matrix2f m(source);

	// Mutate the source array after construction: the Matrix must be unaffected.
	source[0][0] = 999.0f;
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix2f, setArray_isDefensiveCopy)
{
	Matrix2f m(0.0f);
	std::vector<std::vector<float>> source = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
	m.setArray(source);

	source[0][0] = 999.0f;
	CHECK_NEAR_TOL(m.get(0, 0), 1.0f, 0.0f);
}

TEST(Matrix2f, setArray_wrongRowSize_throws)
{
	Matrix2f m(0.0f);
	std::vector<std::vector<float>> a = { { 1.0f, 2.0f }, { 3.0f, 4.0f }, { 5.0f, 6.0f } }; // 3 rows instead of 2
	CHECK_THROWS(m.setArray(a), MatrixArrayWrongSizeException);
}

TEST(Matrix2f, setArray_wrongColumnSize_throws)
{
	Matrix2f m(0.0f);
	std::vector<std::vector<float>> a = { { 1.0f, 2.0f, 3.0f }, { 4.0f, 5.0f, 6.0f } }; // 3 columns instead of 2
	CHECK_THROWS(m.setArray(a), MatrixArrayWrongSizeException);
}

TEST(Matrix2f, setDiagonal)
{
	Matrix2f m(0.0f);
	m.setDiagonal(5.0f);
	CHECK_NEAR_TOL(m.get(0, 0), 5.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 1), 5.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(0, 1), 0.0f, 0.0f);
	CHECK_NEAR_TOL(m.get(1, 0), 0.0f, 0.0f);
}

// ----- times(Vector2f): Matrix2f's own version of the Matrix3f/Vector3fMatrix3f cross-check -----

TEST(Matrix2f, times_vector2_matchesManualComputation)
{
	const float array[2][2] = { { 2.0f, 3.0f }, { 4.0f, 5.0f } };
	Matrix2f A(array);
	Vector2f v(1.0f, 2.0f);

	Vector2f w = A * v;

	// W = A.V : w.x = 2*1+3*2 = 8 ; w.y = 4*1+5*2 = 14
	CHECK_NEAR_TOL(w.getX(), 8.0f, 0.0001f);
	CHECK_NEAR_TOL(w.getY(), 14.0f, 0.0001f);
}

TEST(Matrix2f, times_vector2_identityIsNoOp)
{
	Vector2f v(3.5f, -2.25f);
	Vector2f w = Matrix2f::identity() * v;

	CHECK_EQUAL(w, v);
}

TEST(Matrix2f, times_vector2_matchesVector2TimesMatrix2)
{
	const float array[2][2] = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
	Matrix2f A(array);
	Vector2f v(5.0f, 6.0f);

	Vector2f fromMatrix = A * v;
	Vector2f fromVector = v * A;

	CHECK_EQUAL(fromMatrix, fromVector);
}

TEST(Matrix2f, timesEquals_vector2_matchesTimes)
{
	const float array[2][2] = { { 2.0f, 0.0f }, { 0.0f, 3.0f } };
	Matrix2f A(array);
	Vector2f v(4.0f, 5.0f);

	Vector2f expected = v * A;
	v *= A;

	CHECK_EQUAL(v, expected);
}
