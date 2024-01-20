////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

//NOLINTBEGIN(bugprone-easily-swappable-parameters,readability-identifier-length)

#include "Mat2f.h"

#include <string>
#include "Vec2f.h"
#include "Mat3f.h"
#include "../Numbers/Complex.h"

namespace GML {

// //////////////////////////////////////////////////////////
// ====================== Mat2f class =======================
// //////////////////////////////////////////////////////////

// ==========================================================
// ====================== Constructors ======================
// ==========================================================

Mat2f::Mat2f()
	:m00(1), m10(0), m01(0), m11(1) {}
Mat2f::Mat2f(float v00, float v10, float v01, float v11)
	: m00(v00), m10(v10), m01(v01), m11(v11) {}
Mat2f::Mat2f(const Vec2f& i, const Vec2f& j)
	: m00(i.x), m10(j.x), m01(i.y), m11(j.y) {}

// ==========================================================
// ====================== Set methods =======================
// ==========================================================

void Mat2f::set(float newm00, float newm10, float newm01, float newm11) {
	m00 = newm00;
	m10 = newm10;
	m01 = newm01;
	m11 = newm11;
}
void Mat2f::set(const Mat2f& c) {
	m00 = c.m00;
	m10 = c.m10;
	m01 = c.m01;
	m11 = c.m11;
}

// ==========================================================
// ======================= Utilities ========================
// ==========================================================

// std::string Mat2f::toString() const {
// 	return "(m00:" + std::to_string(m00) + ", m10" + std::to_string(m10) + ", m01" + std::to_string(m01) + ", m11" + std::to_string(m11) + ")";
// }
Vec2f Mat2f::getIHat() const {
	return {m00, m01};
}
Vec2f Mat2f::getJHat() const {
	return {m10, m11};
}
float Mat2f::getDeterminant() const {
	return m00 * m11 - m10 * m01;
}
void Mat2f::invert() {
	if(getDeterminant() != 0) {
		const float s = 1 / (getDeterminant());
		float t00 = m11 * s;
		float t01 = -m01 * s;
		float t10 = -m10 * s;
		float t11 = m00 * s;
		m00 = t00;
		m01 = t01;
		m10 = t10;
		m11 = t11;
	}

}
Mat2f Mat2f::invert(const Mat2f& T) {
	Mat2f M = T;
	M.invert();
	return M;
}
void Mat2f::transpose() {
	float t01 = m10;
	float t10 = m01;
	m01 = t01;
	m10 = t10;
}
Mat2f Mat2f::transpose(const Mat2f& T) {
	return {T.m00, T.m10, T.m01, T.m11};
}

// ==========================================================
// ================= Matrix multiplication ==================
// ==========================================================

void Mat2f::multiply(const Mat2f& A) {
	float t00 = A.m00 * m00 + A.m10 * m01;
	float t01 = A.m01 * m00 + A.m11 * m01;
	float t10 = A.m00 * m10 + A.m10 * m11;
	float t11 = A.m01 * m10 + A.m11 * m11;
	m00 = t00;
	m01 = t01;
	m10 = t10;
	m11 = t11;
}
Mat2f Mat2f::multiply(const Mat2f& A, const Mat2f& B) {
	return {A.m00 * B.m00 + A.m10 * B.m01,
			  A.m01 * B.m00 + A.m11 * B.m01,
			  A.m00 * B.m10 + A.m10 * B.m11,
			  A.m01 * B.m10 + A.m11 * B.m11};
}

// ==========================================================
// ======================= Operators ========================
// ==========================================================

Mat2f::operator Mat3f() const {
	return {m00, m10, 0, m01, m11, 0, 0, 0, 0};
}

std::ostream& operator<<(std::ostream& os, const Mat2f& A) {
	os << "\n" << A.m00 << " " << A.m10 << "\n" << A.m01 << " " << A.m11 << "\n";
	return os;
}

Mat2f operator*(const Mat2f& A, const Mat2f& B) {
	return {A.m00 * B.m00 + A.m10 * B.m01,
			  A.m01 * B.m00 + A.m11 * B.m01,
			  A.m00 * B.m10 + A.m10 * B.m11,
			  A.m01 * B.m10 + A.m11 * B.m11};
}
void Mat2f::operator*=(const Mat2f& m) {
	multiply(m);
}

Mat2f operator!(const Mat2f& m) {
	return Mat2f::invert(m);
}
Mat2f operator~(const Mat2f& m) {
	return Mat2f::transpose(m);

}

bool operator==(const Mat2f& a, const Mat2f& b) {
	return (a.m00 == b.m00 && a.m10 == b.m10 && a.m01 == b.m01 && a.m11 == b.m11);
}
bool operator!=(const Mat2f& a, const Mat2f& b) {
	return a.m00 != b.m00 || a.m10 != b.m10 || a.m01 != b.m01 || a.m11 != b.m11;
}

// ==========================================================
// ====================== /Mat2f class ======================
// ==========================================================

}

//NOLINTEND(bugprone-easily-swappable-parameters,readability-identifier-length)
