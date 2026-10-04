//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestVector3.java

#include <array>
#include "TestFramework.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix3f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(Vector3f, equals)
{
	Vector3f V1;
	Vector3f V2(0.0f);
	Vector3f V3(7.0f);
	(void)V3;

	CHECK(V1 == V2);
}

TEST(Vector3f, axis)
{
	const float x_axis[3] = { 1.0f, 0.0f, 0.0f };
	const float y_axis[3] = { 0.0f, 1.0f, 0.0f };
	const float z_axis[3] = { 0.0f, 0.0f, 1.0f };

	Vector3f V1 = Vector3f::xAxis();
	Vector3f V2 = Vector3f::yAxis();
	Vector3f V3 = Vector3f::zAxis();

	CHECK(V1 == Vector3f(x_axis));
	CHECK(V2 == Vector3f(y_axis));
	CHECK(V3 == Vector3f(z_axis));
}

TEST(Vector3f, length)
{
	const float values[3] = { 1.0f, 2.0f, 3.0f };
	Vector3f vector(values);
	CHECK_NEAR_TOL(vector.length(), (float)std::sqrt(1 * 1 + 2 * 2 + 3 * 3), 0.00001f);
}

TEST(Vector3f, normalize)
{
	Vector3f V1(12.0f, -12.0f, 24.0f);
	CHECK(!(V1.getX() != 12.0f || V1.getY() != -12.0f || V1.getZ() != 24.0f));

	V1.normalize();
	CHECK_NEAR_TOL(V1.length(), 1, 0.00001f);
}

TEST(Vector3f, array_0)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = 0;

	Vector3f V1(array);
	Vector3f V2;
	CHECK(V1 == V2);
}

TEST(Vector3f, array_value)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = 5;
	array[1] = 22.3f;

	Vector3f V1(array);
	Vector3f V2(5.0f);
	V2.set(1, 22.3f);
	CHECK(V1 == V2);
}

TEST(Vector3f, plus)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = (float)i;

	Vector3f V1(array);
	Vector3f V2(5.0f);
	Vector3f V3 = V1 + V2;

	for (int i = 0; i < 3; i++)
		CHECK(V3.get(i) == i + 5);
}

TEST(Vector3f, plusEquals)
{
	float array1[3];
	float array2[3];
	for (int i = 0; i < 3; i++)
		array1[i] = (float)(7 - i); // (7, 6, 5)
	for (int i = 0; i < 3; i++)
		array2[i] = (float)(i * 2); // (0, 2, 4)

	Vector3f V1(array1);
	Vector3f V2(array2);
	V1 += V2;

	CHECK(V1.get(0) == 7.0f && V1.get(1) == 8.0f && V1.get(2) == 9.0f);
}

TEST(Vector3f, minus)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = (float)i;

	Vector3f V1(array);
	Vector3f V2(2.0f);
	Vector3f V3 = V1 - V2;

	for (int i = 0; i < 3; i++)
		CHECK(V3.get(i) == i - 2);
}

TEST(Vector3f, minusEquals)
{
	float array1[3];
	float array2[3];
	for (int i = 0; i < 3; i++)
		array1[i] = (float)(7 - i); // (7, 6, 5)
	for (int i = 0; i < 3; i++)
		array2[i] = (float)(i * 2 - 3); // (-3, -1, 1)

	Vector3f V1(array1);
	Vector3f V2(array2);
	V1 -= V2;

	CHECK(V1.get(0) == 10.0f && V1.get(1) == 7.0f && V1.get(2) == 4.0f);
}

TEST(Vector3f, times)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = (float)(i + 1); // (1, 2, 3)

	Vector3f V1(array);
	Vector3f V2 = V1 * 7.0f;

	CHECK(V2.get(0) == 7.0f && V2.get(1) == 14.0f && V2.get(2) == 21.0f);
}

