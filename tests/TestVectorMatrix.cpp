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
#include <array>
#include <string>
#include <vector>
#include <iostream>
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Vector2f.h"
#include "Matrix2f.h"
#include "Quaternionf.h"
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

static void testVector3fMethods()
{
	CHECK(Vector3f::xAxis() == Vector3f(1, 0, 0));
	CHECK(Vector3f::zOppAxis() == Vector3f(0, 0, -1));
	CHECK(Vector3f::zeroVector() == Vector3f(0, 0, 0));
	CHECK(Vector3f::xAxis().cross(Vector3f::yAxis()) == Vector3f::zAxis());

	Vector3f a(1, 2, 3);
	Vector3f b(4, 5, 6);
	CHECK(a.cross(b) == a * b);
	Vector3f c(a);
	c.crossEquals(b);
	CHECK(c == Vector3f(-3, 6, -3));

	CHECK_NEAR(a.lengthSquared(), 14.0f);
	CHECK_NEAR(a.distanceSquared(b), 27.0f);
	CHECK_NEAR(Vector3f(1, 1, 1).distance(Vector3f(1, 4, 5)), 5.0f);

	c.set(7, 8, 9);
	CHECK(c == Vector3f(7, 8, 9));
	std::array<float, 3> array = c.toArray();
	CHECK_NEAR(array[2], 9.0f);
	float dest[3];
	CHECK(c.toArray(dest) == dest);
	CHECK_NEAR(dest[0], 7.0f);

	CHECK(Vector3f(std::vector<float>{ 1, 2, 3 }) == a);
	CHECK_THROWS(Vector3f(std::vector<float>{ 1, 2 }), VectorArrayWrongSizeException);

	// From Vector4f
	CHECK(Vector3f(Vector4f(1, 2, 3, 4)) == a);
	CHECK(Vector3f(Vector4f(1, 1, 1, 1), Vector4f(2, 3, 4, 1)) == a);

	// Row and column of a matrix
	float va[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	Matrix3f m(va);
	CHECK(Vector3f(1, m) == Vector3f(4, 5, 6));
	CHECK(Vector3f(m, 1) == Vector3f(2, 5, 8));
}

static void testVector4fMethods()
{
	CHECK(Vector4f::yAxis() == Vector4f(0, 1, 0, 0));
	CHECK(Vector4f::xOppAxis() == Vector4f(-1, 0, 0, 0));
	CHECK(Vector4f::zeroPoint() == Vector4f(0, 0, 0, 1));
	CHECK(Vector4f::zeroPoint().isPoint());
	CHECK(Vector4f::zeroVector().isVector());

	Vector4f a(1, 2, 3, 0);
	Vector4f b(4, 5, 6, 0);
	CHECK(a.cross(b) == Vector4f(-3, 6, -3, 0));
	Vector4f c(a);
	c.crossEquals(b);
	CHECK(c == a * b);

	// Vector ab from 2 points
	Vector4f p1(1, 1, 1, 1);
	Vector4f p2(2, 3, 4, 1);
	CHECK(Vector4f(p1, p2) == a);
	CHECK((p1 + Vector3f(1, 2, 3)) == p2);
	CHECK((p2 - Vector3f(1, 2, 3)) == p1);

	// 3D point
	Vector4f h(2, 4, 6, 2);
	CHECK_NEAR(h.get3DX(), 1.0f);
	CHECK_NEAR(h.get3DY(), 2.0f);
	CHECK_NEAR(h.get3DZ(), 3.0f);
	CHECK(h.get3DPoint().has_value());
	CHECK(*h.get3DPoint() == Vector3f(1, 2, 3));
	CHECK(!a.get3DPoint().has_value());
	CHECK(h.V3() == Vector3f(2, 4, 6));

	c.set(1, 2, 3, 4);
	CHECK(c == Vector4f(1, 2, 3, 4));
	c.vector();
	CHECK(c.isVector());
	c.point();
	CHECK(c.isPoint());
	CHECK_NEAR(c.getW(), 1.0f);

	CHECK_NEAR(Vector4f(1, 2, 3, 4).lengthSquared(), 30.0f);
	CHECK_NEAR(Vector4f(0, 0, 0, 1).distance(Vector4f(0, 3, 4, 1)), 5.0f);
	CHECK_NEAR(Vector4f(0, 0, 0, 1).distanceSquared(Vector4f(0, 3, 4, 1)), 25.0f);

	std::array<float, 4> array = h.toArray();
	CHECK_NEAR(array[3], 2.0f);
	float dest[4];
	h.toArray(dest);
	CHECK_NEAR(dest[1], 4.0f);

	CHECK(Vector4f(std::vector<float>{ 1, 2, 3, 0 }) == a);
	CHECK_THROWS(Vector4f(std::vector<float>{ 1, 2, 3 }), VectorArrayWrongSizeException);

	float va[4][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
	Matrix4f m(va);
	CHECK(Vector4f(2, m) == Vector4f(9, 10, 11, 12));
	CHECK(Vector4f(m, 2) == Vector4f(3, 7, 11, 15));
}

static void testMatrix3fMethods()
{
	float va[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	Matrix3f a(va);

	CHECK(Matrix3f::identity().isIdentity());
	CHECK(!a.isIdentity());
	CHECK(a * Matrix3f::identity() == a);
	Matrix3f d;
	d.setDiagonal(2);
	CHECK(d == Matrix3f::identity() * 2.0f);

	CHECK(a.getRow(0) == Vector3f(1, 2, 3));
	CHECK(a.getColumn(0) == Vector3f(1, 4, 7));
	CHECK_THROWS(a.getRow(3), IndexOutOfBoundException);
	CHECK_THROWS(a.getColumn(-1), IndexOutOfBoundException);
	Matrix3f b(a);
	b.setRow(1, Vector3f(0, 0, 0));
	CHECK(b.getRow(1) == Vector3f(0, 0, 0));
	b.setColumn(2, Vector3f(1, 1, 1));
	CHECK(b.getColumn(2) == Vector3f(1, 1, 1));
	CHECK_THROWS(b.setRow(3, Vector3f()), IndexOutOfBoundException);
	CHECK_THROWS(b.setColumn(3, Vector3f()), IndexOutOfBoundException);

	std::vector<std::vector<float>> array = a.getArray();
	CHECK(array.size() == 3 && array[2].size() == 3);
	CHECK_NEAR(array[2][1], 8.0f);
	array[2][1] = 0; // a copy
	CHECK_NEAR(a.get(2, 1), 8.0f);
	b.setArray(array);
	CHECK_NEAR(b.get(2, 1), 0.0f);
	CHECK_THROWS(b.setArray(std::vector<std::vector<float>>(2, std::vector<float>(3))), MatrixArrayWrongSizeException);
	CHECK_THROWS(b.setArray(std::vector<std::vector<float>>(3, std::vector<float>(4))), MatrixArrayWrongSizeException);

	CHECK_NEAR(a.trace(), 15.0f);
	CHECK_NEAR(a.determinant(), 0.0f);
	CHECK_NEAR(Matrix3f::identity().determinant(), 1.0f);

	float vt[3][3] = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 } };
	CHECK(a.transpose() == Matrix3f(vt));
	b = a;
	b.transposeEquals();
	CHECK(b == Matrix3f(vt));

	// Inverse
	float vi[3][3] = { { 2, -1, 0 }, { -1, 2, -1 }, { 0, -1, 2 } };
	Matrix3f m(vi);
	CHECK_NEAR(m.determinant(), 4.0f);
	Matrix3f inv = m.inverse();
	CHECK((m * inv).isIdentity());
	CHECK((inv * m).isIdentity());
	CHECK(inv.inverse() == m);
	CHECK(Matrix3f::identity().inverse().isIdentity());
	CHECK_THROWS(a.inverse(), NotInvertibleMatrixException);
}

static void testMatrix4fMethods()
{
	CHECK(Matrix4f::identity().isIdentity());
	CHECK_NEAR(Matrix4f::identity().trace(), 4.0f);
	CHECK_NEAR(Matrix4f::identity().determinant(), 1.0f);

	// Same matrix as Aventura testMatrix4_inverse1 and testMatrix4_inverse2
	float va[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			va[i][j] = (i > j) ? 0.0f : static_cast<float>(10 - 2 * i - j);
	Matrix4f a(va);
	CHECK_NEAR(a.determinant(), 280.0f); // triangular: 10 * 7 * 4 * 1
	Matrix4f inv = a.inverse();
	CHECK(inv.inverse() == a);
	CHECK(inv * a == Matrix4f::identity());

	// Same matrix as Aventura testMatrix4_inverse_precision_generalCase
	float vg[4][4] = { { 4, 7, 2, 1 }, { 3, 5, 1, 2 }, { 2, 3, 1, 0 }, { 1, 0, 2, 3 } };
	Matrix4f g(vg);
	CHECK((g * g.inverse()).isIdentity());
	CHECK_NEAR(g.determinant(), g.transpose().determinant());

	// Singular matrix (last row is 0)
	Matrix4f singular(a);
	singular.setRow(3, Vector4f());
	CHECK_NEAR(singular.determinant(), 0.0f);
	CHECK_THROWS(singular.inverse(), NotInvertibleMatrixException);

	CHECK(a.getRow(1) == Vector4f(0, 7, 6, 5));
	CHECK(a.getColumn(3) == Vector4f(7, 5, 3, 1));
	CHECK_THROWS(a.getRow(4), IndexOutOfBoundException);
	CHECK(a.transpose().getRow(3) == a.getColumn(3));
	Matrix4f t(a);
	t.transposeEquals();
	CHECK(t == a.transpose());

	Matrix3f m3 = a.getMatrix3();
	CHECK(m3.getRow(0) == Vector3f(10, 9, 8));
	CHECK(m3 == Matrix3f(a));

	std::vector<std::vector<float>> array = a.getArray();
	Matrix4f b;
	b.setArray(array);
	CHECK(b == a);
	CHECK_THROWS(b.setArray(std::vector<std::vector<float>>(3, std::vector<float>(3))), MatrixArrayWrongSizeException);
}

static void testVector2f()
{
	Vector2f a(1, 2);
	Vector2f b(3, 5);

	CHECK(a + b == Vector2f(4, 7));
	CHECK(b - a == Vector2f(2, 3));
	CHECK(a * 2 == Vector2f(2, 4));
	CHECK(b / 2 == Vector2f(1.5f, 2.5f));
	CHECK_NEAR(a.dot(b), 13.0f);
	CHECK(a != b);

	Vector2f c(a);
	(c += b) -= a;
	CHECK(c == b);
	c *= 2;
	c /= 2;
	CHECK(c == b);

	CHECK_NEAR(Vector2f(3, 4).length(), 5.0f);
	CHECK_NEAR(Vector2f(3, 4).lengthSquared(), 25.0f);
	CHECK_NEAR(a.distance(Vector2f(4, 6)), 5.0f);
	CHECK_NEAR(a.distanceSquared(Vector2f(4, 6)), 25.0f);
	Vector2f n(3, 4);
	CHECK(n.normalize() == Vector2f(0.6f, 0.8f));
	CHECK(n == Vector2f(0.6f, 0.8f)); // normalize() modifies this vector

	c.setX(7);
	c.setY(8);
	CHECK(c == Vector2f(7, 8));
	c.set(1, 0);
	CHECK_NEAR(c.getY(), 0.0f);
	CHECK_THROWS(c.get(2), IndexOutOfBoundException);
	CHECK_THROWS(c.set(-1, 0), IndexOutOfBoundException);

	std::array<float, 2> array = b.toArray();
	CHECK_NEAR(array[1], 5.0f);
	float dest[2];
	b.toArray(dest);
	CHECK_NEAR(dest[0], 3.0f);
	float arr[2] = { 1, 2 };
	CHECK(Vector2f(arr) == a);
	CHECK(Vector2f(std::vector<float>{ 1, 2 }) == a);
	CHECK_THROWS(Vector2f(std::vector<float>{ 1 }), VectorArrayWrongSizeException);
	CHECK(Vector2f::interpolate(a, b, 0.5f) == Vector2f(2, 3.5f));

	// W = A.V
	float va[2][2] = { { 1, 2 }, { 3, 4 } };
	Matrix2f m(va);
	CHECK(m * a == Vector2f(5, 11));
	CHECK(a * m == m * a);
	c = a;
	c *= m;
	CHECK(c == Vector2f(5, 11));
}

static void testMatrix2f()
{
	float va[2][2] = { { 1, 2 }, { 3, 4 } };
	float vb[2][2] = { { 5, 6 }, { 7, 8 } };
	float vab[2][2] = { { 19, 22 }, { 43, 50 } };
	Matrix2f a(va);
	Matrix2f b(vb);

	CHECK(a + b == Matrix2f(vab) - Matrix2f(vab) + a + b);
	CHECK((a + b) - b == a);
	CHECK(a * b == Matrix2f(vab));
	CHECK(a * 2.0f == a + a);
	Matrix2f c(a);
	c *= b;
	CHECK(c == Matrix2f(vab));
	c -= Matrix2f(vab);
	CHECK(c == Matrix2f());

	CHECK(Matrix2f::identity().isIdentity());
	CHECK(a * Matrix2f::identity() == a);
	Matrix2f d;
	d.setDiagonal(3);
	CHECK(d == Matrix2f::identity() * 3.0f);

	CHECK(a.getRow(1) == Vector2f(3, 4));
	CHECK(a.getColumn(1) == Vector2f(2, 4));
	CHECK_THROWS(a.getRow(2), IndexOutOfBoundException);
	c = a;
	c.setRow(0, Vector2f(9, 9));
	c.setColumn(1, Vector2f(0, 0));
	CHECK(c.getRow(0) == Vector2f(9, 0));
	CHECK(c.getRow(1) == Vector2f(3, 0));
	CHECK_THROWS(c.setColumn(2, Vector2f()), IndexOutOfBoundException);

	std::vector<std::vector<float>> array = a.getArray();
	Matrix2f e;
	e.setArray(array);
	CHECK(e == a);
	CHECK_THROWS(e.setArray(std::vector<std::vector<float>>(3, std::vector<float>(2))), MatrixArrayWrongSizeException);

	CHECK_NEAR(a.trace(), 5.0f);
	CHECK_NEAR(a.determinant(), -2.0f);
	float vt[2][2] = { { 1, 3 }, { 2, 4 } };
	CHECK(a.transpose() == Matrix2f(vt));
	c = a;
	c.transposeEquals();
	CHECK(c == Matrix2f(vt));

	float vi[2][2] = { { -2, 1 }, { 1.5f, -0.5f } };
	CHECK(a.inverse() == Matrix2f(vi));
	CHECK((a * a.inverse()).isIdentity());
	float vs[2][2] = { { 1, 2 }, { 2, 4 } };
	CHECK_THROWS(Matrix2f(vs).inverse(), NotInvertibleMatrixException);
}

static void testQuaternionf()
{
	const float PI = 3.14159265f;

	Quaternionf id;
	CHECK(id == Quaternionf(0, 0, 0, 1));
	CHECK(id.toMatrix3().isIdentity());
	CHECK(id.toMatrix4().isIdentity());

	// Rotation of 90 degrees around z: x axis goes to y axis
	Quaternionf rz(Vector3f(0, 0, 2), PI / 2); // the axis is normalized
	CHECK_NEAR(rz.length(), 1.0f);
	CHECK(rz.toMatrix3() * Vector3f::xAxis() == Vector3f::yAxis());
	CHECK(rz.toMatrix4() * Vector4f::xAxis() == Vector4f::yAxis());
	CHECK_NEAR(rz.toMatrix4().get(3, 3), 1.0f);
	CHECK_NEAR(rz.toMatrix3().determinant(), 1.0f);

	// Back and forth with rotation matrices
	CHECK(Quaternionf(rz.toMatrix3()) == rz);
	CHECK(Quaternionf(rz.toMatrix4()) == rz);
	Quaternionf rx(Vector3f::xAxis(), PI); // trace < 0 branches
	CHECK(Quaternionf(rx.toMatrix3()) == rx);
	Quaternionf ry(Vector3f::yAxis(), 0.9f * PI);
	CHECK(Quaternionf(ry.toMatrix3()) == ry);
	Quaternionf rzz(Vector3f::zAxis(), 0.9f * PI);
	CHECK(Quaternionf(rzz.toMatrix3()) == rzz);

	// Composition: 2 rotations of 90 degrees = 1 rotation of 180 degrees
	Quaternionf r180(Vector3f::zAxis(), PI);
	CHECK(rz * rz == r180);
	Quaternionf q(rz);
	q *= rz;
	CHECK(q == r180);
	CHECK((rz * rz).toMatrix3() == rz.toMatrix3() * rz.toMatrix3());

	// Conjugate and inverse
	CHECK(rz.conjugate() == Quaternionf(-rz.getX(), -rz.getY(), -rz.getZ(), rz.getW()));
	CHECK(rz * rz.inverse() == id);
	Quaternionf big(1, 2, 3, 4);
	CHECK(big * big.inverse() == id);
	CHECK_NEAR(big.dot(big), big.lengthSquared());
	CHECK_NEAR(big.normalize().length(), 1.0f);

	// Axis and angle
	Vector3f axis;
	CHECK_NEAR(rz.toAxisAngle(axis), PI / 2);
	CHECK(axis == Vector3f::zAxis());
	CHECK_NEAR(id.toAxisAngle(axis), 0.0f);
	CHECK(axis == Vector3f::xAxis()); // no meaningful axis for a null rotation

	// Slerp
	Quaternionf r120(Vector3f::zAxis(), 2 * PI / 3);
	Quaternionf r60(Vector3f::zAxis(), PI / 3);
	CHECK(Quaternionf::slerp(id, r120, 0) == id);
	CHECK(Quaternionf::slerp(id, r120, 1) == r120);
	CHECK(Quaternionf::slerp(id, r120, 0.5f) == r60);
	CHECK(Quaternionf::slerp(rz, rz, 0.3f) == rz);
	// q and -q are the same rotation: slerp takes the shorter path
	Quaternionf negRz(-rz.getX(), -rz.getY(), -rz.getZ(), -rz.getW());
	CHECK(Quaternionf::slerp(id, negRz, 1) == rz);

	// Accessors
	q.set(0, 1);
	q.set(3, 2);
	CHECK_NEAR(q.getX(), 1.0f);
	CHECK_NEAR(q.get(3), 2.0f);
	CHECK_THROWS(q.get(4), IndexOutOfBoundException);
	CHECK_THROWS(q.set(-1, 0), IndexOutOfBoundException);
}

int main()
{
	testMathTools();
	testVector3f();
	testVector4f();
	testMatrix3f();
	testMatrix4f();
	testVector3fMethods();
	testVector4fMethods();
	testMatrix3fMethods();
	testMatrix4fMethods();
	testVector2f();
	testMatrix2f();
	testQuaternionf();

	if (nb_failures == 0)
	{
		std::cout << "All tests passed" << std::endl;
		return 0;
	}
	std::cerr << nb_failures << " check(s) failed" << std::endl;
	return 1;
}
