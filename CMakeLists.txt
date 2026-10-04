cmake_minimum_required(VERSION 3.14)
project(VectorMatrixLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vectormatrix
	VectorMatrixLib/Vector2f.cpp
	VectorMatrixLib/Vector3f.cpp
	VectorMatrixLib/Vector4f.cpp
	VectorMatrixLib/Matrix2f.cpp
	VectorMatrixLib/Matrix3f.cpp
	VectorMatrixLib/Matrix4f.cpp
	VectorMatrixLib/Quaternionf.cpp
	VectorMatrixLib/GeometryTools.cpp
)
target_include_directories(vectormatrix PUBLIC VectorMatrixLib)

if(MSVC)
	target_compile_options(vectormatrix PRIVATE /W4)
else()
	target_compile_options(vectormatrix PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Console tour of the API (same program as the Visual Studio project)
add_executable(vectormatrix_demo VectorMatrixLib/VectorMatrixDemo.cpp)
target_link_libraries(vectormatrix_demo PRIVATE vectormatrix)

# Unit tests
enable_testing()
add_executable(vectormatrix_tests
	tests/TestMain.cpp
	tests/TestVectorMatrix.cpp
	tests/TestVector2f.cpp
	tests/TestVector3f.cpp
	tests/TestVector4f.cpp
	tests/TestMatrix2f.cpp
	tests/TestMatrix3f.cpp
	tests/TestMatrix4f.cpp
	tests/TestQuaternionf.cpp
	tests/TestGaussJordanSolver.cpp
	tests/TestVector3fMatrix3f.cpp
	tests/TestTools.cpp
	tests/TestGeometryTools.cpp
)
target_include_directories(vectormatrix_tests PRIVATE tests)
target_link_libraries(vectormatrix_tests PRIVATE vectormatrix)
add_test(NAME vectormatrix_tests COMMAND vectormatrix_tests)
