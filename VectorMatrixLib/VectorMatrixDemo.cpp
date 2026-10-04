//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Console tour of the library: each section shows a typical use of the API
// on a small geometric example, and prints what happens step by step.
//

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Constants.h"
#include "Exceptions.h"
#include "GeometryTools.h"
#include "Matrix2f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Quaternionf.h"
#include "Tools.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

using namespace vectormatrix;

namespace
{
	const float PI = 3.14159265358979f;

	float degrees(float radians) { return radians * 180 / PI; }
	float radians(float degrees) { return degrees * PI / 180; }

	// Fixed width number, without the "-0.000" of tiny negative values
	std::string num(float f)
	{
		if (std::fabs(f) < 0.0005f) f = 0;
		std::ostringstream s;
		s << std::fixed << std::setprecision(3) << std::setw(7) << f;
		return s.str();
	}

	// Compact one line representations (the library operator<< prints on several lines)
	std::string str(const Vector2f& v) { return "(" + num(v.getX()) + "," + num(v.getY()) + " )"; }
	std::string str(const Vector3f& v) { return "(" + num(v.getX()) + "," + num(v.getY()) + "," + num(v.getZ()) + " )"; }
	std::string str(const Vector4f& v) { return "(" + num(v.getX()) + "," + num(v.getY()) + "," + num(v.getZ()) + "," + num(v.getW()) + " )"; }
	std::string str(const Quaternionf& q) { return "[" + num(q.getX()) + "," + num(q.getY()) + "," + num(q.getZ()) + "," + num(q.getW()) + " ]"; }

	// Print a matrix of any size, aligned under a label
	void print(const std::string& label, const std::vector<std::vector<float>>& a)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			std::cout << "  " << (i == 0 ? label : std::string(label.size(), ' ')) << (i == 0 ? " = | " : "   | ");
			for (float f : a[i]) std::cout << num(f) << " ";
			std::cout << "|" << std::endl;
		}
	}
	void print(const std::string& label, const Matrix2f& m) { print(label, m.getArray()); }
	void print(const std::string& label, const Matrix3f& m) { print(label, m.getArray()); }
	void print(const std::string& label, const Matrix4f& m) { print(label, m.getArray()); }

	void title(const std::string& t)
	{
		std::cout << std::endl << std::string(70, '=') << std::endl;
		std::cout << "  " << t << std::endl;
		std::cout << std::string(70, '=') << std::endl;
	}

	void line(const std::string& label, const std::string& value)
	{
		std::cout << "  " << std::left << std::setw(34) << label << std::right << value << std::endl;
	}

	std::string yes(bool b) { return b ? "yes" : "no"; }

	// Rotation of angle around the z axis, as a 4x4 matrix built from a quaternion
	Matrix4f rotationZ(float angle)
	{
		return Quaternionf(Vector3f::zAxis(), angle).toMatrix4();
	}

	// Translation by t, as a 4x4 matrix (acts on points, not on vectors)
	Matrix4f translation(const Vector3f& t)
	{
		Matrix4f m = Matrix4f::identity();
		m.setColumn(3, Vector4f(t.getX(), t.getY(), t.getZ(), 1));
		return m;
	}

	// Uniform scaling by s, as a 4x4 matrix
	Matrix4f scaling(float s)
	{
		Matrix4f m = Matrix4f::identity();
		m.set(0, 0, s);
		m.set(1, 1, s);
		m.set(2, 2, s);
		return m;
	}
}

static void demoVectors()
{
	title("1. Vectors in 3D: Vector3f");

	Vector3f a(1, 2, 3);
	Vector3f b(4, 5, 6);
	line("a", str(a));
	line("b", str(b));
	line("a + b", str(a + b));
	line("b - a", str(b - a));
	line("a * 2", str(a * 2));
	line("a . b (dot product)", num(a.dot(b)));
	line("a ^ b (cross product)", str(a.cross(b)));
	line("(a ^ b) . a (orthogonal to a)", num(a.cross(b).dot(a)));
	line("|a| (length)", num(a.length()));
	line("distance(a, b)", num(a.distance(b)));

	Vector3f n = a;
	n.normalize();
	line("a normalized", str(n));
	line("length after normalize", num(n.length()));

	std::cout << std::endl << "  Right-handed axes: x ^ y = z, y ^ z = x, z ^ x = y" << std::endl;
	line("x ^ y", str(Vector3f::xAxis() * Vector3f::yAxis()));
	line("y ^ z", str(Vector3f::yAxis() * Vector3f::zAxis()));
	line("z ^ x", str(Vector3f::zAxis() * Vector3f::xAxis()));

	std::cout << std::endl << "  Linear interpolation from a to b (Tools::interpolate):" << std::endl;
	for (float t = 0; t <= 1.001f; t += 0.25f)
		line("  t = " + num(t), str(Tools::interpolate(a, b, t)));
}

