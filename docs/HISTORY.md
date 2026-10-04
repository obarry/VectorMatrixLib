# History: from Aventura (Java) to VectorMatrixLib (C++)

## Aventura, the origin

[Aventura](https://github.com/obarry/Aventura) is a lightweight 3D rendering engine written by Olivier BARRY in 100% pure Java: no GPU, no native code, no third-party library. It builds a scene through a plain Java API (shapes, textures, lights, shadows, camera), then transforms, projects and rasterizes it on the CPU, with a Z-buffer, lighting and shadow mapping.

Everything in such an engine rests on a small amount of linear algebra: points and vectors in homogeneous coordinates, 4x4 transformation matrices composed along a scene graph, matrix inversion to go back from camera to world space, and rotations. Aventura gathers it in its own package, `com.aventura.math.vector`:

- `Vector2`, `Vector3`, `Vector4`, `Matrix2`, `Matrix3`, `Matrix4`;
- `Quaternion`, with `slerp`, used for rotations;
- `GaussJordanSolver`, the matrix inversion shared by `Matrix3` and `Matrix4`;
- `Tools` and `GeometryTools` (interpolation, center of a set of points);
- a common `Vector3DException` hierarchy, and float comparisons within `Constants.EPSILON`;
- a few hundred JUnit tests covering all of it.

## The C++ port (2021 - 2023)

VectorMatrixLib started in 2021 as the first brick of a C++ version of Aventura: every source file still says it is "part of the C++ Aventura Project". The math package was the natural place to start, since the rest of the engine depends on it and it depends on nothing.

That first version translated the four core classes, `Vector3f`, `Vector4f`, `Matrix3f` and `Matrix4f` (the `f` suffix marks single precision `float`, as in many C++ graphics libraries), with C++ operators in place of Java's `plus`, `minus` and `times`, and a small console program, `TestMatrix.cpp`, to try them. It was built with Visual Studio only. Its last update dates from August 2023.

In the meantime, the Java library kept evolving: new classes, the Gauss-Jordan solver, EPSILON comparisons, exceptions, many bug fixes, and a large test suite. By 2026 the two had drifted far apart.

## Bringing it up to date (October 2026)

In October 2026 the C++ library was compared class by class with `com.aventura.math.vector`, and brought up to date in five steps, each one built and tested before the next:

| Step | Content |
|---|---|
| P0 | Fixed the bugs of the first version (`Vector4f::setW`, `Matrix3f::operator-=`, `Matrix3f * float` returning a `Matrix4f`, an out of bound read in `Matrix4f(Matrix3f)`, memory leaks from `new` in operators), const-correctness; added a CMake build, a first test program and CI on Linux, Windows and macOS. |
| P1 | `EPSILON` and `MathTools::equals`, `==` and `!=` within EPSILON, and the exception hierarchy of Aventura (`Vector3DException` and its subclasses). |
| P2 | Completed `Vector3f`, `Vector4f`, `Matrix3f` and `Matrix4f` with the rest of the Java API, including inversion through a shared `GaussJordanSolver`. |
| P3 | Added `Vector2f`, `Matrix2f` and `Quaternionf`. |
| P4 | Ported the JUnit tests, added `Tools` and `GeometryTools`, a console tour of the API, and this documentation. |

A possible next step (P5) is to port Aventura's transformations and projections (rotation, translation, scaling, frustum and orthographic projection matrices) on top of this library.

## What changed in the translation

The C++ library keeps the names, the semantics and the numerical behavior of the Java one, so that a test written for one holds for the other. The differences come from the language:

- **Operators instead of methods.** `a.plus(b)` is `a + b`, `a.timesEquals(2)` is `a *= 2`, `M.times(v)` is `M * v`. Java's `v.times(M)` keeps its meaning: `v * M` is also A·V.
- **Values instead of references.** C++ objects are copied by value, so Java's `copy()` is the copy constructor, and there is no `null`: a missing result is an empty `std::optional`.
- **No `equals(Object)` or `hashCode`**: `==` and `!=` compare within EPSILON.
- **Unchecked `Matrix get(i, j)` and `set(i, j, v)`**, for speed; rows, columns and vector coordinates are checked and throw `IndexOutOfBoundException`.
- **`Quaternionf`** instead of `Quaternion`, for consistency with the other `f` classes.
- **`Vector2f` has no `set(x, y)`**: it would be ambiguous with `set(int i, float v)`.
- **`GeometryTools::center` of a 2D set** counts every point, where Java assumes all rows have the length of the first one.

[API.md](API.md) gives the full mapping, class by class.
