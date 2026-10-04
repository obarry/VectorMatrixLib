//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef GEOMETRYTOOLS_H
#define GEOMETRYTOOLS_H

#include <optional>
#include <vector>
#include "Vector4f.h"

namespace vectormatrix
{
	// Geometry helpers (same as Aventura GeometryTools)
	class GeometryTools
	{
	public:
		// Geometrical center of the points (average of x, y, z, with w = 1),
		// or nothing if there is no point (Java returns null)
		static std::optional<Vector4f> center(const std::vector<Vector4f>& points);
		// Same for a grid of points (rows may have different lengths)
		static std::optional<Vector4f> center(const std::vector<std::vector<Vector4f>>& points);
	};
}

#endif // GEOMETRYTOOLS_H
