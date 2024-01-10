////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#include "Vec4f.h"

#include <cmath>
#include <string>
#include "Mat4f.h"
#include "Vec3f.h"
#include "Vec2f.h"
#include "../Utils.h"

namespace GML {

	// //////////////////////////////////////////////////////////
	// ====================== Vec3f class =======================
	// //////////////////////////////////////////////////////////

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	Vec4f::Vec4f(float x, float y, float z, float w)
		:x(x), y(y), z(z), w(w) {}
	Vec4f::Vec4f(const Vec4f& v)
		:x(v.x), y(v.y), z(v.z), w(v.w) {}

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	void Vec4f::set(float a, float b, float c, float d) {
		x = a;
		y = b;
		z = c;
		w = d;
	}
	void Vec4f::set(const Vec4f& c) {
		x = c.x;
		y = c.y;
		z = c.z;
		w = c.w;
	}

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	std::string Vec4f::toString() const {
		return "[" + std::to_string(x) + "; " + std::to_string(y) + "; " + std::to_string(z) + "; " + std::to_string(w) + "]";
	}
	float Vec4f::getLength() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}
	float Vec4f::getLengthSquared() const {
		return x * x + y * y + z * z + w * w;
	}
	void Vec4f::normalize() {
		scale(1 / getLength());
	}
	Vec4f Vec4f::normalized() {
		Vec4f v = (x, y, z, w);
		v.normalize();
		return v;
	}
	Vec4f Vec4f::normalize(const Vec4f& v) {
		Vec4f w = v;
		w.normalize();
		return w;
	}

	// ==========================================================
	// ===================== Interpolations =====================
	// ==========================================================

	Vec4f Vec4f::lerp(const Vec4f& a, const Vec4f& b, float t) {
		t = GML::clamp(0, 1, t);
		float x = GML::lerp(a.x, b.x, t);
		float y = GML::lerp(a.y, b.y, t);
		float z = GML::lerp(a.z, b.z, t);
		float w = GML::lerp(a.w, b.w, t);
		return Vec4f(x, y, z, w);
	}
	Vec4f Vec4f::lerpUnclamped(const Vec4f& a, const Vec4f& b, float t) {
		float x = GML::lerp(a.x, b.x, t);
		float y = GML::lerp(a.y, b.y, t);
		float z = GML::lerp(a.z, b.z, t);
		float w = GML::lerp(a.w, b.w, t);
		return Vec4f(x, y, z, w);
	}

	// ==========================================================
	// ================ Multiplication by scalar ================
	// ==========================================================

	void Vec4f::scale(const float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}
	Vec4f Vec4f::multiplyByScalar(const Vec4f& v, const float s) {
		return Vec4f(v.x * s, v.y * s, v.z * s, v.w * s);
	}
	Vec4f Vec4f::multiplyByScalar(const float s, const Vec4f& v) {
		return Vec4f(v.x * s, v.y * s, v.z * s, v.w * s);
	}

	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	void Vec4f::add(const Vec4f& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}
	void Vec4f::substract(const Vec4f& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
	}
	Vec4f Vec4f::add(const Vec4f& a, const Vec4f& b) {
		return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}
	Vec4f Vec4f::substract(const Vec4f& a, const Vec4f& b) {
		return Vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	// ==========================================================
	// ==================== Vector products =====================
	// ==========================================================

	float Vec4f::dotProduct(const Vec4f& v) const {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}
	float Vec4f::dotProduct(const Vec4f& a, const Vec4f& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	// ==========================================================
	// ==================== Mat4f transform =====================
	// ==========================================================

	void Vec4f::transform(const Mat4f& T) {
		float a = T.m00 * x + T.m10 * y + T.m20 * z + T.m30 * w;
		float b = T.m01 * x + T.m11 * y + T.m21 * z + T.m31 * w;
		float c = T.m02 * x + T.m12 * y + T.m22 * z + T.m32 * w;
		float d = T.m03 * x + T.m13 * y + T.m23 * z + T.m33 * w;
		x = a;
		y = b;
		z = c;
		w = d;
	}
	Vec4f Vec4f::matrixMultiply(const Mat4f& T, const Vec4f& v) {
		return Vec4f(T.m00 * v.x + T.m10 * v.y + T.m20 * v.z + T.m30 * v.w,
			T.m01 * v.x + T.m11 * v.y + T.m21 * v.z + T.m31 * v.w,
			T.m02 * v.x + T.m12 * v.y + T.m22 * v.z + T.m32 * v.w,
			T.m03 * v.x + T.m13 * v.y + T.m23 * v.z + T.m33 * v.w);
	}

	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	Vec4f::operator Vec3f() const {
		return Vec3f(x, y, z);
	}
	Vec4f::operator Vec2f() const {
		return Vec2f(x, y);
	}

	std::ostream& operator<<(std::ostream& os, const Vec4f& v) {
		os << "[" << v.x << "; " << v.y << "; " << v.z << "; " << v.w << "]";
		return os;
	}

	Vec4f operator*(const float s, const Vec4f& v) {
		return Vec4f(v.x * s, v.y * s, v.z * s, v.w * s);
	}
	Vec4f operator*(const Vec4f& v, const float s) {
		return Vec4f(v.x * s, v.y * s, v.z * s, v.w * s);
	}
	Vec4f operator+(const Vec4f& a, const Vec4f& b) {
		return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}
	Vec4f operator-(const Vec4f& a, const Vec4f& b) {
		return Vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	void Vec4f::operator*=(float s) {
		scale(s);
	}
	void Vec4f::operator/=(float s) {
		scale(1 / s);
	}
	void Vec4f::operator+=(const Vec4f& v) {
		add(v);
	}
	void Vec4f::operator-=(const Vec4f& v) {
		substract(v);
	}
	float operator*(const Vec4f& a, const Vec4f& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	Vec4f operator*(const Mat4f& T, const Vec4f& v) {
		return Vec4f(T.m00 * v.x + T.m10 * v.y + T.m20 * v.z + T.m30 * v.w,
			T.m01 * v.x + T.m11 * v.y + T.m21 * v.z + T.m31 * v.w,
			T.m02 * v.x + T.m12 * v.y + T.m22 * v.z + T.m32 * v.w,
			T.m03 * v.x + T.m13 * v.y + T.m23 * v.z + T.m33 * v.w);
	}

	bool operator==(const Vec4f& a, const Vec4f& b) {
		return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
	}
	bool operator!=(const Vec4f& a, const Vec4f& b) {
		return !(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
	}

	// ==========================================================
	// ====================== /Vec4f class ======================
	// ==========================================================

}