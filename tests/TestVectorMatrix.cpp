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
#include <string>
#include <iostream>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "MathTools.h"
#include "Exceptions.h"

using namespace vectormatrix;

static int nb_failures = 0;

static void check(bool condition, const char* expression, const char* file, int line)
{
	if (!condition)
	{
		std::cerr << file << ":" << line << ": FAILED: " << expression << std::endl;
		nb_failures++;
	}
}

#define CHECK(expr) check((expr), #expr, __FILE__, __LINE__)
#define CHECK_THROWS(expr, Exception) \
	do { bool thrown = false; try { (void)(expr); } catch (const Exception&) { thrown = true; } check(thrown, #expr " throws " #Exception, __FILE__, __LINE__); } while (0)
#define CHECK_NEAR(a, b) check(MathTools::equals((a), (b)), #a " == " #b, __FILE__, __LINE__)

static void testMathTools()
{
	CHECK(MathTools::equals(1.0f, 1.0f + EPSILON / 2));
	CHECK(!MathTools::equals(1.0f, 1.0f + EPSILON * 2));

	CHECK(Vector3f(1, 2, 3) == Vector3f(1, 2, 3.00001f));
	CHECK(Vector3f(1, 2, 3) != Vector3f(1, 2, 3.01f));
	CHECK(Vector4f(1, 2, 3, 4) == Vector4f(1, 2, 3, 4.00001f));
	CHECK(Vector4f(1, 2, 3, 4) != Vector4f(1, 2, 3, 4.01f));
	Matrix3f m3(1);
	Matrix3f n3(1);
	n3.set(2, 1, 1.00001f);
	CHECK(m3 == n3);
	n3.set(2, 1, 1.01f);
	CHECK(m3 != n3);
	Matrix4f m4(1);
	Matrix4f n4(1);
	n4.set(3, 3, 1.01f);
	CHECK(m4 != n4);

	try
	{
		throw NotInvertibleMatrixException();
	}
	catch (const Vector3DException& e)
	{
		CHECK(std::string(e.what()) == "Matrix is not invertible");
	}
}

static void testVector3f()
{
	Vector3f a(1, 2, 3);
	Vector3f b(4, 5, 6);

	CHECK(a + b == Vector3f(5, 7, 9));
	CHECK(b - a == Vector3f(3, 3, 3));
	CHECK(a * 2 == Vector3f(2, 4, 6));
	CHECK(a / 2 == Vector3f(0.5f, 1, 1.5f));
	CHECK_NEAR(a.dot(b), 32.0f);
	CHECK(a * b == Vector3f(-3, 6, -3)); // cross product

	Vector3f c(a);
	(c += b) -= a; // compound assignments return a reference and can be chained
	CHECK(c == b);
	c *= 2;
	c /= 4;
	CHECK(c == Vector3f(2, 2.5f, 3));

	float array[3] = { 7, 8, 9 };
	Vector3f d(array);
	CHECK(d == Vector3f(7, 8, 9));
	d.set(1, 0);
	CHECK_NEAR(d.get(1), 0.0f);
	CHECK_THROWS(d.get(3), IndexOutOfBoundException);
	CHECK_THROWS(d.set(-1, 0), IndexOutOfBoundException);

	Vector3f e(3, 0, 4);
	CHECK_NEAR(e.length(), 5.0f);
	CHECK_NEAR(e.normalize().length(), 1.0f);
	CHECK(e == Vector3f(0.6f, 0, 0.8f)); // normalize() modifies this vector

	CHECK(Vector3f::interpolate(a, b, 0.5f) == Vector3f(2.5f, 3.5f, 4.5f));
	CHECK(a.V4() == Vector4f(1, 2, 3, 0));
}

static void testVector4f()
{
	Vector4f a(1, 2, 3, 4);
	Vector4f b(5, 6, 7, 8);

	CHECK(a + b == Vector4f(6, 8, 10, 12));
	CHECK(b - a == Vector4f(4, 4, 4, 4));
	CHECK(a * 2 == Vector4f(2, 4, 6, 8));
	CHECK(a / 2 == Vector4f(0.5f, 1, 1.5f, 2));
	CHECK_NEAR(a.dot(b), 70.0f);
	CHECK(Vector4f(1, 0, 0, 0) * Vector4f(0, 1, 0, 0) == Vector4f(0, 0, 1, 0)); // cross product

	Vector4f c;
	c.setX(1);
	c.setY(2);
	c.setZ(3);
	c.setW(4);
	CHECK(c == a); // setW used to modify z instead of w
	c.set(3, 9);
	CHECK_NEAR(c.getW(), 9.0f);
	CHECK_NEAR(c.getZ(), 3.0f);
	CHECK_THROWS(c.get(4), IndexOutOfBoundException);
	CHECK_THROWS(c.set(4, 0), Vector3DException); // caught through the base class

	Vector4f e(0, 3, 0, 4);
	CHECK_NEAR(e.length(), 5.0f);
	e.normalize();
	CHECK(e == Vector4f(0, 0.6f, 0, 0.8f));

	CHECK(Vector4f(Vector3f(1, 2, 3)) == Vector4f(1, 2, 3, 0));
	CHECK(Vector4f::interpolate(a, b, 0.25f) == Vector4f(2, 3, 4, 5));
}

static void testMatrix3f()
{
	float va[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	float vb[3][3] = { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } };
	float vab[3][3] = { { 30, 24, 18 }, { 84, 69, 54 }, { 138, 114, 90 } };
	Matrix3f a(va);
	Matrix3f b(vb);

	CHECK(a + b == Matrix3f(10));
	CHECK((a + b) - b == a);
	CHECK(a * b == Matrix3f(vab));
	CHECK(a * 2.0f == a + a);

	Matrix3f c(a);
	c += b;
	c -= b; // -= used to add instead of subtract
	CHECK(c == a);
	c *= b;
	CHECK(c == Matrix3f(vab));
	c = a;
	c *= 2;
	CHECK(c == a * 2.0f);

	// W = A.V
	Vector3f v(1, 0, -1);
	CHECK(a * v == Vector3f(-2, -2, -2));
	CHECK(v * a == a * v);
	v *= a;
	CHECK(v == Vector3f(-2, -2, -2));
}

static void testMatrix4f()
{
	float va[4][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
	Matrix4f a(va);
	Matrix4f id;
	for (int i = 0; i < Matrix4f::SIZE4; i++) id.set(i, i, 1);

	CHECK(a * id == a);
	CHECK(id * a == a);
	CHECK(a + a == a * 2.0f);
	CHECK((a + a) - a == a);

	Matrix4f c(a);
	c *= id;
	c -= a;
	CHECK(c == Matrix4f());

	// W = A.V
	Vector4f v(1, 1, 1, 1);
	CHECK(a * v == Vector4f(10, 26, 42, 58));
	v *= a;
	CHECK(v == Vector4f(10, 26, 42, 58));

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
	testMathTools();
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
