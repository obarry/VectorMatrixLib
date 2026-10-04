//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestVector2.java

#include <array>
#include <vector>
#include "TestFramework.h"
#include "Vector2f.h"
#include "Exceptions.h"

using namespace vectormatrix;

TEST(Vector2f, constructors)
{
	Vector2f v0;
	CHECK_NEAR_TOL(v0.getX(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(v0.getY(), 0.0f, 0.0f);

	Vector2f v1(3.0f, 4.0f);
	CHECK_NEAR_TOL(v1.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(v1.getY(), 4.0f, 0.0f);

	// Copy constructor (the "distinct instance" check is Java reference identity, not ported)
	Vector2f v2(v1);
	CHECK_EQUAL(v2, v1);
}

TEST(Vector2f, settersGetters)
{
	Vector2f v;
	v.setX(5.0f);
	v.setY(-2.0f);
	CHECK_NEAR_TOL(v.getX(), 5.0f, 0.0f);
	CHECK_NEAR_TOL(v.getY(), -2.0f, 0.0f);
}

TEST(Vector2f, length)
{
	Vector2f v(3.0f, 4.0f);
	CHECK_NEAR_TOL(v.length(), 5.0f, 0.00001f);
}

TEST(Vector2f, lengthSquared)
{
	Vector2f v(3.0f, 4.0f);
	CHECK_NEAR_TOL(v.lengthSquared(), 25.0f, 0.00001f);
	// Consistency check: lengthSquared must always equal length()^2
	CHECK_NEAR_TOL(v.lengthSquared(), v.length() * v.length(), 0.001f);
}

TEST(Vector2f, normalize)
{
	Vector2f v(6.0f, -8.0f);
	v.normalize();
	CHECK_NEAR_TOL(v.length(), 1.0f, 0.00001f);
	// direction must be preserved: still pointing in the same quadrant
	CHECK(v.getX() > 0);
	CHECK(v.getY() < 0);
}

TEST(Vector2f, dot)
{
	Vector2f v1(1.0f, 0.0f);
	Vector2f v2(0.0f, 1.0f);
	// Orthogonal vectors: dot product is 0
	CHECK_NEAR_TOL(v1.dot(v2), 0.0f, 0.00001f);

	Vector2f v3(2.0f, 3.0f);
	Vector2f v4(4.0f, 5.0f);
	CHECK_NEAR_TOL(v3.dot(v4), 23.0f, 0.00001f); // 2*4 + 3*5
}

TEST(Vector2f, timesScalar)
{
	Vector2f v(2.0f, -3.0f);
	Vector2f r = v * 2.0f;
	CHECK_NEAR_TOL(r.getX(), 4.0f, 0.0f);
	CHECK_NEAR_TOL(r.getY(), -6.0f, 0.0f);

	v *= 2.0f;
	CHECK_NEAR_TOL(v.getX(), 4.0f, 0.0f);
	CHECK_NEAR_TOL(v.getY(), -6.0f, 0.0f);
}

TEST(Vector2f, plus)
{
	Vector2f v1(1.0f, 2.0f);
	Vector2f v2(3.0f, 4.0f);
	Vector2f v3 = v1 + v2;
	CHECK_NEAR_TOL(v3.getX(), 4.0f, 0.0f);
	CHECK_NEAR_TOL(v3.getY(), 6.0f, 0.0f);

	v1 += v2;
	CHECK_EQUAL(v1, v3);
}

TEST(Vector2f, minus)
{
	Vector2f v1(5.0f, 7.0f);
	Vector2f v2(2.0f, 3.0f);
	Vector2f v3 = v1 - v2;
	CHECK_NEAR_TOL(v3.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(v3.getY(), 4.0f, 0.0f);

	v1 -= v2;
	CHECK_EQUAL(v1, v3);
}

TEST(Vector2f, equals_instance)
{
	Vector2f v1(1.0f, 2.0f);
	Vector2f v2(1.0f, 2.0f);
	Vector2f v3(9.0f, 9.0f);

	CHECK(v1 == v2);
	CHECK(!(v1 == v3));
}

// Not ported: testVector2_equals_static, no static equals(v1, v2) in C++ (operator== is covered by equals_instance)

TEST(Vector2f, copy)
{
	// Java copy() maps to the C++ copy constructor
	Vector2f v1(1.0f, 2.0f);
	Vector2f v2(v1);

	CHECK_EQUAL(v2, v1);

	// Mutating the copy must not affect the original
	v2.setX(999.0f);
	CHECK_NEAR_TOL(v1.getX(), 1.0f, 0.0f);
}

// Not ported: testVector2_legacyEqualsNoArg_stillWorksAsCopy, legacy deprecated Java method

TEST(Vector2f, constructor_array_ok)
{
	std::vector<float> array = { 3.0f, 4.0f };
	Vector2f v(array);
	CHECK_NEAR_TOL(v.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(v.getY(), 4.0f, 0.0f);

	float carray[2] = { 3.0f, 4.0f };
	Vector2f w(carray);
	CHECK_NEAR_TOL(w.getX(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(w.getY(), 4.0f, 0.0f);
}

TEST(Vector2f, constructor_array_tooShort)
{
	std::vector<float> array = { 3.0f }; // only 1 element, Vector2f needs 2
	CHECK_THROWS(Vector2f(array), VectorArrayWrongSizeException);
}

TEST(Vector2f, indexedGetSet_valid)
{
	Vector2f v;
	v.set(0, 5.0f);
	v.set(1, 6.0f);
	CHECK_NEAR_TOL(v.get(0), 5.0f, 0.0f);
	CHECK_NEAR_TOL(v.get(1), 6.0f, 0.0f);
}

TEST(Vector2f, get_invalidIndex_throws)
{
	Vector2f v;
	CHECK_THROWS(v.get(2), IndexOutOfBoundException); // valid indices are 0..1
}

TEST(Vector2f, set_invalidIndex_throws)
{
	Vector2f v;
	CHECK_THROWS(v.set(2, 1.0f), IndexOutOfBoundException); // valid indices are 0..1
}

TEST(Vector2f, distance_distanceSquared)
{
	Vector2f v1(0.0f, 0.0f);
	Vector2f v2(3.0f, 4.0f);

	CHECK_NEAR_TOL(v1.distanceSquared(v2), 25.0f, 0.00001f);
	CHECK_NEAR_TOL(v1.distance(v2), 5.0f, 0.00001f);
	CHECK_NEAR_TOL(v1.distance(v2), (v1 - v2).length(), 0.0001f);
}

TEST(Vector2f, toArray)
{
	Vector2f v(1.0f, 2.0f);
	std::array<float, 2> a = v.toArray();
	CHECK_NEAR_TOL(a[0], 1.0f, 0.00001f);
	CHECK_NEAR_TOL(a[1], 2.0f, 0.00001f);

	float dest[2] = { 0.0f, 0.0f };
	float* r = v.toArray(dest);
	CHECK(r == dest);
	CHECK_NEAR_TOL(dest[0], 1.0f, 0.00001f);
	CHECK_NEAR_TOL(dest[1], 2.0f, 0.00001f);
}

// Not ported: testVector2_equalsObject_and_hashCode, Java-only equals(Object)/hashCode contract
