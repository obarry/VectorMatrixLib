//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestTools.java

#include "TestFramework.h"
#include "Tools.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

using namespace vectormatrix;

TEST(Tools, interpolate_vector4_endpoints)
{
	Vector4f a(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4f b(10.0f, 20.0f, 30.0f, 1.0f);

	Vector4f atStart = Tools::interpolate(a, b, 0.0f);
	CHECK(atStart == a);

	Vector4f atEnd = Tools::interpolate(a, b, 1.0f);
	CHECK(atEnd == b);
}

TEST(Tools, interpolate_vector4_midpoint)
{
	Vector4f a(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4f b(10.0f, 20.0f, 30.0f, 1.0f);

	Vector4f mid = Tools::interpolate(a, b, 0.5f);
	CHECK_NEAR_TOL(mid.getX(), 5.0f, 0.00001f);
	CHECK_NEAR_TOL(mid.getY(), 10.0f, 0.00001f);
	CHECK_NEAR_TOL(mid.getZ(), 15.0f, 0.00001f);
}

TEST(Tools, interpolate_vector4_extrapolation)
{
	Vector4f a(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4f b(10.0f, 0.0f, 0.0f, 1.0f);

	Vector4f beyondB = Tools::interpolate(a, b, 2.0f);
	CHECK_NEAR_TOL(beyondB.getX(), 20.0f, 0.00001f); // beyond B, on the (AB) line

	Vector4f beforeA = Tools::interpolate(a, b, -1.0f);
	CHECK_NEAR_TOL(beforeA.getX(), -10.0f, 0.00001f); // beyond A, on the (AB) line
}

TEST(Tools, interpolate_vector3_endpointsAndMidpoint)
{
	Vector3f a(0.0f, 0.0f, 0.0f);
	Vector3f b(4.0f, 8.0f, 12.0f);

	CHECK(Tools::interpolate(a, b, 0.0f) == a);
	CHECK(Tools::interpolate(a, b, 1.0f) == b);

	Vector3f mid = Tools::interpolate(a, b, 0.5f);
	CHECK_NEAR_TOL(mid.getX(), 2.0f, 0.00001f);
	CHECK_NEAR_TOL(mid.getY(), 4.0f, 0.00001f);
	CHECK_NEAR_TOL(mid.getZ(), 6.0f, 0.00001f);
}

TEST(Tools, interpolate_vector2_endpointsAndMidpoint)
{
	// Java passes t as a double here; the C++ Vector2f overload takes a float
	Vector2f a(0.0f, 0.0f);
	Vector2f b(6.0f, 10.0f);

	CHECK(Tools::interpolate(a, b, 0.0f) == a);
	CHECK(Tools::interpolate(a, b, 1.0f) == b);

	Vector2f mid = Tools::interpolate(a, b, 0.5f);
	CHECK_NEAR_TOL(mid.getX(), 3.0f, 0.00001f);
	CHECK_NEAR_TOL(mid.getY(), 5.0f, 0.00001f);
}

TEST(Tools, interpolate_scalar_double)
{
	CHECK_NEAR_TOL(Tools::interpolate(0.0, 10.0, 0.0), 0.0, 0.00001);
	CHECK_NEAR_TOL(Tools::interpolate(0.0, 10.0, 1.0), 10.0, 0.00001);
	CHECK_NEAR_TOL(Tools::interpolate(0.0, 10.0, 0.5), 5.0, 0.00001);
	CHECK_NEAR_TOL(Tools::interpolate(0.0, 10.0, 2.0), 20.0, 0.00001); // extrapolation beyond b
}

TEST(Tools, interpolate_scalar_float)
{
	CHECK_NEAR_TOL(Tools::interpolate(0.0f, 10.0f, 0.0f), 0.0f, 0.00001f);
	CHECK_NEAR_TOL(Tools::interpolate(0.0f, 10.0f, 1.0f), 10.0f, 0.00001f);
	CHECK_NEAR_TOL(Tools::interpolate(0.0f, 10.0f, 0.5f), 5.0f, 0.00001f);
	CHECK_NEAR_TOL(Tools::interpolate(0.0f, 10.0f, -1.0f), -10.0f, 0.00001f); // extrapolation before a
}
