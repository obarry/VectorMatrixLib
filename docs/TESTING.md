# Tests

## Running them

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

or run `build/vectormatrix_tests` directly to see the result of each suite. An argument runs only the suites whose name contains it: `vectormatrix_tests Quaternion`. The program returns a nonzero exit code when a test fails, which is what CTest and the CI check.

## The framework

`tests/TestFramework.h` is a minimal framework with no dependency, in the spirit of JUnit:

```cpp
#include "TestFramework.h"
#include "Vector3f.h"

using namespace vectormatrix;

TEST(Vector3f, length)
{
	CHECK_NEAR(Vector3f(3, 4, 0).length(), 5.0f);
}
```

Each `TEST(Suite, name)` registers itself, and `tests/TestMain.cpp` runs them all, grouped by suite. A failed check prints its file, line and expression, and the test goes on with its next checks.

| Macro | JUnit equivalent | Checks that |
|---|---|---|
| `CHECK(expr)` | `assertTrue` | `expr` is true |
| `CHECK_EQUAL(actual, expected)` | `assertEquals(expected, actual)` | `actual == expected` (within EPSILON for the library classes); prints both on failure |
| `CHECK_NEAR(actual, expected)` | `assertEquals(expected, actual, EPSILON)` | the floats differ by at most `EPSILON` |
| `CHECK_NEAR_TOL(actual, expected, tol)` | `assertEquals(expected, actual, tol)` | the floats differ by at most `tol` |
| `CHECK_THROWS(expr, Exception)` | `assertThrows` | `expr` throws `Exception` or a subclass |
| `CHECK_NO_THROW(expr)` | | `expr` throws nothing |

An exception escaping a test is reported as a failure of that test.

To add a test file, create it in `tests/` and add it to `vectormatrix_tests` in `CMakeLists.txt`.

## Where the tests come from

| File | Suite | Origin |
|---|---|---|
| `TestVector2f.cpp` ... `TestVector4f.cpp` | `Vector2f` ... `Vector4f` | Aventura `TestVector2.java` ... `TestVector4.java` |
| `TestMatrix2f.cpp` ... `TestMatrix4f.cpp` | `Matrix2f` ... `Matrix4f` | Aventura `TestMatrix2.java` ... `TestMatrix4.java` |
| `TestQuaternionf.cpp` | `Quaternionf` | Aventura `TestQuaternion.java` |
| `TestGaussJordanSolver.cpp` | `GaussJordanSolver` | Aventura `TestGaussJordanSolver.java` |
| `TestVector3fMatrix3f.cpp` | `Vector3fMatrix3f` | Aventura `TestVector3Matrix3.java` |
| `TestTools.cpp`, `TestGeometryTools.cpp` | `Tools`, `GeometryTools` | Aventura `TestTools.java`, `TestGeometryTools.java` |
| `TestVectorMatrix.cpp` | `CppSpecific` | written for the C++ library: EPSILON comparisons, exceptions, conversions between classes, and the behaviors that differ from Java |

The JUnit tests were ported one for one, in the same order and with the same values, so that a failure can be compared with the Java side. A few could not be, and are marked `// Not ported:` with the reason where they would be:

- tests of `equals(Object)`, `hashCode` and `null` arguments, which have no C++ counterpart;
- tests of protected Java helpers (`timesRow`, `swapRows`) and of their visibility;
- a static `Vector2.equals(v1, v2)` and a deprecated method.

Checks that compare Java references (two calls returning different objects) were dropped from tests that otherwise were ported, since C++ returns values; the value checks around them were kept. The tests that relied on Aventura's `Rotation` class build the same matrix with a local helper using the formula of `Rotation.initRotation`.
