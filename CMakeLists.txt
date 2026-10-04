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
	VectorMatrixLib/Quaternion.cpp
)
target_include_directories(vectormatrix PUBLIC VectorMatrixLib)

if(MSVC)
	target_compile_options(vectormatrix PRIVATE /W4)
else()
	target_compile_options(vectormatrix PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Demo program (same as the Visual Studio project)
add_executable(vectormatrix_demo VectorMatrixLib/TestMatrix.cpp)
target_link_libraries(vectormatrix_demo PRIVATE vectormatrix)

# Unit tests
enable_testing()
add_executable(vectormatrix_tests tests/TestVectorMatrix.cpp)
target_link_libraries(vectormatrix_tests PRIVATE vectormatrix)
add_test(NAME vectormatrix_tests COMMAND vectormatrix_tests)
