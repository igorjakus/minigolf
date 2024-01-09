////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#include "Vec3f.h"

#include <cmath>
#include <string>
#include "Mat3f.h"
#include "Vec2f.h"
#include "../Utils.h"

namespace GML {

	// //////////////////////////////////////////////////////////
	// ====================== Vec3f class =======================
	// //////////////////////////////////////////////////////////

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	Vec3f::Vec3f(float x, float y, float z)
		:x(x), y(y), z(z) {}
	Vec3f::Vec3f(const Vec3f& v)
		:x(v.x), y(v.y), z(v.z) {}

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	void Vec3f::set(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	void Vec3f::set(const Vec3f& c) {
		x = c.x;
		y = c.y;
		z = c.z;
	}

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	std::string Vec3f::toString() const {
		return "[" + std::to_string(x) + "; " + std::to_string(y) + "; " + std::to_string(z) + "]";
	}
	float Vec3f::getLength() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	float Vec3f::getLengthSquared() const {
		return x * x + y * y + z * z;
	}
	void Vec3f::normalize() {
		scale(1 / getLength());
	}
	Vec3f Vec3f::normalized() {
		Vec3f v = (x, y, z);
		v.normalize();
		return v;
	}
	Vec3f Vec3f::normalize(const Vec3f& v) {
		Vec3f w = v;
		w.normalize();
		return w;
	}

	// ==========================================================
	// ===================== Interpolations =====================
	// ==========================================================

	Vec3f Vec3f::lerp(const Vec3f& a, const Vec3f& b, float t) {
		t = GML::clamp(0, 1, t);
		float x = GML::lerp(a.x, b.x, t);
		float y = GML::lerp(a.y, b.y, t);
		float z = GML::lerp(a.z, b.z, t);
		return Vec3f(x, y, z);
	}
	Vec3f Vec3f::lerpUnclamped(const Vec3f& a, const Vec3f& b, float t) {
		float x = GML::lerp(a.x, b.x, t);
		float y = GML::lerp(a.y, b.y, t);
		float z = GML::lerp(a.z, b.z, t);
		return Vec3f(x, y, z);
	}

	// ==========================================================
	// ================ Multiplication by scalar ================
	// ==========================================================

	void Vec3f::scale(const float s) {
		x *= s;
		y *= s;
		z *= s;
	}
	Vec3f Vec3f::multiplyByScalar(const Vec3f& v, const float s) {
		return Vec3f(v.x * s, v.y * s, v.z * s);
	}
	Vec3f Vec3f::multiplyByScalar(const float s, const Vec3f& v) {
		return Vec3f(v.x * s, v.y * s, v.z * s);
	}

	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	void Vec3f::add(const Vec3f& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void Vec3f::substract(const Vec3f& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	Vec3f Vec3f::add(const Vec3f& a, const Vec3f& b) {
		return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	Vec3f Vec3f::substract(const Vec3f& a, const Vec3f& b) {
		return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	// ==========================================================
	// ==================== Vector products =====================
	// ==========================================================

	float Vec3f::dotProduct(const Vec3f& v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	float Vec3f::dotProduct(const Vec3f& a, const Vec3f& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Vec3f Vec3f::crossProduct(const Vec3f& v) const {
		return Vec3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	Vec3f Vec3f::crossProduct(const Vec3f& a, const Vec3f& b) {
		return Vec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	// ==========================================================
	// ==================== Mat3f transform =====================
	// ==========================================================

	void Vec3f::transform(const Mat3f& T) {
		float a = T.m00 * x + T.m10 * y + T.m20 * z;
		float b = T.m01 * x + T.m11 * y + T.m21 * z;
		float c = T.m02 * x + T.m12 * y + T.m22 * z;
		x = a;
		y = b;
		z = c;
	}
	Vec3f Vec3f::matrixMultiply(const Mat3f& T, const Vec3f& v) {
		return Vec3f(T.m00 * v.x + T.m10 * v.y + T.m20 * v.z,
			T.m01 * v.x + T.m11 * v.y + T.m21 * v.z,
			T.m02 * v.x + T.m12 * v.y + T.m22 * v.z);
	}

	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	Vec3f::operator Vec2f() const {
		return Vec2f(x, y);
	}

	std::ostream& operator<<(std::ostream& os, const Vec3f& v) {
		os << "[" << v.x << "; " << v.y << "; " << v.z << "]";
		return os;
	}

	Vec3f operator*(const float s, const Vec3f& v) {
		return Vec3f(v.x * s, v.y * s, v.z * s);
	}
	Vec3f operator*(const Vec3f& v, const float s) {
		return Vec3f(v.x * s, v.y * s, v.z * s);
	}
	Vec3f operator+(const Vec3f& a, const Vec3f& b) {
		return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	Vec3f operator-(const Vec3f& a, const Vec3f& b) {
		return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	void Vec3f::operator*=(float s) {
		scale(s);
	}
	void Vec3f::operator/=(float s) {
		scale(1 / s);
	}
	void Vec3f::operator+=(const Vec3f& v) {
		add(v);
	}
	void Vec3f::operator-=(const Vec3f& v) {
		substract(v);
	}
	float operator*(const Vec3f& a, const Vec3f& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	Vec3f operator%(const Vec3f& a, const Vec3f& b) {
		return Vec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
	Vec3f operator*(const Mat3f& T, const Vec3f& v) {
		return Vec3f(T.m00 * v.x + T.m10 * v.y + T.m20 * v.z,
			T.m01 * v.x + T.m11 * v.y + T.m21 * v.z,
			T.m02 * v.x + T.m12 * v.y + T.m22 * v.z);
	}

	bool operator==(const Vec3f& a, const Vec3f& b) {
		return (a.x == b.x && a.y == b.y && a.z == b.z);
	}
	bool operator!=(const Vec3f& a, const Vec3f& b) {
		return !(a.x == b.x && a.y == b.y && a.z == b.z);
	}

	// ==========================================================
	// ====================== /Vec3f class ======================
	// ==========================================================

}