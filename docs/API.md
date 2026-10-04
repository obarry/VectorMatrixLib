# API guide

Everything lives in the `vectormatrix` namespace. Include the header of each class you use (`#include "Vector3f.h"`, ...). The headers are short and commented: they are the reference, this page is the map.

## Classes

| Header | Content |
|---|---|
| `Vector2f.h` | 2D vector |
| `Vector3f.h` | 3D vector |
| `Vector4f.h` | 3D point or vector in homogeneous coordinates (x, y, z, w) |
| `Matrix2f.h`, `Matrix3f.h`, `Matrix4f.h` | 2x2, 3x3 and 4x4 matrices of `float` |
| `Quaternionf.h` | quaternion `w + xi + yj + zk`, for rotations |
| `GaussJordanSolver.h` | matrix inversion used by `Matrix3f` and `Matrix4f` (header only) |
| `Tools.h` | `Tools::interpolate` for vectors and scalars (header only) |
| `GeometryTools.h` | `GeometryTools::center` of a set of points |
| `Constants.h` | `EPSILON` (1e-4), `SIZE_2/3/4`, `X_AXIS`, `Y_AXIS`, `Z_AXIS` |
| `MathTools.h` | `MathTools::equals(a, b)`: floats equal within `EPSILON` |
| `Exceptions.h` | `Vector3DException` and its subclasses |

## Vectors

All vector classes share the same shape:

```cpp
Vector3f a(1, 2, 3), b(4, 5, 6);
Vector3f c = a + b - a * 2;      // + - and * / by a float, and their += -= *= /= forms
float d = a.dot(b);              // dot product
Vector3f n = a.cross(b);         // cross product, also a * b (and a.crossEquals(b))
float l = a.length();            // also lengthSquared(), distance(b), distanceSquared(b)
a.normalize();                   // modifies a and returns it
float x = a.get(0);              // or getX(); get(3) throws IndexOutOfBoundException
std::array<float, 3> arr = a.toArray();
Vector3f m = Vector3f::interpolate(a, b, 0.5f);  // a*(1-t) + b*t
```

- Constant vectors are functions returning a fresh copy: `Vector3f::xAxis()`, `yAxis()`, `zAxis()`, `xOppAxis()`, ..., `zeroVector()`, and `Vector4f::zeroPoint()`.
- Constructors from a `std::vector<float>` throw `VectorArrayWrongSizeException` when it is too short.
- `Vector3f` and `Vector4f` convert into each other: `v3.V4()` (w = 0), `v4.V3()`, `Vector3f(v4)`, `Vector4f(v3)`.
- A row or a column of a matrix: `Vector3f(r, M)` is row `r`, `Vector3f(M, c)` is column `c` (same for `Vector4f`).

### Points and vectors: `Vector4f`

`w = 1` marks a point, `w = 0` a vector: a translation matrix moves points and leaves vectors unchanged, and the difference of two points is a vector.

```cpp
Vector4f p(1, 2, 3, 1), q(4, 6, 3, 1);
Vector4f pq(p, q);                  // q - p, w = 0
bool b = pq.isVector();             // also isPoint(), point(), vector()
std::optional<Vector3f> r = Vector4f(2, 4, 6, 2).get3DPoint();  // (1, 2, 3): x/w, y/w, z/w
// get3DPoint() of a vector (w = 0) is empty
```

`Vector4f` cross product and `*` between two `Vector4f` treat both as vectors (w = 0).

## Matrices

Matrices are stored row-major, `get(row, column)`, and act on column vectors.

```cpp
const float values[3][3] = { { 2, 0, 1 }, { 1, 3, 2 }, { 1, 1, 2 } };
Matrix3f m(values);                 // also Matrix3f(a): all elements equal to a, Matrix3f::identity()
Matrix3f p = m * m.transpose();     // + - * with matrices, * with a float, and += -= *=
Vector3f v = m * Vector3f(1, 2, 3); // A.V
float det = m.determinant();        // also trace(), isIdentity()
Matrix3f inv = m.inverse();         // throws NotInvertibleMatrixException if singular
Vector3f row = m.getRow(1);         // also getColumn, setRow, setColumn (checked indices)
std::vector<std::vector<float>> a = m.getArray();   // copy; setArray(a) checks the size
```