TEST(Vector3f, timesEquals)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = (float)(i - 1); // (-1, 0, 1)

	Vector3f V1(array);
	V1 *= 3.0f;

	CHECK(V1.get(0) == -3.0f && V1.get(1) == 0.0f && V1.get(2) == 3.0f);
}

TEST(Vector3f, scalar)
{
	float array[3];
	for (int i = 0; i < 3; i++)
		array[i] = (float)i;

	Vector3f V1(array);
	Vector3f V2(2.0f);
	float scal = V1.dot(V2);

	CHECK(scal == 6);
}

TEST(Vector3f, timesVector)
{
	// a=(a1,a2,a3) and b=(b1,b2,b3) then a^b=(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)
	float array1[3];
	float array2[3];
	for (int i = 0; i < 3; i++)
	{
		array1[i] = (float)i;
		array2[i] = (float)(3 - i);
	}

	Vector3f V1(array1); // V1=(0,1,2)
	Vector3f V2(array2); // V2=(3,2,1)
	Vector3f V3 = V1.cross(V2); // V3=(1x1-2x2, 2x3-0x1, 0x2-1x3)=(-3,6,-3)

	CHECK(V3.get(0) == -3.0f && V3.get(1) == 6.0f && V3.get(2) == -3.0f);
}

TEST(Vector3f, timesEqualsVector)
{
	// a=(a1,a2,a3) and b=(b1,b2,b3) then a^b=(a2b3-a3b2, a3b1-a1b3, a1b2-a2b1)
	float array1[3];
	float array2[3];
	for (int i = 0; i < 3; i++)
	{
		array1[i] = (float)(i + 1);
		array2[i] = (float)(3 - i);
	}

	Vector3f V1(array1); // V1=(1,2,3)
	Vector3f V2(array2); // V2=(3,2,1)
	V1.crossEquals(V2); // Result=(2x1-3x2, 3x3-1x1, 1x2-2x3)=(-4,8,-4)

	CHECK(V1.get(0) == -4.0f && V1.get(1) == 8.0f && V1.get(2) == -4.0f);
}

TEST(Vector3f, get_invalidIndex_throws)
{
	Vector3f v;
	CHECK_THROWS(v.get(3), IndexOutOfBoundException); // valid indices are 0..2
}

TEST(Vector3f, set_invalidIndex_throws)
{
	Vector3f v;
	CHECK_THROWS(v.set(3, 1.0f), IndexOutOfBoundException); // valid indices are 0..2
}

TEST(Vector3f, equals_negativeCase)
{
	Vector3f v1(1.0f, 2.0f, 3.0f);
	Vector3f v2(9.0f, 9.0f, 9.0f);
	CHECK(!(v1 == v2));
}

TEST(Vector3f, dot_orthogonalIsZero)
{
	CHECK_NEAR_TOL(Vector3f::xAxis().dot(Vector3f::yAxis()), 0.0f, 0.00001f);
	CHECK_NEAR_TOL(Vector3f::yAxis().dot(Vector3f::zAxis()), 0.0f, 0.00001f);
}

TEST(Vector3f, cross_isAnticommutative)
{
	Vector3f v1(1.0f, 2.0f, 3.0f);
	Vector3f v2(4.0f, 5.0f, 6.0f);

	Vector3f cross12 = v1.cross(v2);
	Vector3f cross21 = v2.cross(v1);

	CHECK(cross12 == cross21 * -1.0f);
}