static void demoHomogeneous()
{
	title("2. Points and vectors in homogeneous coordinates: Vector4f");

	Vector4f p(1, 2, 3, 1);
	Vector4f q(4, 6, 3, 1);
	line("point p (w = 1)", str(p) + "  isPoint: " + yes(p.isPoint()));
	line("point q (w = 1)", str(q) + "  isPoint: " + yes(q.isPoint()));
	Vector4f pq(p, q);
	line("vector pq = q - p (w = 0)", str(pq) + "  isVector: " + yes(pq.isVector()));
	line("|pq|", num(pq.length()));
	line("p + pq lands on q", str(p + pq));

	Vector4f h(2, 4, 6, 2);
	line("point h with w = 2", str(h));
	line("h.get3DPoint() = (x/w, y/w, z/w)", str(h.get3DPoint().value()));
	std::optional<Vector3f> none = pq.get3DPoint();
	line("pq.get3DPoint() on a vector", none ? str(*none) : std::string("empty (w = 0: point at infinity)"));
}

static void demoMatrices()
{
	title("3. Matrices: Matrix3f");

	const float values[3][3] = { { 2, 0, 1 }, { 1, 3, 2 }, { 1, 1, 2 } };
	Matrix3f m(values);
	print("M", m);
	std::cout << std::endl;
	print("transpose(M)", m.transpose());
	std::cout << std::endl;
	line("det(M)", num(m.determinant()));
	line("trace(M)", num(m.trace()));
	line("row 1", str(m.getRow(1)));
	line("column 2", str(m.getColumn(2)));
	std::cout << std::endl;

	Matrix3f inv = m.inverse();
	print("inverse(M)", inv);
	std::cout << std::endl;
	print("M * inverse(M)", m * inv);
	line("is identity", yes((m * inv).isIdentity()));

	std::cout << std::endl << "  Solving the system M.x = b with x = inverse(M).b:" << std::endl;
	Vector3f b(5, 13, 9);
	Vector3f x = inv * b;
	line("b", str(b));
	line("x", str(x));
	line("check M.x", str(m * x));
}

static void demoTransforms()
{
	title("4. Transformations: Matrix4f on points and vectors");

	Vector4f point(1, 0, 0, 1);
	Vector4f vector(1, 0, 0, 0);
	Matrix4f t = translation(Vector3f(10, 0, 0));
	Matrix4f r = rotationZ(radians(90));
	Matrix4f s = scaling(2);

	print("T (translation x+10)", t);
	std::cout << std::endl;
	print("R (rotation 90 around z)", r);
	std::cout << std::endl;

	line("point P", str(point));
	line("vector V", str(vector));
	line("T * P (point is moved)", str(t * point));
	line("T * V (vector is not)", str(t * vector));
	line("R * P", str(r * point));
	line("S * P (scale x2)", str(s * point));

	std::cout << std::endl << "  Matrix products are not commutative: the order matters" << std::endl;
	line("(T * R) * P: rotate, then move", str((t * r) * point));
	line("(R * T) * P: move, then rotate", str((r * t) * point));

	Matrix4f m = t * r * s;
	line("M = T * R * S, M * P", str(m * point));
	line("inverse(M) * (M * P) is P again", str(m.inverse() * (m * point)));
}

