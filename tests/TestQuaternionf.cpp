//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestQuaternion.java
//

#include <cmath>
#include "TestFramework.h"
#include "Vector3f.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Quaternionf.h"
#include "Exceptions.h"

using namespace vectormatrix;

static const float DELTA = 0.0001f;
static const float PI_F = static_cast<float>(3.14159265358979323846);

// Replacement for Aventura Rotation(a, v) (class absent from the C++ lib): same formula as
// Rotation.initRotation(a, v), applied on an identity Matrix4f
static Matrix4f rotationMatrix(float a, const Vector3f& v)
{
	Vector3f v1(v);
	v1.normalize();
	float x = v1.getX();
	float y = v1.getY();
	float z = v1.getZ();
	float c = std::cos(a);
	float s = std::sin(a);

	Matrix4f r = Matrix4f::identity();
	// First row
	r.set(0, 0, x * x + (1 - x * x) * c);
	r.set(0, 1, x * y * (1 - c) - z * s);
	r.set(0, 2, x * z * (1 - c) + y * s);
	// Second row
	r.set(1, 0, x * y * (1 - c) + z * s);
	r.set(1, 1, y * y + (1 - y * y) * c);
	r.set(1, 2, y * z * (1 - c) - x * s);
	// Third row
	r.set(2, 0, x * z * (1 - c) - y * s);
	r.set(2, 1, y * z * (1 - c) + x * s);
	r.set(2, 2, z * z + (1 - z * z) * c);
	return r;
}

