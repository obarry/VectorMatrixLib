//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//
// Runs all the registered tests, suite by suite.
// Run them with: ctest --test-dir build --output-on-failure
// An optional argument runs only the suites whose name contains it, e.g. vectormatrix_tests Matrix
//

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include "TestFramework.h"

int main(int argc, char* argv[])
{
	using namespace testframework;

	std::string filter = argc > 1 ? argv[1] : "";

	// Group by suite, keeping each suite's tests in registration order
	std::map<std::string, std::vector<TestCase>> suites;
	for (const TestCase& test : registry())
		if (std::string(test.suite).find(filter) != std::string::npos)
			suites[test.suite].push_back(test);

	int nbTests = 0;
	int nbFailedTests = 0;
	for (const auto& suite : suites)
	{
		int suiteFailed = 0;
		for (const TestCase& test : suite.second)
		{
			int before = failures();
			try
			{
				test.function();
			}
			catch (const std::exception& e)
			{
				std::cerr << "    unexpected exception: " << e.what() << std::endl;
				failures()++;
			}
			if (failures() != before)
			{
				std::cerr << "  FAILED " << test.suite << "." << test.name << std::endl;
				suiteFailed++;
			}
		}
		nbTests += static_cast<int>(suite.second.size());
		nbFailedTests += suiteFailed;
		std::cout << (suiteFailed == 0 ? "[  OK  ] " : "[FAILED] ") << suite.first
				  << " (" << suite.second.size() << " tests" << (suiteFailed ? ", " + std::to_string(suiteFailed) + " failed" : "") << ")" << std::endl;
	}

	std::cout << std::endl;
	if (nbFailedTests == 0)
	{
		std::cout << "All " << nbTests << " tests passed" << std::endl;
		return 0;
	}
	std::cout << nbFailedTests << " of " << nbTests << " tests failed (" << failures() << " failed checks)" << std::endl;
	return 1;
}
