////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#include "Mat3f.h"

#include <string>
#include "Vec3f.h"
#include "Mat2f.h"

namespace GML {

	// //////////////////////////////////////////////////////////
	// ====================== Mat3f class =======================
	// //////////////////////////////////////////////////////////

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================
	Mat3f::Mat3f(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12, float m22)
		: m00(m00), m10(m10), m20(m20), m01(m01), m11(m11), m21(m21), m02(m02), m12(m12), m22(m22) {}
	Mat3f::Mat3f(const Mat3f& A)
		: m00(A.m00), m10(A.m10), m20(A.m20), m01(A.m01), m11(A.m11), m21(A.m21), m02(A.m02), m12(A.m12), m22(A.m22) {}
	Mat3f::Mat3f(const Vec3f& i, const Vec3f& j, const Vec3f& k)
		: m00(i.x), m10(j.x), m20(k.x), m01(i.y), m11(j.y), m21(k.y), m02(i.z), m12(j.z), m22(k.z) {}

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	void Mat3f::set(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		m00 = a;
		m10 = b;
		m20 = c;
		m01 = d;
		m11 = e;
		m21 = f;
		m02 = g;
		m12 = h;
		m22 = i;
	}
	void Mat3f::set(const Mat3f& c) {
		m00 = c.m00;
		m10 = c.m10;
		m20 = c.m20;
		m01 = c.m01;
		m11 = c.m11;
		m21 = c.m21;
		m02 = c.m02;
		m12 = c.m12;
		m22 = c.m22;
	}

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	std::string Mat3f::toString() {
		return "(m00:" + std::to_string(m00) + ", m10" + std::to_string(m10) + ", m20" + std::to_string(m20) +
			", m01" + std::to_string(m01) + ", m11" + std::to_string(m11) + ", m21" + std::to_string(m21) +
			", m02" + std::to_string(m02) + ", m12" + std::to_string(m12) + ", m22" + std::to_string(m22);
	}
	Vec3f Mat3f::getIHat() const {
		return Vec3f(m00, m01, m02);
	}
	Vec3f Mat3f::getJHat() const {
		return Vec3f(m10, m11, m12);
	}
	Vec3f Mat3f::getKHat() const {
		return Vec3f(m20, m21, m22);
	}
	float Mat3f::getDeterminant() const {
		return (m00 * m11 * m22 + m10 * m21 * m02 + m20 * m01 * m12) - (m02 * m11 * m20 + m12 * m21 * m00 + m22 * m01 * m10);
	}
	void Mat3f::invert() {
		if(getDeterminant()) {
			float s = 1 / (getDeterminant());
			float t00 = (m11 * m22 - m21 * m12) * s;
			float t01 = -(m01 * m22 - m21 * m02) * s;
			float t02 = (m01 * m12 - m11 * m02) * s;
			float t10 = -(m10 * m22 - m20 * m12) * s;
			float t11 = -(m00 * m22 - m20 * m02) * s;
			float t12 = -(m00 * m12 - m10 * m02) * s;
			float t20 = (m10 * m21 - m20 * m11) * s;
			float t21 = -(m00 * m21 - m20 * m01) * s;
			float t22 = (m00 * m11 - m10 * m01) * s;
			m00 = t00;
			m01 = t01;
			m02 = t02;
			m10 = t10;
			m11 = t11;
			m12 = t12;
			m20 = t20;
			m21 = t21;
			m22 = t22;
		}

	}
	Mat3f Mat3f::invert(const Mat3f& T) {
		Mat3f M = T;
		M.invert();
		return M;
	}
	void Mat3f::transpose() {
		float t01 = m10;
		float t02 = m20;
		float t12 = m21;
		float t10 = m01;
		float t20 = m02;
		float t21 = m12;
		m01 = t01;
		m02 = t02;
		m12 = t12;
		m10 = t10;
		m20 = t20;
		m21 = t21;
	}
	Mat3f Mat3f::transpose(const Mat3f& T) {
		return Mat3f(T.m00, T.m01, T.m02, T.m10, T.m11, T.m12, T.m20, T.m21, T.m22);
	}

	// ==========================================================
	// ================= Matrix multiplication ==================
	// ==========================================================