TEST(Quaternionf, identity)
{
	Quaternionf q;
	CHECK_NEAR_TOL(q.getX(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(q.getY(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(q.getZ(), 0.0f, 0.0f);
	CHECK_NEAR_TOL(q.getW(), 1.0f, 0.0f);
}

TEST(Quaternionf, identity_toMatrix4IsIdentity)
{
	Quaternionf q;
	CHECK(q.toMatrix4().isIdentity());
}

TEST(Quaternionf, constructor_fourArgs)
{
	Quaternionf q(1.0f, 2.0f, 3.0f, 4.0f);
	CHECK_NEAR_TOL(q.getX(), 1.0f, 0.0f);
	CHECK_NEAR_TOL(q.getY(), 2.0f, 0.0f);
	CHECK_NEAR_TOL(q.getZ(), 3.0f, 0.0f);
	CHECK_NEAR_TOL(q.getW(), 4.0f, 0.0f);
}

TEST(Quaternionf, copyConstructor)
{
	Quaternionf q1(1.0f, 2.0f, 3.0f, 4.0f);
	Quaternionf q2(q1);
	CHECK(q1 == q2);
	// Verify it's a real copy
	q2.setX(99.0f);
	CHECK_NEAR_TOL(q1.getX(), 1.0f, 0.0f);
}

TEST(Quaternionf, getSet_byIndex)
{
	Quaternionf q;
	q.set(0, 10.0f);
	q.set(1, 20.0f);
	q.set(2, 30.0f);
	q.set(3, 40.0f);
	CHECK_NEAR_TOL(q.get(0), 10.0f, 0.0f);
	CHECK_NEAR_TOL(q.get(1), 20.0f, 0.0f);
	CHECK_NEAR_TOL(q.get(2), 30.0f, 0.0f);
	CHECK_NEAR_TOL(q.get(3), 40.0f, 0.0f);
	CHECK_NEAR_TOL(q.get(0), q.getX(), 0.0f);
	CHECK_NEAR_TOL(q.get(3), q.getW(), 0.0f);
}

TEST(Quaternionf, get_invalidIndex_throws)
{
	CHECK_THROWS(Quaternionf().get(4), IndexOutOfBoundException);
}

TEST(Quaternionf, set_invalidIndex_throws)
{
	Quaternionf q;
	CHECK_THROWS(q.set(4, 1.0f), IndexOutOfBoundException);
}

TEST(Quaternionf, length_ofIdentityIsOne)
{
	CHECK_NEAR_TOL(Quaternionf().length(), 1.0f, DELTA);
}

TEST(Quaternionf, lengthSquared_matchesLengthSquared)
{
	Quaternionf q(1.0f, 2.0f, 2.0f, 4.0f); // length = sqrt(1+4+4+16) = 5
	CHECK_NEAR_TOL(q.lengthSquared(), 25.0f, DELTA);
	CHECK_NEAR_TOL(q.length(), 5.0f, DELTA);
}

TEST(Quaternionf, normalize)
{
	Quaternionf q(0.0f, 0.0f, 0.0f, 5.0f);
	q.normalize();
	CHECK_NEAR_TOL(q.length(), 1.0f, DELTA);
	CHECK_NEAR_TOL(q.getW(), 1.0f, DELTA);
}

TEST(Quaternionf, conjugate)
{
	Quaternionf q(1.0f, 2.0f, 3.0f, 4.0f);
	Quaternionf c = q.conjugate();
	CHECK_NEAR_TOL(c.getX(), -1.0f, 0.0f);
	CHECK_NEAR_TOL(c.getY(), -2.0f, 0.0f);
	CHECK_NEAR_TOL(c.getZ(), -3.0f, 0.0f);
	CHECK_NEAR_TOL(c.getW(), 4.0f, 0.0f);
	// Original must not be modified
	CHECK_NEAR_TOL(q.getX(), 1.0f, 0.0f);
}

TEST(Quaternionf, inverse_ofUnitQuaternionEqualsConjugate)
{
	Quaternionf q(Vector3f::xAxis(), PI_F / 3);
	Quaternionf inv = q.inverse();
	Quaternionf conj = q.conjugate();
	CHECK(inv == conj);
}

TEST(Quaternionf, inverse_timesOriginalIsIdentity)
{
	Quaternionf q(Vector3f::yAxis(), PI_F / 5);
	Quaternionf result = q * q.inverse();
	CHECK(result == Quaternionf());
}

TEST(Quaternionf, times_withIdentityIsUnchanged)
{
	Quaternionf q(Vector3f::zAxis(), PI_F / 4);
	Quaternionf result = q * Quaternionf();
	CHECK(result == q);
}

TEST(Quaternionf, timesEquals_matchesTimes)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	Quaternionf q2(Vector3f::yAxis(), PI_F / 7);
	Quaternionf expected = q1 * q2;
	q1 *= q2;
	CHECK(expected == q1);
}

TEST(Quaternionf, dot_ofIdenticalUnitQuaternionIsOne)
{
	Quaternionf q(Vector3f::xAxis(), PI_F / 3);
	CHECK_NEAR_TOL(q.dot(q), 1.0f, DELTA);
}

TEST(Quaternionf, axisAngleConstructor_matchesRotationClass)
{
	float angle = PI_F / 3;
	Quaternionf q(Vector3f::xAxis(), angle);
	Matrix4f r = rotationMatrix(angle, Vector3f::xAxis());
	CHECK(q.toMatrix4() == r);
}

TEST(Quaternionf, axisAngleConstructor_matchesRotationClass_yAxis)
{
	float angle = PI_F / 4;
	Quaternionf q(Vector3f::yAxis(), angle);
	Matrix4f r = rotationMatrix(angle, Vector3f::yAxis());
	CHECK(q.toMatrix4() == r);
}

TEST(Quaternionf, axisAngleConstructor_matchesRotationClass_zAxis)
{
	float angle = PI_F / 5;
	Quaternionf q(Vector3f::zAxis(), angle);
	Matrix4f r = rotationMatrix(angle, Vector3f::zAxis());
	CHECK(q.toMatrix4() == r);
}

TEST(Quaternionf, toMatrix3_matchesToMatrix4UpperLeft)
{
	Quaternionf q(Vector3f::xAxis(), PI_F / 3);
	Matrix3f m3 = q.toMatrix3();
	Matrix4f m4 = q.toMatrix4();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			CHECK_NEAR_TOL(m3.get(i, j), m4.get(i, j), DELTA);
}

TEST(Quaternionf, matrix3Constructor_roundTrip)
{
	Quaternionf original(Vector3f::xAxis(), PI_F / 3);
	Matrix3f m = original.toMatrix3();
	Quaternionf rebuilt(m);
	// May differ by an overall sign (q and -q represent the same rotation matrix): compare the matrices
	CHECK(original.toMatrix3() == rebuilt.toMatrix3());
}

TEST(Quaternionf, matrix4Constructor_roundTrip)
{
	Quaternionf original(Vector3f::yAxis(), PI_F / 4);
	Matrix4f m = original.toMatrix4();
	Quaternionf rebuilt(m);
	CHECK(original.toMatrix4() == rebuilt.toMatrix4());
}

TEST(Quaternionf, matrix3Constructor_matchesMatrix4Constructor)
{
	float angle = PI_F / 3;
	Matrix4f r = rotationMatrix(angle, Vector3f::zAxis());

	float upperLeft3x3[3][3];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			upperLeft3x3[i][j] = r.get(i, j);
	Matrix3f m3(upperLeft3x3);

	Quaternionf fromMatrix3(m3);
	Quaternionf fromMatrix4(r);

	// May differ by an overall sign (q and -q represent the same rotation): compare the matrices
	CHECK(fromMatrix3.toMatrix4() == fromMatrix4.toMatrix4());
}

TEST(Quaternionf, toAxisAngle_roundTrip)
{
	Vector3f originalAxis = Vector3f::xAxis();
	float originalAngle = PI_F / 3;
	Quaternionf q(originalAxis, originalAngle);

	Vector3f recoveredAxis;
	float recoveredAngle = q.toAxisAngle(recoveredAxis);

	CHECK_NEAR_TOL(recoveredAngle, originalAngle, DELTA);
	CHECK(originalAxis == recoveredAxis);
}

TEST(Quaternionf, toAxisAngle_identityHasZeroAngle)
{
	Quaternionf q;
	Vector3f axis;
	float angle = q.toAxisAngle(axis);
	CHECK_NEAR_TOL(angle, 0.0f, DELTA);
}

TEST(Quaternionf, slerp_atZeroReturnsStart)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	Quaternionf q2(Vector3f::xAxis(), PI_F / 2);
	Quaternionf result = Quaternionf::slerp(q1, q2, 0.0f);
	CHECK(q1 == result);
}

TEST(Quaternionf, slerp_atOneReturnsEnd)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	Quaternionf q2(Vector3f::xAxis(), PI_F / 2);
	Quaternionf result = Quaternionf::slerp(q1, q2, 1.0f);
	CHECK(q2 == result);
}

TEST(Quaternionf, slerp_atHalfway_sameAxis_isAverageAngle)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	Quaternionf q2(Vector3f::xAxis(), PI_F / 2);
	Quaternionf expected(Vector3f::xAxis(), (PI_F / 6 + PI_F / 2) / 2);
	Quaternionf result = Quaternionf::slerp(q1, q2, 0.5f);
	CHECK(expected == result);
}

