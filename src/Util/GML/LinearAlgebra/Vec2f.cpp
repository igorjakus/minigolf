////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#include "Vec2f.h"

#include <cmath>
#include <string>
#include "Mat2f.h"
#include "Vec3f.h"
#include "../Utils.h"
#include "../Numbers/Complex.h"

namespace GML {

	// //////////////////////////////////////////////////////////
	// ====================== Vec2f class =======================
	// //////////////////////////////////////////////////////////

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	Vec2f::Vec2f(float x, float y)
		:x(x), y(y) {}
	Vec2f::Vec2f(const Vec2f& v)
		:x(v.x), y(v.y) {}

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	void Vec2f::set(float a, float b) {
		x = a;
		y = b;
	}
	void Vec2f::set(const Vec2f& c) {
		x = c.x;
		y = c.y;
	}

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	std::string Vec2f::toString() const {
		return "[" + std::to_string(x) + "; " + std::to_string(y) + "]";
	}
	Complex Vec2f::toComplex() const {
		return Complex(x, y);
	}
	float Vec2f::getLength() const {
		return std::sqrt(x * x + y * y);
	}	
	float Vec2f::getLengthSquared() const {
		return x * x + y * y;
	}
	void Vec2f::normalize() {
		scale(1 / getLength());
	}
	Vec2f Vec2f::normalized() {
		Vec2f v = (x, y);
		v.normalize();
		return v;
	}
	Vec2f Vec2f::normalize(const Vec2f& v) {
		Vec2f w = v;
		w.normalize();
		return w;
	}

	// ==========================================================
	// ===================== Interpolations =====================
	// ==========================================================

	Vec2f Vec2f::lerp(const Vec2f& a, const Vec2f& b, float t) {
		t = GML::clamp(0, 1, t);
		float x = GML::lerp(a.x, b.x, t);
		float y = GML::lerp(a.y, b.y, t);
		return Vec2f(x, y);
	}
	Vec2f Vec2f::lerpUnclamped(const Vec2f& a, const Vec2f& b, float t) {
		float x = GML::lerp(a.x, b.x, t);
		float y = GML::lerp(a.y, b.y, t);
		return Vec2f(x, y);
	}

	// ==========================================================
	// ================ Multiplication by scalar ================
	// ==========================================================

	void Vec2f::scale(float s) {
		x *= s;
		y *= s;
	}
	Vec2f Vec2f::multiplyByScalar(const Vec2f& v, float s) {
		return Vec2f(v.x * s, v.y * s);
	}
	Vec2f Vec2f::multiplyByScalar(float s, const Vec2f& v) {
		return Vec2f(v.x * s, v.y * s);
	}

	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	void Vec2f::add(const Vec2f& v) {
		x += v.x;
		y += v.y;
	}
	void Vec2f::substract(const Vec2f& v) {
		x -= v.x;
		y -= v.y;
	}
	Vec2f Vec2f::add(const Vec2f& a, const Vec2f& b) {
		return Vec2f(a.x + b.x, a.y + b.y);
	}
	Vec2f Vec2f::substract(const Vec2f& a, const Vec2f& b) {
		return Vec2f(a.x - b.x, a.y - b.y);
	}

	// ==========================================================
	// ==================== Vector products =====================
	// ==========================================================

	float Vec2f::dotProduct(const Vec2f& v) const {
		return x * v.x + y * v.y;
	}
	float Vec2f::dotProduct(const Vec2f& a, const Vec2f& b) {
		return a.x * b.x + a.y * b.y;
	}

	float Vec2f::crossProduct(const Vec2f& v) const {
		return x * v.y - y * v.x;
	}
	float Vec2f::crossProduct(const Vec2f& a, const Vec2f& b) {
		return a.x * b.y - a.y * b.x;
	}

	// ==========================================================
	// ==================== Mat2f transform =====================
	// ==========================================================

	void Vec2f::transform(const Mat2f& T) {
		float a = T.m00 * x + T.m10 * y;
		float b = T.m01 * x + T.m11 * y;
		x = a;
		y = b;
	}
	Vec2f Vec2f::matrixMultiply(const Mat2f& T, const Vec2f& v) {
		return Vec2f(T.m00 * v.x + T.m10 * v.y, T.m01 * v.x + T.m11 * v.y);
	}

	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	Vec2f::operator Vec3f() const {
		return Vec3f(x, y, 0);
	}

	std::ostream& operator<<(std::ostream& os, const Vec2f& v) {
		os << "[" << v.x << "; " << v.y << "]";
		return os;
	}

	Vec2f operator*(float s, const Vec2f& v) {
		return Vec2f(v.x * s, v.y * s);
	}
	Vec2f operator*(const Vec2f& v, float s) {
		return Vec2f(v.x * s, v.y * s);
	}
	Vec2f operator+(const Vec2f& a, const Vec2f& b) {
		return Vec2f(a.x + b.x, a.y + b.y);
	}
	Vec2f operator-(const Vec2f& a, const Vec2f& b) {
		return Vec2f(a.x - b.x, a.y - b.y);
	}

	void Vec2f::operator*=(float s) {
		scale(s);
	}
	void Vec2f::operator/=(float s) {
		scale(1 / s);
	}
	void Vec2f::operator+=(const Vec2f& v) {
		add(v);
	}
	void Vec2f::operator-=(const Vec2f& v) {
		substract(v);
	}
	float operator*(const Vec2f& a, const Vec2f& b) {
		return a.x * b.x + a.y * b.y;
	}
	float operator%(const Vec2f& a, const Vec2f& b) {
		return a.x * b.y - a.y * b.x;
	}
	Vec2f operator*(const Mat2f& T, const Vec2f& v) {
		return Vec2f(T.m00 * v.x + T.m10 * v.y, T.m01 * v.x + T.m11 * v.y);
	}

	bool operator==(const Vec2f& a, const Vec2f& b) {
		return (a.x == b.x && a.y == b.y);
	}
	bool operator!=(const Vec2f& a, const Vec2f& b) {
		return !(a.x == b.x && a.y == b.y);
	}

	// ==========================================================
	// ====================== /Vec2f class ======================
	// ==========================================================

}