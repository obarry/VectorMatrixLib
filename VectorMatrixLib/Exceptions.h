//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace vectormatrix
{
	// Base class of all the exceptions of the library (same hierarchy as Aventura)
	class Vector3DException : public std::runtime_error
	{
	public:
		explicit Vector3DException(const std::string& message) : std::runtime_error(message) {}
	};

	// An index of a vector or matrix element is out of bound
	class IndexOutOfBoundException : public Vector3DException
	{
	public:
		explicit IndexOutOfBoundException(const std::string& message) : Vector3DException(message) {}
	};

	// An array used to set a vector has a wrong size
	class VectorArrayWrongSizeException : public Vector3DException
	{
	public:
		explicit VectorArrayWrongSizeException(const std::string& message) : Vector3DException(message) {}
	};

	// An array used to set a matrix has a wrong size
	class MatrixArrayWrongSizeException : public Vector3DException
	{
	public:
		explicit MatrixArrayWrongSizeException(const std::string& message) : Vector3DException(message) {}
	};

	// A matrix is singular and cannot be inverted
	class NotInvertibleMatrixException : public Vector3DException
	{
	public:
		explicit NotInvertibleMatrixException(const std::string& message = "Matrix is not invertible") : Vector3DException(message) {}
	};
}

#endif // EXCEPTIONS_H