TEST(Quaternionf, slerp_resultIsUnitLength)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	Quaternionf q2(Vector3f::yAxis(), PI_F / 2);
	Quaternionf result = Quaternionf::slerp(q1, q2, 0.37f);
	CHECK_NEAR_TOL(result.length(), 1.0f, DELTA);
}

TEST(Quaternionf, slerp_takesShorterPath)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	// -q1 represents the exact same rotation as q1, but dot(q1, -q1) = -1: slerp must still
	// produce a valid, unit-length interpolation rather than blowing up or taking the long way
	Quaternionf negQ1(-q1.getX(), -q1.getY(), -q1.getZ(), -q1.getW());
	Quaternionf q2(Vector3f::xAxis(), PI_F / 2);
	Quaternionf result = Quaternionf::slerp(negQ1, q2, 0.5f);
	CHECK_NEAR_TOL(result.length(), 1.0f, DELTA);
	// The rotation it represents should still land at the same matrix as slerping q1->q2 directly
	Quaternionf directResult = Quaternionf::slerp(q1, q2, 0.5f);
	CHECK(directResult.toMatrix4() == result.toMatrix4());
}

TEST(Quaternionf, slerp_nearIdenticalQuaternions_fallsBackToLerp)
{
	Quaternionf q1(Vector3f::xAxis(), PI_F / 6);
	Quaternionf q2(Vector3f::xAxis(), PI_F / 6 + 0.00001f);
	Quaternionf result = Quaternionf::slerp(q1, q2, 0.5f);
	CHECK(!std::isnan(result.getX()));
	CHECK(!std::isnan(result.getW()));
	CHECK_NEAR_TOL(result.length(), 1.0f, DELTA);
}

TEST(Quaternionf, equals_negativeCase)
{
	Quaternionf q1(1.0f, 2.0f, 3.0f, 4.0f);
	Quaternionf q2(9.0f, 9.0f, 9.0f, 9.0f);
	CHECK(!(q1 == q2));
}

// Not ported: testEquals_object_negativeCase_null (Java-only equals(Object) with null / other type)

// Not ported: testHashCode_consistentWithEquals (Java-only hashCode)

// Rotation(Quaternion) is Rotation(q.toMatrix4()) in Aventura: compare toMatrix4() with Rotation(angle, axis)
TEST(Quaternionf, rotationConstructor_fromQuaternion)
{
	float angle = PI_F / 4;
	Quaternionf q(Vector3f::yAxis(), angle);
	Matrix4f fromQuaternion = q.toMatrix4();
	Matrix4f fromAngleAxis = rotationMatrix(angle, Vector3f::yAxis());
	CHECK(fromQuaternion == fromAngleAxis);
}
