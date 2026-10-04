# VectorMatrixLib

**A small C++17 vector, matrix and quaternion library for 3D graphics, ported from the math package of the [Aventura](https://github.com/obarry/Aventura) Java rendering engine.**

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Build: CMake | Visual Studio](https://img.shields.io/badge/build-CMake%20%7C%20Visual%20Studio-informational.svg)

VectorMatrixLib gives you the building blocks of a 3D pipeline: vectors and points in homogeneous coordinates, 2x2, 3x3 and 4x4 matrices with inversion, and quaternions for rotations. It has no dependency other than the C++ standard library, and it follows the same API and semantics as Aventura's `com.aventura.math.vector`, so code and tests move easily from one to the other.

## Highlights

- **Vectors:** `Vector2f`, `Vector3f`, `Vector4f` (points with `w = 1`, vectors with `w = 0`), with dot and cross products, length, distance, normalization and interpolation.
- **Matrices:** `Matrix2f`, `Matrix3f`, `Matrix4f`, with products, transpose, determinant, trace, rows and columns, and inversion by Gauss-Jordan elimination with partial pivoting.
- **Quaternions:** `Quaternionf` from an axis and an angle or from a rotation matrix, Hamilton product, conversion to matrices and to axis-angle, and `slerp`.
- **Helpers:** `Tools::interpolate` and `GeometryTools::center`.
- **Robust comparisons:** `==` and `!=` compare within `EPSILON` (`1e-4`), as in Aventura.
- **Clear errors:** out of bound indices, wrong array sizes and singular matrices throw exceptions derived from `Vector3DException`.
- **Tested:** about 230 unit tests, most of them ported from Aventura's JUnit tests, run by CI on Linux, Windows and macOS.

## Quick start

```cpp
#include <iostream>
#include "Matrix4f.h"
#include "Quaternionf.h"
#include "Vector4f.h"

using namespace vectormatrix;

int main()
{
	// A point (w = 1) and a rotation of 90 degrees around the z axis
	Vector4f p(1, 0, 0, 1);
	Quaternionf q(Vector3f::zAxis(), 3.14159265f / 2);
	Matrix4f r = q.toMatrix4();

	// Translation of 10 along x, in the last column
	Matrix4f t = Matrix4f::identity();
	t.setColumn(3, Vector4f(10, 0, 0, 1));

	Vector4f moved = t * r * p;                     // rotate, then translate: (10, 1, 0, 1)
	Vector4f back = (t * r).inverse() * moved;       // p again
	std::cout << (back == p ? "round trip OK" : "KO") << std::endl;
}
```

The demo program prints a guided tour of the whole API, section by section (vectors, homogeneous coordinates, matrices and linear systems, transformations, quaternions and slerp, 2D, geometry helpers, errors). It is the best place to see the library in action.

## Build

### CMake (any platform)

```bash
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure   # unit tests
./build/vectormatrix_demo                               # console tour (build/Release/ on Windows)
```

Targets:

| Target | What it is |
|---|---|
| `vectormatrix` | the static library |
| `vectormatrix_demo` | the console tour, `VectorMatrixLib/VectorMatrixDemo.cpp` |
| `vectormatrix_tests` | the unit tests, `tests/*.cpp` (an argument filters the suites, e.g. `vectormatrix_tests Matrix`) |

To use the library from your own CMake project, add this repository with `add_subdirectory` and link to `vectormatrix`; its include directory comes with it.

### Visual Studio

Open `VectorMatrixLib.sln` (VS 2019 or later, toolset v142, C++17): it builds the library and the demo. Visual Studio can also open the folder directly and use `CMakeLists.txt`, which includes the tests (Test Explorer runs them through CTest).

## Conventions

A few rules to know before using the library; [docs/API.md](docs/API.md) details all of them.

- **Matrices are row-major and act on column vectors:** `M * v` computes A·V. For compatibility with Aventura's `v.times(M)`, `v * M` computes the same A·V.
- **`*` between two vectors is the cross product**; the dot product is `dot()`.
- **Homogeneous coordinates:** `Vector4f` points have `w = 1` and vectors `w = 0`, so a translation matrix moves points and leaves vectors unchanged.
- **Comparisons use `EPSILON`:** `Vector3f(1, 2, 3) == Vector3f(1, 2, 3.00001f)` is true.
- **Index checks:** vector `get(i)`/`set(i, v)` and matrix rows and columns throw `IndexOutOfBoundException`; matrix `get(i, j)`/`set(i, j, v)` are not checked, for speed.
- **No null:** where Aventura returns `null`, the C++ API returns an empty `std::optional` (`Vector4f::get3DPoint`, `GeometryTools::center`).

## Project layout

```
VectorMatrixLib/      library sources (namespace vectormatrix), demo, Visual Studio project
tests/                unit tests: TestFramework.h, TestMain.cpp, one file per class
docs/                 documentation
CMakeLists.txt        CMake build (library, demo, tests)
.github/workflows/    CI on Linux, Windows and macOS
```

## Documentation

- [docs/API.md](docs/API.md): the classes, their semantics, and the mapping from Aventura's Java API.
- [docs/HISTORY.md](docs/HISTORY.md): the genesis of this library from the Aventura Java project, and how it was brought up to date.
- [docs/TESTING.md](docs/TESTING.md): the test framework and how the JUnit tests were ported.

## License

MIT, Copyright (c) 2021 - 2026 Olivier BARRY.