- `get(i, j)` and `set(i, j, v)` do not check their indices, for speed.
- `setDiagonal(v)` sets the diagonal; `transposeEquals()` transposes in place.
- `Matrix4f(Matrix3f)` copies the 3x3 part and leaves the rest at 0 (including [3][3]); `Matrix4f::getMatrix3()` and `Matrix3f(Matrix4f)` extract the upper-left 3x3 part.
- `v * M` computes the same A·V as `M * v`, to keep the meaning of Java's `v.times(M)`.
- Write float literals for the "all elements" constructor: `Matrix4f(0)` is ambiguous with the array constructor, `Matrix4f(0.0f)` is not.

## Quaternions

```cpp
Quaternionf q(Vector3f::zAxis(), angle);   // rotation of angle (radians) around an axis
Quaternionf r(rotationMatrix);             // from a Matrix3f or Matrix4f
Quaternionf qr = q * r;                    // Hamilton product: r is applied first, then q
Matrix3f m3 = q.toMatrix3();               // toMatrix4() sets [3][3] to 1
Vector3f axis;
float a = q.toAxisAngle(axis);
Quaternionf s = Quaternionf::slerp(q, r, 0.5f);  // takes the shorter path
```

Also `conjugate()`, `inverse()`, `normalize()`, `length()`, `dot()`, and `get`/`set` of the components. `Quaternionf()` is the identity (0, 0, 0, 1). Remember that `q` and `-q` are the same rotation.

## Helpers

- `Tools::interpolate(a, b, t)` for `Vector2f`, `Vector3f`, `Vector4f`, `float` and `double`: `a*(1-t) + b*t`; `t` outside [0, 1] extrapolates.
- `GeometryTools::center(points)` for a `std::vector<Vector4f>` or a `std::vector<std::vector<Vector4f>>`: the average of x, y, z with w = 1, or an empty `std::optional` when there is no point.
- `GaussJordanSolver::invert<N>(a, result, epsilon)` inverts any N x N `float` array; `indiceOfMaxRowInColumn` is public so that the pivoting can be tested.

## Exceptions

All derive from `Vector3DException`, itself a `std::runtime_error`, so one `catch (const Vector3DException&)` handles them all.

| Exception | Thrown by |
|---|---|
| `IndexOutOfBoundException` | vector and quaternion `get(i)`/`set(i, v)`, matrix rows and columns |
| `VectorArrayWrongSizeException` | vector constructors from a too short `std::vector` |
| `MatrixArrayWrongSizeException` | `setArray` with a wrong size |
| `NotInvertibleMatrixException` | `inverse()` of a singular matrix |

## Mapping from Aventura (Java)

| Java (`com.aventura.math.vector`) | C++ (`vectormatrix`) |
|---|---|
| `Vector3`, `Matrix4`, `Quaternion`, ... | `Vector3f`, `Matrix4f`, `Quaternionf`, ... |
| `a.plus(b)`, `a.minus(b)` | `a + b`, `a - b` |
| `a.plusEquals(b)`, `a.minusEquals(b)` | `a += b`, `a -= b` |
| `a.times(2f)`, `a.timesEquals(2f)` | `a * 2`, `a *= 2` |
| `a.cross(b)`, `a.crossEquals(b)` | `a.cross(b)` or `a * b`, `a.crossEquals(b)` |
| `a.dot(b)` | `a.dot(b)` |
| `A.times(B)`, `A.times(v)`, `v.times(A)` | `A * B`, `A * v`, `v * A` (all A·V) |
| `a.equals(b)` | `a == b` (within EPSILON) |
| `new Vector3(v)`, `v.copy()` | copy constructor |
| `null` result | empty `std::optional` |
| `equals(Object)`, `hashCode()` | not needed |
| `float[][] getArray()`, `setArray(float[][])` | `std::vector<std::vector<float>>` |
| `Constants.EPSILON` | `EPSILON` |
| `Tools`, `GeometryTools` | `Tools`, `GeometryTools` |
| `Vector2.set(x, y)` | `setX(x); setY(y);` (a `set(x, y)` would be ambiguous with `set(i, v)`) |

Not ported: the classes of the rest of the engine (`Rotation`, `Translation`, `Scaling`, projections), see the possible step P5 in [HISTORY.md](HISTORY.md).
