//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestVector4.java
//

#include <array>
#include <optional>
#include <vector>
#include "TestFramework.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix4f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(Vector4f, constructors_basic)
{
	Vector4f v0;
	CHECK_NEAR_TOL(v0.getX(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(v0.getY(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(v0.getZ(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(v0.getW(), 0.0f, 0.0f);

	Vector4f v1(2.0f);
	CHECK_NEAR_TOL(v1.getX(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v1.getW(), 2.0f, 0.0f);

	Vector4f v2(1.0f, 2.0f, 3.0f, 1.0f);
	CHECK_NEAR_TOL(v2.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v2.getY(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v2.getZ(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(v2.getW(), 1.0f, 0.0f);

	// Copy constructor (reference identity check of the Java test is meaningless by value)
	Vector4f v3(v2);
	CHECK_EQUAL(v3, v2);
}

TEST(Vector4f, constructor_array_ok)
{
	float array[] = { 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4f v(array);
	CHECK_NEAR_TOL(v.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v.getW(), 4.0f, 0.0f);

	std::vector<float> vec = { 1.0f, 2.0f, 3.0f, 4.0f };
	Vector4f w(vec);
	CHECK_NEAR_TOL(w.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(w.getW(), 4.0f, 0.0f);
}

TEST(Vector4f, constructor_array_tooShort)
{
	std::vector<float> array = { 1.0f, 2.0f, 3.0f }; // only 3 elements, Vector4f needs 4
	CHECK_THROWS(Vector4f(array), VectorArrayWrongSizeException);
}

TEST(Vector4f, constructor_fromVector3)
{
	Vector3f v3(1.0f, 2.0f, 3.0f);
	Vector4f v4(v3);
	CHECK_NEAR_TOL(v4.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v4.getY(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v4.getZ(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(v4.getW(), 0.0f, 0.0f); // built from a Vector3f: w defaults to 0 (a vector, not a point)
}

TEST(Vector4f, constructor_fromTwoPoints)
{
	Vector4f a(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f b(4.0f, 5.0f, 6.0f, 1.0f);
	Vector4f ab(a, b);

	CHECK_NEAR_TOL(ab.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(ab.getY(), 4.0f, 0.0f);
	CHECK_NEAR_TOL(ab.getZ(), 5.0f, 0.0f);
	CHECK_NEAR_TOL(ab.getW(), 0.0f, 0.0f); // both points have w=1: ab is a direction, not a point
}

TEST(Vector4f, constructor_fromMatrixRowColumn)
{
	Matrix4f m(Matrix4f::identity());
	Vector4f row0(0, m);
	CHECK_NEAR_TOL(row0.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(row0.getY(), 0.0f, 0.0f);

	Vector4f col0(m, 0);
	CHECK_NEAR_TOL(col0.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(col0.getY(), 0.0f, 0.0f);
}

TEST(Vector4f, indexedGetSet_valid)
{
	Vector4f v;
	v.set(0, 1.0f);
	v.set(1, 2.0f);
	v.set(2, 3.0f);
	v.set(3, 4.0f);

	CHECK_NEAR_TOL(v.get(0), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v.get(1), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v.get(2), 3.0f, 0.0f);
	CHECK_NEAR_TOL(v.get(3), 4.0f, 0.0f);
}

TEST(Vector4f, get_invalidIndex_throws)
{
	Vector4f v;
	CHECK_THROWS(v.get(4), IndexOutOfBoundException); // valid indices are 0..3
}

TEST(Vector4f, set_invalidIndex_throws)
{
	Vector4f v;
	CHECK_THROWS(v.set(4, 1.0f), IndexOutOfBoundException); // valid indices are 0..3
}

TEST(Vector4f, get3DConversions)
{
	Vector4f v(4.0f, 6.0f, 8.0f, 2.0f);
	CHECK_NEAR_TOL(v.get3DX(), 2.0f, 0.00001f);
	CHECK_NEAR_TOL(v.get3DY(), 3.0f, 0.00001f);
	CHECK_NEAR_TOL(v.get3DZ(), 4.0f, 0.00001f);

	std::optional<Vector3f> p = v.get3DPoint();
	if (CHECK(p.has_value()))
	{
		CHECK_NEAR_TOL(p->getX(), 2.0f, 0.00001f);
		CHECK_NEAR_TOL(p->getY(), 3.0f, 0.00001f);
		CHECK_NEAR_TOL(p->getZ(), 4.0f, 0.00001f);
	}
}

TEST(Vector4f, get3DPoint_nullWhenW0)
{
	Vector4f v(1.0f, 2.0f, 3.0f, 0.0f);
	CHECK(!v.get3DPoint().has_value());
}

TEST(Vector4f, length_normalize)
{
	Vector4f v(1.0f, 2.0f, 2.0f, 0.0f);
	CHECK_NEAR_TOL(v.length(), 3.0f, 0.00001f); // sqrt(1+4+4) = 3

	v.normalize();
	CHECK_NEAR_TOL(v.length(), 1.0f, 0.00001f);
}

TEST(Vector4f, equals)
{
	Vector4f v1(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4f v2(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4f v3(9.0f, 9.0f, 9.0f, 9.0f);

	CHECK(v1 == v2);
	CHECK(!(v1 == v3));
}

TEST(Vector4f, plusMinus_vector4)
{
	Vector4f v1(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4f v2(4.0f, 5.0f, 6.0f, 0.0f);

	Vector4f sum = v1 + v2;
	CHECK_NEAR_TOL(sum.getX(), 5.0f, 0.0f);
	CHECK_NEAR_TOL(sum.getY(), 7.0f, 0.0f);
	CHECK_NEAR_TOL(sum.getZ(), 9.0f, 0.0f);
	CHECK_NEAR_TOL(sum.getW(), 1.0f, 0.0f);

	Vector4f diff = v1 - v2;
	CHECK_NEAR_TOL(diff.getX(), -3.0f, 0.0f);

	v1 += v2;
	CHECK_EQUAL(v1, sum);
}

TEST(Vector4f, plusMinus_vector3_movesPointKeepingW)
{
	Vector4f point(1.0f, 1.0f, 1.0f, 1.0f); // a point
	Vector3f displacement(2.0f, 3.0f, 4.0f);

	Vector4f moved = point + displacement;
	CHECK_NEAR_TOL(moved.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(moved.getY(), 4.0f, 0.0f);
	CHECK_NEAR_TOL(moved.getZ(), 5.0f, 0.0f);
	CHECK_NEAR_TOL(moved.getW(), 1.0f, 0.0f); // w must be left unchanged (still a point)

	Vector4f movedBack = moved - displacement;
	CHECK_EQUAL(movedBack, point);
}

TEST(Vector4f, dot)
{
	Vector4f v1(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4f v2(5.0f, 6.0f, 7.0f, 8.0f);
	CHECK_NEAR_TOL(v1.dot(v2), 70.0f, 0.00001f); // 5+12+21+32
}

TEST(Vector4f, timesScalar)
{
	Vector4f v(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4f r = v * 2.0f;
	CHECK_NEAR_TOL(r.getX(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(r.getW(), 8.0f, 0.0f);

	v *= 2.0f;
	CHECK_EQUAL(v, r);
}

TEST(Vector4f, crossProduct_forcesW0)
{
	Vector4f x(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4f y(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4f z = x.cross(y);

	CHECK_NEAR_TOL(z.getX(), 0.0f, 0.00001f);
	CHECK_NEAR_TOL(z.getY(), 0.0f, 0.00001f);
	CHECK_NEAR_TOL(z.getZ(), 1.0f, 0.00001f);
	CHECK_NEAR_TOL(z.getW(), 0.0f, 0.0f);
}

TEST(Vector4f, timesMatrix4_identity)
{
	Vector4f v(3.0f, -2.0f, 5.0f, 1.0f);
	Vector4f r = v * Matrix4f::identity();
	CHECK_EQUAL(r, v);

	v *= Matrix4f::identity();
	CHECK_EQUAL(v, r);
}

TEST(Vector4f, V3_conversion)
{
	Vector4f v4(1.0f, 2.0f, 3.0f, 9.0f);
	Vector3f v3 = v4.V3();
	CHECK_NEAR_TOL(v3.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(v3.getY(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(v3.getZ(), 3.0f, 0.0f); // w is dropped
}

TEST(Vector4f, pointVectorSemantics)
{
	Vector4f v(1.0f, 2.0f, 3.0f, 0.0f);
	CHECK(v.isVector());
	CHECK(!v.isPoint());

	v.point();
	CHECK(v.isPoint());
	CHECK(!v.isVector());

	v.vector();
	CHECK(v.isVector());

	v.point();
	CHECK(v.isPoint());

	v.vector();
	CHECK(v.isVector());
	CHECK_NEAR_TOL(v.getW(), 0.0f, 0.0f);
}

TEST(Vector4f, lengthSquared)
{
	Vector4f v(1.0f, 2.0f, 2.0f, 0.0f);
	CHECK_NEAR_TOL(v.lengthSquared(), 9.0f, 0.00001f); // 1+4+4
	CHECK_NEAR_TOL(v.lengthSquared(), v.length() * v.length(), 0.001f);
}

TEST(Vector4f, distance_distanceSquared)
{
	Vector4f v1(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4f v2(1.0f, 2.0f, 2.0f, 0.0f);

	CHECK_NEAR_TOL(v1.distanceSquared(v2), 9.0f, 0.00001f);
	CHECK_NEAR_TOL(v1.distance(v2), 3.0f, 0.00001f);

	// Consistency with the allocating equivalent (v1 - v2).length()
	CHECK_NEAR_TOL(v1.distance(v2), (v1 - v2).length(), 0.0001f);
}

TEST(Vector4f, toArray)
{
	Vector4f v(1.0f, 2.0f, 3.0f, 4.0f);
	std::array<float, 4> a = v.toArray();
	const float expected[] = { 1.0f, 2.0f, 3.0f, 4.0f };
	for (int i = 0; i < 4; i++)
		CHECK_NEAR_TOL(a[i], expected[i], 0.00001f);

	float dest[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float* r = v.toArray(dest);
	CHECK(r == dest); // must fill and return the same array, not allocate a new one
	for (int i = 0; i < 4; i++)
		CHECK_NEAR_TOL(dest[i], expected[i], 0.00001f);
}

// Not ported: equalsObject_and_hashCode (Java-only equals(Object)/null/other type and hashCode)

TEST(Vector4f, accessorConstants_areFreshIndependentCopies)
{
	Vector4f a1 = Vector4f::xAxis();
	Vector4f a2 = Vector4f::xAxis();
	CHECK(a1 == a2);

	// Mutating one call's result must never affect a later call's result
	a1.setX(999.0f);
	Vector4f a3 = Vector4f::xAxis();
	CHECK_NEAR_TOL(a3.getX(), 1.0f, 0.0f);

	CHECK(Vector4f::yAxis() == Vector4f(0.0f, 1.0f, 0.0f, 0.0f));
	CHECK(Vector4f::zAxis() == Vector4f(0.0f, 0.0f, 1.0f, 0.0f));
	CHECK(Vector4f::xOppAxis() == Vector4f(-1.0f, 0.0f, 0.0f, 0.0f));
	CHECK(Vector4f::yOppAxis() == Vector4f(0.0f, -1.0f, 0.0f, 0.0f));
	CHECK(Vector4f::zOppAxis() == Vector4f(0.0f, 0.0f, -1.0f, 0.0f));
	CHECK(Vector4f::zeroVector() == Vector4f(0.0f, 0.0f, 0.0f, 0.0f));
	CHECK(Vector4f::zeroPoint() == Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
}
