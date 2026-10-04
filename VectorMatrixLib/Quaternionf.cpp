//
// MIT License
// Copyright(c) 2021 - 2026 Olivier BARRY
// 
// This file is part of the C++ Aventura Project
// 
// VectorMatrix Math Library
//

#include <iostream>
#include <cmath>
#include <string>
#include "Quaternionf.h"
#include "Matrix3f.h"
#include "Matrix4f.h"
#include "Constants.h"
#include "Exceptions.h"
#include "MathTools.h"

namespace vectormatrix
{
	Quaternionf::Quaternionf() : x(0), y(0), z(0), w(1)
	{
	}

	Quaternionf::Quaternionf(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{
	}

	Quaternionf::Quaternionf(const Vector3f& axis, float angleRadians)
	{
		Vector3f a(axis);
		a.normalize();
		float half = angleRadians / 2;
		float sinHalf = std::sin(half);
		x = a.getX() * sinHalf;
		y = a.getY() * sinHalf;
		z = a.getZ() * sinHalf;
		w = std::cos(half);
	}

	Quaternionf::Quaternionf(const Matrix3f& m)
	{
		initFromRotationMatrix(
			m.get(0, 0), m.get(0, 1), m.get(0, 2),
			m.get(1, 0), m.get(1, 1), m.get(1, 2),
			m.get(2, 0), m.get(2, 1), m.get(2, 2));
	}

	Quaternionf::Quaternionf(const Matrix4f& m)
	{
		initFromRotationMatrix(
			m.get(0, 0), m.get(0, 1), m.get(0, 2),
			m.get(1, 0), m.get(1, 1), m.get(1, 2),
			m.get(2, 0), m.get(2, 1), m.get(2, 2));
	}

	void Quaternionf::initFromRotationMatrix(float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22)
	{
		float trace = m00 + m11 + m22;
		if (trace > 0)
		{
			float s = std::sqrt(trace + 1.0f) * 2; // s = 4*w
			w = 0.25f * s;
			x = (m21 - m12) / s;
			y = (m02 - m20) / s;
			z = (m10 - m01) / s;
		}
		else if (m00 > m11 && m00 > m22)
		{
			float s = std::sqrt(1.0f + m00 - m11 - m22) * 2; // s = 4*x
			x = 0.25f * s;
			y = (m01 + m10) / s;
			z = (m02 + m20) / s;
			w = (m21 - m12) / s;
		}
		else if (m11 > m22)
		{
			float s = std::sqrt(1.0f + m11 - m00 - m22) * 2; // s = 4*y
			y = 0.25f * s;
			x = (m01 + m10) / s;
			z = (m12 + m21) / s;
			w = (m02 - m20) / s;
		}
		else
		{
			float s = std::sqrt(1.0f + m22 - m00 - m11) * 2; // s = 4*z
			z = 0.25f * s;
			x = (m02 + m20) / s;
			y = (m12 + m21) / s;
			w = (m10 - m01) / s;
		}
	}

	Quaternionf Quaternionf::operator*(const Quaternionf& q) const
	{
		float rw = w * q.w - x * q.x - y * q.y - z * q.z;
		float rx = w * q.x + x * q.w + y * q.z - z * q.y;
		float ry = w * q.y - x * q.z + y * q.w + z * q.x;
		float rz = w * q.z + x * q.y - y * q.x + z * q.w;
		return Quaternionf(rx, ry, rz, rw);
	}

	Quaternionf& Quaternionf::operator*=(const Quaternionf& q)
	{
		*this = *this * q;
		return *this;
	}

	float Quaternionf::dot(const Quaternionf& q) const
	{
		return x * q.x + y * q.y + z * q.z + w * q.w;
	}

	bool Quaternionf::operator==(const Quaternionf& q) const
	{
		return MathTools::equals(x, q.x) && MathTools::equals(y, q.y) && MathTools::equals(z, q.z) && MathTools::equals(w, q.w);
	}

	bool Quaternionf::operator!=(const Quaternionf& q) const
	{
		return !(*this == q);
	}

	float Quaternionf::get(int i) const
	{
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			throw IndexOutOfBoundException("Index out of bound while getting coordinate (" + std::to_string(i) + ") of Quaternionf");
		}
	}

	float Quaternionf::getX() const
	{
		return x;
	}

	float Quaternionf::getY() const
	{
		return y;
	}

