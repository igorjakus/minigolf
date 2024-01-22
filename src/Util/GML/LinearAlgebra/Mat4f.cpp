////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

//NOLINTBEGIN(bugprone-easily-swappable-parameters,readability-identifier-length)

#include "Mat4f.h"

#include <string>
#include "Vec4f.h"
#include "Mat3f.h"
#include "Mat2f.h"

namespace GML {

// //////////////////////////////////////////////////////////
// ====================== Mat4f class =======================
// //////////////////////////////////////////////////////////

// ==========================================================
// ====================== Constructors ======================
// ==========================================================

Mat4f::Mat4f()
	: m00(1), m10(), m20(), m30(), m01(), m11(1), m21(), m31(), m02(), m12(), m22(1), m32(), m03(), m13(), m23(), m33(1) {}
Mat4f::Mat4f(float v00, float v10, float v20, float v30, float v01, float v11, float v21, float v31, float v02, float v12, float v22, float v32, float v03, float v13, float v23, float v33)
	: m00(v00), m10(v10), m20(v20), m30(v30), m01(v01), m11(v11), m21(v21), m31(v31), m02(v02), m12(v12), m22(v22), m32(v32), m03(v03), m13(v13), m23(v23), m33(v33) {}
Mat4f::Mat4f(const Vec4f& i, const Vec4f& j, const Vec4f& k, const Vec4f& w)
	: m00(i.x), m10(j.x), m20(k.x), m30(w.x), m01(i.y), m11(j.y), m21(k.y), m31(w.y), m02(i.z), m12(j.z), m22(k.z), m32(w.z), m03(i.w), m13(j.w), m23(k.w), m33(w.w) {}

// ==========================================================
// ====================== Set methods =======================
// ==========================================================

void Mat4f::set(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) {
	m00 = a;
	m10 = b;
	m20 = c;
	m30 = d;
	m01 = e;
	m11 = f;
	m21 = g;
	m31 = h;
	m02 = i;
	m12 = j;
	m22 = k;
	m32 = l;
	m03 = m;
	m13 = n;
	m23 = o;
	m33 = p;
}
void Mat4f::set(const Mat4f& c) {
	m00 = c.m00;
	m10 = c.m10;
	m20 = c.m20;
	m30 = c.m30;
	m01 = c.m01;
	m11 = c.m11;
	m21 = c.m21;
	m31 = c.m31;
	m02 = c.m02;
	m12 = c.m12;
	m22 = c.m22;
	m32 = c.m32;
	m03 = c.m03;
	m13 = c.m13;
	m23 = c.m23;
	m33 = c.m33;
}

// ==========================================================
// ======================= Utilities ========================
// ==========================================================

// std::string Mat4f::toString() const {
// 	return "(m00:" + std::to_string(m00) + ", m10" + std::to_string(m10) + ", m20" + std::to_string(m20) + ", m30" + std::to_string(m30) +
// 	", m01" + std::to_string(m01) + ", m11" + std::to_string(m11) + ", m21" + std::to_string(m21) + ", m31" + std::to_string(m31) +
// 	", m02" + std::to_string(m02) + ", m12" + std::to_string(m12) + ", m22" + std::to_string(m22) + ", m32" + std::to_string(m32) +
// 	", m03" + std::to_string(m03) + ", m13" + std::to_string(m13) + ", m23" + std::to_string(m23) + ", m33" + std::to_string(m33);
// }
Vec4f Mat4f::getIHat() const {
	return {m00, m01, m02, m03};
}
Vec4f Mat4f::getJHat() const {
	return {m10, m11, m12, m13};
}
Vec4f Mat4f::getKHat() const {
	return {m20, m21, m22, m23};
}
Vec4f Mat4f::getWHat() const {
	return {m30, m31, m32, m33};
}
float Mat4f::getDeterminant() const {
	return (m00 * m11 * m22 * m33 + m10 * m21 * m32 * m03 + m20 * m31 * m02 * m13 + m30 * m01 * m12 * m23) -
	(m03 * m12 * m21 * m30 + m13 * m22 * m31 * m00 + m23 * m32 * m01 * m10 + m33 * m02 * m11 * m20);
}
void Mat4f::invert() {
	//TODO
}
Mat4f Mat4f::invert(const Mat4f& T) {
	//TODO
	return T;
}
void Mat4f::transpose() {
	float t01 = m10;
	float t02 = m20;
	float t03 = m30;
	float t12 = m21;
	float t13 = m31;
	float t23 = m32;
	float t10 = m01;
	float t20 = m02;
	float t30 = m03;
	float t21 = m12;
	float t31 = m13;
	float t32 = m23;
	m01 = t01;
	m02 = t02;
	m03 = t03;
	m12 = t12;
	m13 = t13;
	m23 = t23;
	m10 = t10;
	m20 = t20;
	m30 = t30;
	m21 = t21;
	m31 = t31;
	m32 = t32;
}
Mat4f Mat4f::transpose(const Mat4f& T) {
	return {T.m00, T.m01, T.m02, T.m03, T.m10, T.m11, T.m12, T.m13, T.m20, T.m21, T.m22, T.m23, T.m30, T.m31, T.m32, T.m33};
}

// ==========================================================
// ================= Matrix multiplication ==================
// ==========================================================

void Mat4f::multiply(const Mat4f& T) {
	float t00 = m00 * T.m00 + m10 * T.m01 + m20 * T.m02 + m30 * T.m03;
	float t10 = m00 * T.m10 + m10 * T.m11 + m20 * T.m12 + m30 * T.m13;
	float t20 = m00 * T.m20 + m10 * T.m21 + m20 * T.m22 + m30 * T.m23;
	float t30 = m00 * T.m30 + m10 * T.m31 + m20 * T.m32 + m30 * T.m33;

	float t01 = m01 * T.m00 + m11 * T.m01 + m21 * T.m02 + m31 * T.m03;
	float t11 = m01 * T.m10 + m11 * T.m11 + m21 * T.m12 + m31 * T.m13;
	float t21 = m01 * T.m20 + m11 * T.m21 + m21 * T.m22 + m31 * T.m23;
	float t31 = m01 * T.m30 + m11 * T.m31 + m21 * T.m32 + m31 * T.m33;

	float t02 = m02 * T.m00 + m12 * T.m01 + m22 * T.m02 + m32 * T.m03;
	float t12 = m02 * T.m10 + m12 * T.m11 + m22 * T.m12 + m32 * T.m13;
	float t22 = m02 * T.m20 + m12 * T.m21 + m22 * T.m22 + m32 * T.m23;
	float t32 = m02 * T.m30 + m12 * T.m31 + m22 * T.m32 + m32 * T.m33;

	float t03 = m03 * T.m00 + m13 * T.m01 + m23 * T.m02 + m33 * T.m03;
	float t13 = m03 * T.m10 + m13 * T.m11 + m23 * T.m12 + m33 * T.m13;
	float t23 = m03 * T.m20 + m13 * T.m21 + m23 * T.m22 + m33 * T.m23;
	float t33 = m03 * T.m30 + m13 * T.m31 + m23 * T.m32 + m33 * T.m33;

	m00 = t00;
	m10 = t10;
	m20 = t20;
	m30 = t30;

	m01 = t01;
	m11 = t11;
	m21 = t21;
	m31 = t31;

	m02 = t02;
	m12 = t12;
	m22 = t22;
	m32 = t32;

	m03 = t03;
	m13 = t13;
	m23 = t23;
	m33 = t33;
}
Mat4f Mat4f::multiply(const Mat4f& A, const Mat4f& B) {
	return {A.m00 * B.m00 + A.m10 * B.m01 + A.m20 * B.m02 + A.m30 * B.m03,
			  A.m00 * B.m10 + A.m10 * B.m11 + A.m20 * B.m12 + A.m30 * B.m13,
			  A.m00 * B.m20 + A.m10 * B.m21 + A.m20 * B.m22 + A.m30 * B.m23,
			  A.m00 * B.m30 + A.m10 * B.m31 + A.m20 * B.m32 + A.m30 * B.m33,
			  A.m01 * B.m00 + A.m11 * B.m01 + A.m21 * B.m02 + A.m31 * B.m03,
			  A.m01 * B.m10 + A.m11 * B.m11 + A.m21 * B.m12 + A.m31 * B.m13,
			  A.m01 * B.m20 + A.m11 * B.m21 + A.m21 * B.m22 + A.m31 * B.m23,
			  A.m01 * B.m30 + A.m11 * B.m31 + A.m21 * B.m32 + A.m31 * B.m33,
			  A.m02 * B.m00 + A.m12 * B.m01 + A.m22 * B.m02 + A.m32 * B.m03,
			  A.m02 * B.m10 + A.m12 * B.m11 + A.m22 * B.m12 + A.m32 * B.m13,
			  A.m02 * B.m20 + A.m12 * B.m21 + A.m22 * B.m22 + A.m32 * B.m23,
			  A.m02 * B.m30 + A.m12 * B.m31 + A.m22 * B.m32 + A.m32 * B.m33,
			  A.m03 * B.m00 + A.m13 * B.m01 + A.m23 * B.m02 + A.m33 * B.m03,
			  A.m03 * B.m10 + A.m13 * B.m11 + A.m23 * B.m12 + A.m33 * B.m13,
			  A.m03 * B.m20 + A.m13 * B.m21 + A.m23 * B.m22 + A.m33 * B.m23,
			  A.m03 * B.m30 + A.m13 * B.m31 + A.m23 * B.m32 + A.m33 * B.m33};
}

// ==========================================================
// ======================= Operators ========================
// ==========================================================

Mat4f::operator Mat3f() const {
	return {m00, m10, m20, m01, m11, m21, m02, m12, m22};
}
Mat4f::operator Mat2f() const {
	return {m00, m10, m01, m11};
}

std::ostream& operator<<(std::ostream& os, const Mat4f& A) {
	os << "\n" << A.m00 << " " << A.m10 << " " << A.m20 << " " << A.m30 << "\n" << A.m01 << " " << A.m11 << " " << A.m21 << " " << A.m31 << "\n" << A.m02 << " " << A.m12 << " " << A.m22 << " " << A.m32 << "\n" << A.m03 << " " << A.m13 << " " << A.m23 << " " << A.m33 << "\n";
	return os;
}

Mat4f operator*(const Mat4f& A, const Mat4f& B) {
	return {A.m00 * B.m00 + A.m10 * B.m01 + A.m20 * B.m02 + A.m30 * B.m03,
			  A.m00 * B.m10 + A.m10 * B.m11 + A.m20 * B.m12 + A.m30 * B.m13,
			  A.m00 * B.m20 + A.m10 * B.m21 + A.m20 * B.m22 + A.m30 * B.m23,
			  A.m00 * B.m30 + A.m10 * B.m31 + A.m20 * B.m32 + A.m30 * B.m33,
			  A.m01 * B.m00 + A.m11 * B.m01 + A.m21 * B.m02 + A.m31 * B.m03,
			  A.m01 * B.m10 + A.m11 * B.m11 + A.m21 * B.m12 + A.m31 * B.m13,
			  A.m01 * B.m20 + A.m11 * B.m21 + A.m21 * B.m22 + A.m31 * B.m23,
			  A.m01 * B.m30 + A.m11 * B.m31 + A.m21 * B.m32 + A.m31 * B.m33,
			  A.m02 * B.m00 + A.m12 * B.m01 + A.m22 * B.m02 + A.m32 * B.m03,
			  A.m02 * B.m10 + A.m12 * B.m11 + A.m22 * B.m12 + A.m32 * B.m13,
			  A.m02 * B.m20 + A.m12 * B.m21 + A.m22 * B.m22 + A.m32 * B.m23,
			  A.m02 * B.m30 + A.m12 * B.m31 + A.m22 * B.m32 + A.m32 * B.m33,
			  A.m03 * B.m00 + A.m13 * B.m01 + A.m23 * B.m02 + A.m33 * B.m03,
			  A.m03 * B.m10 + A.m13 * B.m11 + A.m23 * B.m12 + A.m33 * B.m13,
			  A.m03 * B.m20 + A.m13 * B.m21 + A.m23 * B.m22 + A.m33 * B.m23,
			  A.m03 * B.m30 + A.m13 * B.m31 + A.m23 * B.m32 + A.m33 * B.m33};
}
void Mat4f::operator*=(const Mat4f& m) {
	multiply(m);
}

Mat4f operator!(const Mat4f& m) {
	return Mat4f::invert(m);
}
Mat4f operator~(const Mat4f& m) {
	return Mat4f::transpose(m);

}

bool operator==(const Mat4f& a, const Mat4f& b) {
	return a.m00 == b.m00 && a.m10 == b.m10 && a.m20 == b.m20 && a.m30 == b.m30
		&& a.m01 == b.m01 && a.m11 == b.m11 && a.m21 == b.m21 && a.m31 == b.m31
		&& a.m02 == b.m02 && a.m12 == b.m12 && a.m22 == b.m22 && a.m32 == b.m32
		&& a.m03 == b.m03 && a.m13 == b.m13 && a.m23 == b.m23 && a.m33 == b.m33;
}
bool operator!=(const Mat4f& a, const Mat4f& b) {
	return a.m00 != b.m00 || a.m10 != b.m10 || a.m20 != b.m20 || a.m30 != b.m30
		|| a.m01 != b.m01 || a.m11 != b.m11 || a.m21 != b.m21 || a.m31 != b.m31
		|| a.m02 != b.m02 || a.m12 != b.m12 || a.m22 != b.m22 || a.m32 != b.m32
		|| a.m03 != b.m03 || a.m13 != b.m13 || a.m23 != b.m23 || a.m33 != b.m33;
}

// ==========================================================
// ====================== /Mat4f class ======================
// ==========================================================

}

//NOLINTEND(bugprone-easily-swappable-parameters,readability-identifier-length)
