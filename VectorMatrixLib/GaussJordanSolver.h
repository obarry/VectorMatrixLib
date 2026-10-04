//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef GAUSSJORDANSOLVER_H
#define GAUSSJORDANSOLVER_H

#include <cmath>
#include "Exceptions.h"

namespace vectormatrix
{
	// Matrix inversion by Gauss-Jordan elimination with partial pivoting,
	// shared by Matrix3f and Matrix4f (same algorithm as Aventura GaussJordanSolver)
	class GaussJordanSolver
	{
	public:
		// Invert the N x N matrix a into result.
		// Throws NotInvertibleMatrixException if a pivot is smaller than epsilon (singular matrix).
		template <int N>
		static void invert(const float (&a)[N][N], float (&result)[N][N], float epsilon)
		{
			float matrix[N][N];
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
				{
					matrix[i][j] = a[i][j];
					result[i][j] = (i == j) ? 1.0f : 0.0f;
				}

			int r = 0; // last pivot row

			// Browsing columns one by one
			for (int j = 0; j < N; j++)
			{
				int k = indiceOfMaxRowInColumn(matrix, j, r);
				float pivot = matrix[k][j];

				if (std::fabs(pivot) < epsilon) throw NotInvertibleMatrixException();

				// Divide all the row by the pivot to reduce the pivot to 1
				for (int col = 0; col < N; col++)
				{
					matrix[k][col] /= pivot;
					result[k][col] /= pivot;
				}
				// Swap the rows k and r
				if (r != k)
				{
					swapRows(matrix, r, k);
					swapRows(result, r, k);
				}
				for (int i = 0; i < N; i++)
				{
					if (i != r)
					{
						float matrix_ij = matrix[i][j];
						for (int col = 0; col < N; col++)
						{
							matrix[i][col] -= matrix[r][col] * matrix_ij;
							result[i][col] -= result[r][col] * matrix_ij;
						}
					}
				}
				r++;
			}
		}

	private:
		template <int N>
		static void swapRows(float (&a)[N][N], int r1, int r2)
		{
			for (int col = 0; col < N; col++)
			{
				float tmp = a[r1][col];
				a[r1][col] = a[r2][col];
				a[r2][col] = tmp;
			}
		}

		// Row index (from pivot row down) of the greatest absolute value in column col
		template <int N>
		static int indiceOfMaxRowInColumn(const float (&m)[N][N], int col, int pivot)
		{
			float max = std::fabs(m[pivot][col]);
			int indiceMax = pivot;
			for (int i = pivot + 1; i < N; i++)
			{
				float val = std::fabs(m[i][col]);
				if (max < val)
				{
					max = val;
					indiceMax = i;
				}
			}
			return indiceMax;
		}
	};
}

#endif // GAUSSJORDANSOLVER_H
