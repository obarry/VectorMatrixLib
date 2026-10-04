//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include "GeometryTools.h"

namespace vectormatrix
{
	std::optional<Vector4f> GeometryTools::center(const std::vector<Vector4f>& points)
	{
		if (points.empty()) return std::nullopt;

		float x = 0, y = 0, z = 0;
		for (const Vector4f& p : points)
		{
			x += p.getX();
			y += p.getY();
			z += p.getZ();
		}
		float n = static_cast<float>(points.size());
		return Vector4f(x / n, y / n, z / n, 1);
	}

	std::optional<Vector4f> GeometryTools::center(const std::vector<std::vector<Vector4f>>& points)
	{
		float x = 0, y = 0, z = 0;
		size_t count = 0;
		for (const std::vector<Vector4f>& row : points)
		{
			for (const Vector4f& p : row)
			{
				x += p.getX();
				y += p.getY();
				z += p.getZ();
			}
			count += row.size();
		}
		if (count == 0) return std::nullopt;

		float n = static_cast<float>(count);
		return Vector4f(x / n, y / n, z / n, 1);
	}
}
