////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

//NOLINTBEGIN(bugprone-easily-swappable-parameters,readability-identifier-length)

#include "Vec2f.h"

#include <cmath>
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

Vec2f::Vec2f()
	:x(0), y(0) {}
Vec2f::Vec2f(float xv, float yv)
	:x(xv), y(yv) {}
Vec2f::Vec2f(std::pair<float, float>values)
	:x(values.first), y(values.second) {}

// ==========================================================
// ====================== Set methods =======================
// ==========================================================

void Vec2f::set(float newX, float newY) {
	x = newX;
	y = newY;
}
void Vec2f::set(const Vec2f& c) {
	x = c.x;
	y = c.y;
}

// ==========================================================
// ======================= Utilities ========================
// ==========================================================

// std::string Vec2f::toString() const {
// 	return "[" + std::to_string(x) + "; " + std::to_string(y) + "]";
// }
Complex Vec2f::toComplex() const {
	return {x, y};
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
Vec2f Vec2f::normalized() const {
	Vec2f v(x, y);
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
	float x = GML::clamp(0, 1, GML::lerp(a.x, b.x, t));
	float y = GML::clamp(0, 1, GML::lerp(a.y, b.y, t));
	return {x, y};
}
Vec2f Vec2f::lerpUnclamped(const Vec2f& a, const Vec2f& b, float t) {
	float x = GML::lerp(a.x, b.x, t);
	float y = GML::lerp(a.y, b.y, t);
	return {x, y};
}

// ==========================================================
// ================ Multiplication by scalar ================
// ==========================================================

void Vec2f::scale(float s) {
	x *= s;
	y *= s;
}
Vec2f Vec2f::multiplyByScalar(const Vec2f& v, float s) {
	return {v.x * s, v.y * s};
}
Vec2f Vec2f::multiplyByScalar(float s, const Vec2f& v) {
	return {v.x * s, v.y * s};
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
	return {a.x + b.x, a.y + b.y};
}
Vec2f Vec2f::substract(const Vec2f& a, const Vec2f& b) {
	return {a.x - b.x, a.y - b.y};
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

void Vec2f::transform(const Mat2f& matrix) {
	float a = matrix.m00 * x + matrix.m10 * y;
	float b = matrix.m01 * x + matrix.m11 * y;
	x = a;
	y = b;
}
Vec2f Vec2f::matrixMultiply(const Mat2f& matrix, const Vec2f& v) {
	return {matrix.m00 * v.x + matrix.m10 * v.y,
			matrix.m01 * v.x + matrix.m11 * v.y};
}

// ==========================================================
// ======================= Operators ========================
// ==========================================================

Vec2f::operator Vec3f() const {
	return {x, y, 0};
}

std::ostream& operator<<(std::ostream& os, const Vec2f& v) {
	os << "[" << v.x << "; " << v.y << "]";
	return os;
}

Vec2f operator*(float s, const Vec2f& v) {
	return {v.x * s, v.y * s};
}
Vec2f operator*(const Vec2f& v, float s) {
	return {v.x * s, v.y * s};
}
Vec2f operator/(const Vec2f& v, float s) {
	return {v.x / s, v.y / s};
}
Vec2f operator+(const Vec2f& a, const Vec2f& b) {
	return {a.x + b.x, a.y + b.y};
}
Vec2f operator-(const Vec2f& a, const Vec2f& b) {
	return {a.x - b.x, a.y - b.y};
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
Vec2f operator*(const Mat2f& matrix, const Vec2f& v) {
	return {matrix.m00 * v.x + matrix.m10 * v.y,
			matrix.m01 * v.x + matrix.m11 * v.y};
}

bool operator==(const Vec2f& a, const Vec2f& b) {
	return (a.x == b.x && a.y == b.y);
}
bool operator!=(const Vec2f& a, const Vec2f& b) {
	return a.x != b.x || a.y != b.y;
}

// ==========================================================
// ====================== /Vec2f class ======================
// ==========================================================

}

//NOLINTEND(bugprone-easily-swappable-parameters,readability-identifier-length)
