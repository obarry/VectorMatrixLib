//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Port of Aventura TestGeometryTools.java

#include <optional>
#include <vector>
#include "TestFramework.h"
#include "GeometryTools.h"
#include "Vector4f.h"

using namespace vectormatrix;

TEST(GeometryTools, center_monoDimensional_normalCase)
{
	std::vector<Vector4f> points = {
		Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
		Vector4f(2.0f, 0.0f, 0.0f, 1.0f),
		Vector4f(0.0f, 2.0f, 0.0f, 1.0f),
		Vector4f(0.0f, 0.0f, 2.0f, 1.0f)
	};
	std::optional<Vector4f> center = GeometryTools::center(points);
	CHECK(center.has_value());
	if (!center) return;
	CHECK_NEAR_TOL(center->getX(), 0.5f, 0.00001f);
	CHECK_NEAR_TOL(center->getY(), 0.5f, 0.00001f);
	CHECK_NEAR_TOL(center->getZ(), 0.5f, 0.00001f);
	CHECK_NEAR_TOL(center->getW(), 1.0f, 0.00001f); // center of points must remain a Point (w=1)
}

TEST(GeometryTools, center_monoDimensional_singlePoint)
{
	std::vector<Vector4f> points = { Vector4f(3.0f, 4.0f, 5.0f, 1.0f) };
	std::optional<Vector4f> center = GeometryTools::center(points);
	CHECK(center.has_value());
	if (!center) return;
	CHECK_NEAR_TOL(center->getX(), 3.0f, 0.00001f);
	CHECK_NEAR_TOL(center->getY(), 4.0f, 0.00001f);
	CHECK_NEAR_TOL(center->getZ(), 5.0f, 0.00001f);
}

TEST(GeometryTools, center_monoDimensional_emptyArray_returnsNull)
{
	std::optional<Vector4f> center = GeometryTools::center(std::vector<Vector4f>());
	CHECK(!center.has_value());
}

// Not ported: testCenter_monoDimensional_null_returnsNull (no null std::vector in C++)

TEST(GeometryTools, center_biDimensional_normalCase)
{
	std::vector<std::vector<Vector4f>> points = {
		{ Vector4f(0.0f, 0.0f, 0.0f, 1.0f), Vector4f(4.0f, 0.0f, 0.0f, 1.0f) },
		{ Vector4f(0.0f, 4.0f, 0.0f, 1.0f), Vector4f(0.0f, 0.0f, 4.0f, 1.0f) }
	};
	std::optional<Vector4f> center = GeometryTools::center(points);
	CHECK(center.has_value());
	if (!center) return;
	CHECK_NEAR_TOL(center->getX(), 1.0f, 0.00001f);
	CHECK_NEAR_TOL(center->getY(), 1.0f, 0.00001f);
	CHECK_NEAR_TOL(center->getZ(), 1.0f, 0.00001f);
}

TEST(GeometryTools, center_biDimensional_emptyOuterArray_returnsNull)
{
	std::optional<Vector4f> center = GeometryTools::center(std::vector<std::vector<Vector4f>>());
	CHECK(!center.has_value());
}

TEST(GeometryTools, center_biDimensional_emptyInnerArray_returnsNull)
{
	std::vector<std::vector<Vector4f>> points = { std::vector<Vector4f>() };
	std::optional<Vector4f> center = GeometryTools::center(points);
	CHECK(!center.has_value());
}

// Not ported: testCenter_biDimensional_null_returnsNull (no null std::vector in C++)