static void demoQuaternions()
{
	title("5. Rotations with quaternions: Quaternionf");

	Quaternionf qz(Vector3f::zAxis(), radians(90));
	Quaternionf qx(Vector3f::xAxis(), radians(90));
	line("qz = 90 around z", str(qz));
	line("qx = 90 around x", str(qx));
	line("|qz|", num(qz.length()));
	line("qz * conjugate(qz)", str(qz * qz.conjugate()) + "  (identity)");

	Vector3f v(1, 0, 0);
	line("v", str(v));
	line("qz rotates v", str(qz.toMatrix3() * v));

	Quaternionf both = qx * qz;
	Vector3f axis;
	float angle = both.toAxisAngle(axis);
	line("qx * qz (qz first, then qx)", str(both));
	line("  as axis", str(axis));
	line("  and angle (degrees)", num(degrees(angle)));
	line("  rotates v", str(both.toMatrix3() * v));

	std::cout << std::endl << "  A rotation matrix converts back to the same quaternion:" << std::endl;
	line("Quaternionf(qz.toMatrix4())", str(Quaternionf(qz.toMatrix4())));

	std::cout << std::endl << "  Smooth rotation from identity to 120 around z (slerp):" << std::endl;
	Quaternionf start;
	Quaternionf end(Vector3f::zAxis(), radians(120));
	for (int i = 0; i <= 4; i++)
	{
		float t = i / 4.0f;
		Quaternionf qt = Quaternionf::slerp(start, end, t);
		Vector3f a;
		float deg = degrees(qt.toAxisAngle(a));
		line("  t = " + num(t) + "  angle " + num(deg), "v -> " + str(qt.toMatrix3() * v));
	}
}

static void demo2D()
{
	title("6. 2D: Vector2f and Matrix2f");

	float c = std::cos(radians(45));
	float s = std::sin(radians(45));
	const float values[2][2] = { { c, -s }, { s, c } };
	Matrix2f rotation(values);
	print("R (rotation 45)", rotation);
	line("det(R) (a rotation keeps areas)", num(rotation.determinant()));
	line("inverse(R) == transpose(R)", yes(rotation.inverse() == rotation.transpose()));

	std::cout << std::endl << "  Corners of a unit square, rotated by 45 degrees:" << std::endl;
	std::vector<Vector2f> square = { Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) };
	for (const Vector2f& corner : square)
		line("  " + str(corner), "-> " + str(rotation * corner));
}

static void demoGeometry()
{
	title("7. Geometry helpers: GeometryTools");

	std::vector<Vector4f> cube;
	for (int i = 0; i < 8; i++)
		cube.push_back(Vector4f(1.0f + 2 * (i & 1), 1.0f + 2 * ((i >> 1) & 1), 1.0f + 2 * ((i >> 2) & 1), 1));
	std::cout << "  The 8 corners of a cube of side 2 starting at (1, 1, 1):" << std::endl;
	for (const Vector4f& corner : cube)
		std::cout << "    " << str(corner) << std::endl;
	line("center of the cube", str(GeometryTools::center(cube).value()));
	std::optional<Vector4f> empty = GeometryTools::center(std::vector<Vector4f>());
	line("center of no point", empty ? str(*empty) : std::string("empty"));
}

static void demoErrors()
{
	title("8. Errors are reported with exceptions (all derive from Vector3DException)");

	const float singularValues[3][3] = { { 1, 2, 3 }, { 2, 4, 6 }, { 0, 1, 1 } };
	Matrix3f singular(singularValues);
	print("S (row 2 = 2 x row 1)", singular);
	line("det(S)", num(singular.determinant()));
	try
	{
		singular.inverse();
	}
	catch (const NotInvertibleMatrixException& e)
	{
		line("inverse(S)", std::string("NotInvertibleMatrixException: ") + e.what());
	}

	try
	{
		Vector3f(1, 2, 3).get(3);
	}
	catch (const IndexOutOfBoundException& e)
	{
		line("Vector3f.get(3)", std::string("IndexOutOfBoundException: ") + e.what());
	}

	try
	{
		Matrix3f m;
		m.setArray({ { 1, 2 }, { 3, 4 } });
	}
	catch (const Vector3DException& e)
	{
		line("Matrix3f.setArray(2x2 array)", std::string("caught as Vector3DException: ") + e.what());
	}
}

int main()
{
	std::cout << "VectorMatrixLib: a tour of the API (EPSILON = " << EPSILON << ")" << std::endl;

	demoVectors();
	demoHomogeneous();
	demoMatrices();
	demoTransforms();
	demoQuaternions();
	demo2D();
	demoGeometry();
	demoErrors();

	std::cout << std::endl;
	return 0;
}
