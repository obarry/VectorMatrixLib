//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Unit tests, without any third-party dependency.
// Run them with: ctest --test-dir build --output-on-failure
//

#include <cmath>
#include <iostream>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"

using namespace vectormatrix;

static int nb_failures = 0;
static const float EPSILON = 1.0E-4f;

static void check(bool condition, const char* expression, const char* file, int line)
{
	if (!condition)
	{
		std::cerr << file << ":" << line << ": FAILED: " << expression << std::endl;
		nb_failures++;
	}
}

#define CHECK(expr) check((expr), #expr, __FILE__, __LINE__)
#define CHECK_NEAR(a, b) check(std::fabs((a) - (b)) <= EPSILON, #a " == " #b, __FILE__, __LINE__)

static bool equals(const Vector3f& a, const Vector3f& b)
{
	return std::fabs(a.getX() - b.getX()) <= EPSILON && std::fabs(a.getY() - b.getY()) <= EPSILON && std::fabs(a.getZ() - b.getZ()) <= EPSILON;
}

static bool equals(const Vector4f& a, const Vector4f& b)
{
	return std::fabs(a.getX() - b.getX()) <= EPSILON && std::fabs(a.getY() - b.getY()) <= EPSILON && std::fabs(a.getZ() - b.getZ()) <= EPSILON && std::fabs(a.getW() - b.getW()) <= EPSILON;
}

template <class M>
static bool equals(const M& a, const M& b, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (std::fabs(a.get(i, j) - b.get(i, j)) > EPSILON) return false;
	return true;
}

static void testVector3f()
{
	Vector3f a(1, 2, 3);
	Vector3f b(4, 5, 6);

	CHECK(equals(a + b, Vector3f(5, 7, 9)));
	CHECK(equals(b - a, Vector3f(3, 3, 3)));
	CHECK(equals(a * 2, Vector3f(2, 4, 6)));
	CHECK(equals(a / 2, Vector3f(0.5f, 1, 1.5f)));
	CHECK_NEAR(a.dot(b), 32.0f);
	CHECK(equals(a * b, Vector3f(-3, 6, -3))); // cross product

	Vector3f c(a);
	(c += b) -= a; // compound assignments return a reference and can be chained
	CHECK(equals(c, b));
	c *= 2;
	c /= 4;
	CHECK(equals(c, Vector3f(2, 2.5f, 3)));

	float array[3] = { 7, 8, 9 };
	Vector3f d(array);
	CHECK(equals(d, Vector3f(7, 8, 9)));
	d.set(1, 0);
	CHECK_NEAR(d.get(1), 0.0f);
	CHECK(std::isnan(d.get(3)));

	Vector3f e(3, 0, 4);
	CHECK_NEAR(e.length(), 5.0f);
	CHECK_NEAR(e.normalize().length(), 1.0f);
	CHECK(equals(e, Vector3f(0.6f, 0, 0.8f))); // normalize() modifies this vector

	CHECK(equals(Vector3f::interpolate(a, b, 0.5f), Vector3f(2.5f, 3.5f, 4.5f)));
	CHECK(equals(a.V4(), Vector4f(1, 2, 3, 0)));
}

static void testVector4f()
{
	Vector4f a(1, 2, 3, 4);
	Vector4f b(5, 6, 7, 8);

	CHECK(equals(a + b, Vector4f(6, 8, 10, 12)));
	CHECK(equals(b - a, Vector4f(4, 4, 4, 4)));
	CHECK(equals(a * 2, Vector4f(2, 4, 6, 8)));
	CHECK(equals(a / 2, Vector4f(0.5f, 1, 1.5f, 2)));
	CHECK_NEAR(a.dot(b), 70.0f);
	CHECK(equals(Vector4f(1, 0, 0, 0) * Vector4f(0, 1, 0, 0), Vector4f(0, 0, 1, 0))); // cross product

	Vector4f c;
	c.setX(1);
	c.setY(2);
	c.setZ(3);
	c.setW(4);
	CHECK(equals(c, a)); // setW used to modify z instead of w
	c.set(3, 9);
	CHECK_NEAR(c.getW(), 9.0f);
	CHECK_NEAR(c.getZ(), 3.0f);
	CHECK(std::isnan(c.get(4)));

	Vector4f e(0, 3, 0, 4);
	CHECK_NEAR(e.length(), 5.0f);
	e.normalize();
	CHECK(equals(e, Vector4f(0, 0.6f, 0, 0.8f)));

	CHECK(equals(Vector4f(Vector3f(1, 2, 3)), Vector4f(1, 2, 3, 0)));
	CHECK(equals(Vector4f::interpolate(a, b, 0.25f), Vector4f(2, 3, 4, 5)));
}

static void testMatrix3f()
{
	float va[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	float vb[3][3] = { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } };
	float vab[3][3] = { { 30, 24, 18 }, { 84, 69, 54 }, { 138, 114, 90 } };
	Matrix3f a(va);
	Matrix3f b(vb);

	CHECK(equals(a + b, Matrix3f(10), 3));
	CHECK(equals((a + b) - b, a, 3));
	CHECK(equals(a * b, Matrix3f(vab), 3));
	CHECK(equals(a * 2.0f, a + a, 3));

	Matrix3f c(a);
	c += b;
	c -= b; // -= used to add instead of subtract
	CHECK(equals(c, a, 3));
	c *= b;
	CHECK(equals(c, Matrix3f(vab), 3));
	c = a;
	c *= 2;
	CHECK(equals(c, a * 2.0f, 3));

	// W = A.V
	Vector3f v(1, 0, -1);
	CHECK(equals(a * v, Vector3f(-2, -2, -2)));
	CHECK(equals(v * a, a * v));
	v *= a;
	CHECK(equals(v, Vector3f(-2, -2, -2)));
}

static void testMatrix4f()
{
	float va[4][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
	Matrix4f a(va);
	Matrix4f id;
	for (int i = 0; i < Matrix4f::SIZE4; i++) id.set(i, i, 1);

	CHECK(equals(a * id, a, 4));
	CHECK(equals(id * a, a, 4));
	CHECK(equals(a + a, a * 2.0f, 4));
	CHECK(equals((a + a) - a, a, 4));

	Matrix4f c(a);
	c *= id;
	c -= a;
	CHECK(equals(c, Matrix4f(), 4));

	// W = A.V
	Vector4f v(1, 1, 1, 1);
	CHECK(equals(a * v, Vector4f(10, 26, 42, 58)));
	v *= a;
	CHECK(equals(v, Vector4f(10, 26, 42, 58)));

	// Conversions between Matrix3f and Matrix4f
	Matrix3f m3(a);
	CHECK_NEAR(m3.get(2, 2), 11.0f);
	CHECK_NEAR(m3.get(0, 1), 2.0f);
	Matrix4f m4(m3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			CHECK_NEAR(m4.get(i, j), a.get(i, j));
	for (int k = 0; k < 4; k++)
	{
		CHECK_NEAR(m4.get(k, 3), 0.0f);
		CHECK_NEAR(m4.get(3, k), 0.0f);
	}
}

int main()
{
	testVector3f();
	testVector4f();
	testMatrix3f();
	testMatrix4f();

	if (nb_failures == 0)
	{
		std::cout << "All tests passed" << std::endl;
		return 0;
	}
	std::cerr << nb_failures << " check(s) failed" << std::endl;
	return 1;
}
