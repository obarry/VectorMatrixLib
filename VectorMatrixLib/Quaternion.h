//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include "Vector3f.h"

namespace vectormatrix
{
	class Matrix3f;
	class Matrix4f;

	// Quaternion q = w + xi + yj + zk, used to represent rotations (same as Aventura Quaternion)
	class Quaternion
	{
	public:

		// Constructors
		// Identity quaternion (0, 0, 0, 1): no rotation
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		// Rotation of angleRadians around axis (the axis is normalized)
		Quaternion(const Vector3f& axis, float angleRadians);
		// From a rotation matrix (upper-left 3x3 part for a Matrix4f)
		explicit Quaternion(const Matrix3f& m);
		explicit Quaternion(const Matrix4f& m);

		// Operators
		// Hamilton product
		Quaternion operator*(const Quaternion& q) const;
		Quaternion& operator*=(const Quaternion& q);
		float dot(const Quaternion& q) const;
		// Equality within EPSILON tolerance
		bool operator==(const Quaternion& q) const;
		bool operator!=(const Quaternion& q) const;

		// getter and setter (get and set throw IndexOutOfBoundException if i is out of bound)
		float get(int i) const;
		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		void set(int i, float v);
		void setX(float v);
		void setY(float v);
		void setZ(float v);
		void setW(float v);

		// Other methods
		float length() const;
		float lengthSquared() const;
		// Normalize this quaternion (modified) and return it
		Quaternion& normalize();
		Quaternion conjugate() const;
		Quaternion inverse() const;
		Matrix3f toMatrix3() const;
		Matrix4f toMatrix4() const;
		// Return the rotation angle (radians) and set axis to the rotation axis (x axis for a null rotation)
		float toAxisAngle(Vector3f& axis) const;

		// Static methods
		// Spherical linear interpolation, taking the shorter path
		static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);

	private:
		void initFromRotationMatrix(float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);

		float x;
		float y;
		float z;
		float w;
		friend std::ostream& operator<<(std::ostream&, const Quaternion&);
	};
}

#endif // QUATERNION_H