TEST(Vector3f, constructor_fromVector4_dropsW)
{
	Vector4f v4(1.0f, 2.0f, 3.0f, 99.0f);
	Vector3f v3(v4);
	CHECK_NEAR_TOL(v3.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v3.getY(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v3.getZ(), 3.0f, 0.0f);
}

TEST(Vector3f, constructor_fromTwoVector4Points)
{
	Vector4f a(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f b(4.0f, 6.0f, 8.0f, 1.0f);
	Vector3f ab(a, b);

	CHECK_NEAR_TOL(ab.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(ab.getY(), 5.0f, 0.0f);
	CHECK_NEAR_TOL(ab.getZ(), 7.0f, 0.0f);
}

TEST(Vector3f, constructor_fromMatrix3RowColumn)
{
	Matrix3f m(Matrix3f::identity());
	Vector3f row0(0, m);
	CHECK_NEAR_TOL(row0.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(row0.getY(), 0.0f, 0.0f);

	Vector3f col1(m, 1);
	CHECK_NEAR_TOL(col1.getX(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(col1.getY(), 1.0f, 0.0f);
}

TEST(Vector3f, V4_conversion)
{
	Vector3f v3(1.0f, 2.0f, 3.0f);
	Vector4f v4 = v3.V4();
	CHECK_NEAR_TOL(v4.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v4.getY(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v4.getZ(), 3.0f, 0.0f);
}

TEST(Vector3f, lengthSquared)
{
	Vector3f v(2.0f, 3.0f, 6.0f);
	CHECK_NEAR_TOL(v.lengthSquared(), 49.0f, 0.00001f); // 4+9+36
	CHECK_NEAR_TOL(v.lengthSquared(), v.length() * v.length(), 0.001f);
}

TEST(Vector3f, distance_distanceSquared)
{
	Vector3f v1(0.0f, 0.0f, 0.0f);
	Vector3f v2(2.0f, 3.0f, 6.0f);

	CHECK_NEAR_TOL(v1.distanceSquared(v2), 49.0f, 0.00001f);
	CHECK_NEAR_TOL(v1.distance(v2), 7.0f, 0.00001f);
	CHECK_NEAR_TOL(v1.distance(v2), (v1 - v2).length(), 0.0001f);
}

TEST(Vector3f, toArray)
{
	Vector3f v(1.0f, 2.0f, 3.0f);
	std::array<float, 3> a = v.toArray();
	CHECK_NEAR_TOL(a[0], 1.0f, 0.00001f);
	CHECK_NEAR_TOL(a[1], 2.0f, 0.00001f);
	CHECK_NEAR_TOL(a[2], 3.0f, 0.00001f);

	float dest[3] = { 0.0f, 0.0f, 0.0f };
	float* r = v.toArray(dest);
	CHECK(r == dest);
	CHECK_NEAR_TOL(dest[0], 1.0f, 0.00001f);
	CHECK_NEAR_TOL(dest[1], 2.0f, 0.00001f);
	CHECK_NEAR_TOL(dest[2], 3.0f, 0.00001f);
}

// Not ported: testVector3_equalsObject_and_hashCode (Java-only equals(Object)/null/other type and hashCode)

TEST(Vector3f, accessorConstants_areFreshIndependentCopies)
{
	// Java also checks that two calls return different references: meaningless in C++ (returned by value)
	Vector3f a1 = Vector3f::xAxis();
	Vector3f a2 = Vector3f::xAxis();
	CHECK(a1 == a2);

	// Mutating one call's result must never affect a later call's result
	a1.setX(999.0f);
	Vector3f a3 = Vector3f::xAxis();
	CHECK_NEAR_TOL(a3.getX(), 1.0f, 0.0f);

	CHECK(Vector3f::yAxis() == Vector3f(0.0f, 1.0f, 0.0f));
	CHECK(Vector3f::zAxis() == Vector3f(0.0f, 0.0f, 1.0f));
	CHECK(Vector3f::xOppAxis() == Vector3f(-1.0f, 0.0f, 0.0f));
	CHECK(Vector3f::yOppAxis() == Vector3f(0.0f, -1.0f, 0.0f));
	CHECK(Vector3f::zOppAxis() == Vector3f(0.0f, 0.0f, -1.0f));
	CHECK(Vector3f::zeroVector() == Vector3f(0.0f, 0.0f, 0.0f));
}