	float Quaternionf::getZ() const
	{
		return z;
	}

	float Quaternionf::getW() const
	{
		return w;
	}

	void Quaternionf::set(int i, float v)
	{
		switch (i) {
		case 0:
			x = v;
			break;
		case 1:
			y = v;
			break;
		case 2:
			z = v;
			break;
		case 3:
			w = v;
			break;
		default:
			throw IndexOutOfBoundException("Index out of bound while setting coordinate (" + std::to_string(i) + ") of Quaternionf");
		}
	}

	void Quaternionf::setX(float v)
	{
		x = v;
	}

	void Quaternionf::setY(float v)
	{
		y = v;
	}

	void Quaternionf::setZ(float v)
	{
		z = v;
	}

	void Quaternionf::setW(float v)
	{
		w = v;
	}

	float Quaternionf::length() const
	{
		return std::sqrt(lengthSquared());
	}

	float Quaternionf::lengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Quaternionf& Quaternionf::normalize()
	{
		float length = this->length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
		return *this;
	}

	Quaternionf Quaternionf::conjugate() const
	{
		return Quaternionf(-x, -y, -z, w);
	}

	Quaternionf Quaternionf::inverse() const
	{
		float ls = lengthSquared();
		return Quaternionf(-x / ls, -y / ls, -z / ls, w / ls);
	}

	Matrix3f Quaternionf::toMatrix3() const
	{
		float xx = x * x, yy = y * y, zz = z * z;
		float xy = x * y, xz = x * z, yz = y * z;
		float wx = w * x, wy = w * y, wz = w * z;
		float a[3][3] = {
			{ 1 - 2 * (yy + zz),     2 * (xy - wz),     2 * (xz + wy) },
			{     2 * (xy + wz), 1 - 2 * (xx + zz),     2 * (yz - wx) },
			{     2 * (xz - wy),     2 * (yz + wx), 1 - 2 * (xx + yy) }
		};
		return Matrix3f(a);
	}

	Matrix4f Quaternionf::toMatrix4() const
	{
		Matrix4f r(toMatrix3());
		r.set(3, 3, 1);
		return r;
	}

	float Quaternionf::toAxisAngle(Vector3f& axis) const
	{
		// Guard w slightly past +/-1 (float rounding on a quaternion that is only approximately
		// unit length) so acos() never receives an out-of-domain argument and returns NaN
		float cw = w;
		if (cw > 1.0f) cw = 1.0f;
		if (cw < -1.0f) cw = -1.0f;
		float angle = 2 * std::acos(cw);
		float sinHalf = std::sqrt(1 - cw * cw);
		if (sinHalf < EPSILON)
		{
			// No meaningful axis for a null (or near-null) rotation
			axis.set(1, 0, 0);
		}
		else
		{
			axis.set(x / sinHalf, y / sinHalf, z / sinHalf);
		}
		return angle;
	}

	// static member function (see declaration)
	Quaternionf Quaternionf::slerp(const Quaternionf& q1, const Quaternionf& q2, float t)
	{
		float cosOmega = q1.dot(q2);
		float x2 = q2.x, y2 = q2.y, z2 = q2.z, w2 = q2.w;
		if (cosOmega < 0)
		{
			// q2 and -q2 represent the same rotation; negate to take the shorter path
			cosOmega = -cosOmega;
			x2 = -x2; y2 = -y2; z2 = -z2; w2 = -w2;
		}

		float scale0, scale1;
		if (cosOmega > 1.0f - EPSILON)
		{
			// q1 and q2 are almost identical: sin(omega) would be ~0, fall back to a plain lerp
			scale0 = 1.0f - t;
			scale1 = t;
		}
		else
		{
			float omega = std::acos(cosOmega);
			float sinOmega = std::sin(omega);
			scale0 = std::sin((1 - t) * omega) / sinOmega;
			scale1 = std::sin(t * omega) / sinOmega;
		}

		Quaternionf result(
			scale0 * q1.x + scale1 * x2,
			scale0 * q1.y + scale1 * y2,
			scale0 * q1.z + scale1 * z2,
			scale0 * q1.w + scale1 * w2);
		result.normalize();
		return result;
	}

	std::ostream& operator<<(std::ostream& strm, const Quaternionf& q)
	{
		return strm << "Quaternionf [" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << "]";
	}
}
