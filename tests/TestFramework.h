//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Minimal unit test framework, without any third-party dependency.
//
//   TEST(Vector3f, length) { CHECK_NEAR(Vector3f(3, 4, 0).length(), 5.0f); }
//
// Each TEST registers itself; TestMain.cpp runs them all, suite by suite.
//

#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "MathTools.h"

namespace testframework
{
	struct TestCase
	{
		const char* suite;
		const char* name;
		void (*function)();
	};

	inline std::vector<TestCase>& registry()
	{
		static std::vector<TestCase> tests;
		return tests;
	}

	// Number of failed checks since the start of the run
	inline int& failures()
	{
		static int count = 0;
		return count;
	}

	struct Registrar
	{
		Registrar(const char* suite, const char* name, void (*function)())
		{
			registry().push_back({ suite, name, function });
		}
	};

	inline bool check(bool condition, const char* expression, const char* file, int line)
	{
		if (!condition)
		{
			std::cerr << "    " << file << ":" << line << ": FAILED: " << expression << std::endl;
			failures()++;
		}
		return condition;
	}

	template <typename A, typename B>
	void checkEqual(const A& actual, const B& expected, const char* expression, const char* file, int line)
	{
		if (!check(actual == expected, expression, file, line))
			std::cerr << "      actual:   " << actual << std::endl
					  << "      expected: " << expected << std::endl;
	}

	inline void checkNear(double actual, double expected, double tolerance, const char* expression, const char* file, int line)
	{
		if (!check(std::fabs(actual - expected) <= tolerance, expression, file, line))
			std::cerr << "      actual: " << actual << ", expected: " << expected << " (tolerance " << tolerance << ")" << std::endl;
	}
}

#define TEST(suite, name) \
	static void suite##_##name(); \
	static const testframework::Registrar suite##_##name##_registrar(#suite, #name, &suite##_##name); \
	static void suite##_##name()

// expr must be true
#define CHECK(expr) testframework::check((expr), #expr, __FILE__, __LINE__)
// actual == expected (vectors, matrices and quaternions compare within EPSILON), both printed on failure
#define CHECK_EQUAL(actual, expected) testframework::checkEqual((actual), (expected), #actual " == " #expected, __FILE__, __LINE__)
// |actual - expected| <= EPSILON (same tolerance as MathTools::equals)
#define CHECK_NEAR(actual, expected) testframework::checkNear((actual), (expected), vectormatrix::EPSILON, #actual " ~= " #expected, __FILE__, __LINE__)
// |actual - expected| <= tolerance (same as JUnit assertEquals(expected, actual, delta))
#define CHECK_NEAR_TOL(actual, expected, tolerance) testframework::checkNear((actual), (expected), (tolerance), #actual " ~= " #expected, __FILE__, __LINE__)
// expr must throw Exception (or a subclass)
#define CHECK_THROWS(expr, Exception) \
	do { bool thrown_ = false; try { (void)(expr); } catch (const Exception&) { thrown_ = true; } \
		testframework::check(thrown_, #expr " throws " #Exception, __FILE__, __LINE__); } while (0)
// expr must not throw anything
#define CHECK_NO_THROW(expr) \
	do { bool thrown_ = false; try { (void)(expr); } catch (...) { thrown_ = true; } \
		testframework::check(!thrown_, #expr " does not throw", __FILE__, __LINE__); } while (0)

#endif // TESTFRAMEWORK_H