	void Mat3f::multiply(const Mat3f& T) {
		float t00 = T.m00 * m00 + T.m10 * m01 + T.m20 * m02;
		float t01 = T.m01 * m00 + T.m11 * m01 + T.m21 * m02;
		float t02 = T.m02 * m00 + T.m12 * m01 + T.m22 * m02;
		float t10 = T.m00 * m10 + T.m10 * m11 + T.m20 * m12;
		float t11 = T.m01 * m10 + T.m11 * m11 + T.m21 * m12;
		float t12 = T.m02 * m10 + T.m12 * m11 + T.m22 * m12;
		float t20 = T.m00 * m20 + T.m10 * m21 + T.m20 * m22;
		float t21 = T.m01 * m20 + T.m11 * m21 + T.m21 * m22;
		float t22 = T.m02 * m20 + T.m12 * m21 + T.m22 * m22;
		m00 = t00;
		m01 = t01;
		m02 = t02;
		m10 = t10;
		m11 = t11;
		m12 = t12;
		m20 = t20;
		m21 = t21;
		m22 = t22;
	}
	Mat3f Mat3f::multiply(const Mat3f& A, const Mat3f& B) {
		return Mat3f(A.m00 * B.m00 + A.m10 * B.m01 + A.m20 * B.m02,
			A.m00 * B.m10 + A.m10 * B.m11 + A.m20 * B.m12,
			A.m00 * B.m20 + A.m10 * B.m21 + A.m20 * B.m22,
			A.m01 * B.m00 + A.m11 * B.m01 + A.m21 * B.m02,
			A.m01 * B.m10 + A.m11 * B.m11 + A.m21 * B.m12,
			A.m01 * B.m20 + A.m11 * B.m21 + A.m21 * B.m22,
			A.m02 * B.m00 + A.m12 * B.m01 + A.m22 * B.m02,
			A.m02 * B.m10 + A.m12 * B.m11 + A.m22 * B.m12,
			A.m02 * B.m20 + A.m12 * B.m21 + A.m22 * B.m22);
	}

	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	Mat3f::operator Mat2f() const {
		return Mat2f(m00, m10, m01, m11);
	}

	std::ostream& operator<<(std::ostream& os, const Mat3f& A) {
		os << "\n" << A.m00 << " " << A.m10 << " " << A.m20 << "\n" << A.m01 << " " << A.m11 << " " << A.m21 << "\n" << A.m02 << " " << A.m12 << " " << A.m22 << "\n";
		return os;
	}

	Mat3f operator*(const Mat3f& A, const Mat3f& B) {
		return Mat3f(A.m00 * B.m00 + A.m10 * B.m01 + A.m20 * B.m02,
			A.m00 * B.m10 + A.m10 * B.m11 + A.m20 * B.m12,
			A.m00 * B.m20 + A.m10 * B.m21 + A.m20 * B.m22,
			A.m01 * B.m00 + A.m11 * B.m01 + A.m21 * B.m02,
			A.m01 * B.m10 + A.m11 * B.m11 + A.m21 * B.m12,
			A.m01 * B.m20 + A.m11 * B.m21 + A.m21 * B.m22,
			A.m02 * B.m00 + A.m12 * B.m01 + A.m22 * B.m02,
			A.m02 * B.m10 + A.m12 * B.m11 + A.m22 * B.m12,
			A.m02 * B.m20 + A.m12 * B.m21 + A.m22 * B.m22);
	}
	void Mat3f::operator*=(const Mat3f& m) {
		multiply(m);
	}

	Mat3f operator!(const Mat3f& m) {
		return Mat3f::invert(m);
	}
	Mat3f operator~(const Mat3f& m) {
		return Mat3f::transpose(m);

	}

	bool operator==(const Mat3f& a, const Mat3f& b) {
		return (a.m00 == b.m00 && a.m10 == b.m10 && a.m20 == b.m20
			&& a.m01 == b.m01 && a.m11 == b.m11 && a.m21 == b.m21
			&& a.m02 == b.m02 && a.m12 == b.m12 && a.m22 == b.m22);
	}
	bool operator!=(const Mat3f& a, const Mat3f& b) {
		return !(a.m00 == b.m00 && a.m10 == b.m10 && a.m20 == b.m20
			&& a.m01 == b.m01 && a.m11 == b.m11 && a.m21 == b.m21
			&& a.m02 == b.m02 && a.m12 == b.m12 && a.m22 == b.m22);
	}

	// ==========================================================
	// ====================== /Mat3f class ======================
	// ==========================================================

}