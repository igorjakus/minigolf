// 
// Quaternion.cpp
//
// Class representing quaternions
//

#include "Quaternion.h"

#include <string>
#include "../LinearAlgebra/Vec3f.h"

namespace GML {

	// //////////////////////////////////////////////////////////
	// =================== Quaternion class =====================
	// //////////////////////////////////////////////////////////

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	Quaternion::Quaternion(float w, float x, float y, float z)
		: w(w), x(x), y(y), z(z) {}
	Quaternion::Quaternion(const Quaternion& m)
		: w(m.w), x(m.x), y(m.y), z(m.z) {}

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	void Quaternion::set(float a, float b, float c, float d) {
		w = a;
		x = b;
		y = c;
		z = d;
	}
	void Quaternion::set(const Quaternion& c) {
		w = c.w;
		x = c.x;
		y = c.y;
		z = c.z;
	}

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	std::string Quaternion::toString() const {
		std::string s = std::to_string(w);
		if (x >= 0)
			s += "+";
		s += std::to_string(x) + "i";
		if (y >= 0)
			s += "+";
		s += std::to_string(y) + "j";
		if (z >= 0)
			s += "+";
		s += std::to_string(z) + "k";
		return s;
	}
	float Quaternion::getMagnitude() const {
		return std::sqrt(w * w + x * x + y * y + z * z);
	}
	float Quaternion::getMagnitudeSquared() const {
		return w * w + x * x + y * y + z * z;
	}
	float Quaternion::getUnrealMagnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}
	float Quaternion::getUnrealMagnitudeSquared() const {
		return x * x + y * y + z * z;
	}
	Quaternion Quaternion::getConjugate() const {
		return Quaternion(w, -x, -y, -z);
	}
	Quaternion Quaternion::getInverse() const {
		return getConjugate() * (1 / getMagnitudeSquared());
	}
	Quaternion operator!(const Quaternion& m) {
		return Quaternion(m.w, -m.x, -m.y, -m.z);
	}
	Quaternion operator~(const Quaternion& m) {
		return m.getConjugate() * (1 / m.getMagnitudeSquared());
	}
	void Quaternion::normalize() {
		float mod = getMagnitude();
		w /= mod;
		x /= mod;
		y /= mod;
		z /= mod;
		
	}
	Quaternion Quaternion::normalized() {
		float mod = getMagnitude();
		return Quaternion(w / mod, x / mod, y / mod, z / mod);
	}
	Quaternion Quaternion::normalize(const Quaternion& m) {
		float mod = m.getMagnitude();
		return Quaternion(m.w / mod, m.x / mod, m.y / mod, m.z /mod);
	}
	void Quaternion::normalizeUnreal() {
		float mod = getUnrealMagnitude();
		x /= mod;
		y /= mod;
		z /= mod;
	}
	Quaternion Quaternion::normalizedUnreal() {
		float mod = getUnrealMagnitude();
		return Quaternion(w, x / mod, y / mod, z / mod);
	}
	Quaternion Quaternion::normalizeUnreal(const Quaternion& m) {
		float mod = m.getUnrealMagnitude();
		return Quaternion(m.w, m.x / mod, m.y / mod, m.z / mod);
	}
	Quaternion Quaternion::createRotation(float angle, const Vec3f& axis) {
		Vec3f v = Vec3f::normalize(axis) * std::sin(angle);
		return Quaternion(std::cos(angle), v.x, v.y, v.z);
	}

	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	void Quaternion::add(const Quaternion& m) {
		w += m.w;
		x += m.x;
		y += m.y;
		z += m.z;
	}
	void Quaternion::substract(const Quaternion& m) {
		w -= m.w;
		x -= m.x;
		y -= m.y;
		z -= m.z;
	}

	Quaternion Quaternion::add(const Quaternion& m, const Quaternion& n) {
		return Quaternion(m.w + n.w, m.x + n.x, m.y + n.y, m.z + n.z);
	}
	Quaternion Quaternion::substract(const Quaternion& m, const Quaternion& n) {
		return Quaternion(m.w - n.w, m.x - n.x, m.y - n.y, m.z - n.z);
	}

	// ==========================================================
	// ===================== Multiplication =====================
	// ==========================================================

	void Quaternion::multiply(const Quaternion& m) {
		float newW = w * m.w - x * m.x - y * m.y - z * m.z;
		float newX = w * m.x + x * m.w + y * m.z - z * m.y;
		float newY = w * m.y - x * m.z + y * m.w + z * m.x;
		float newZ = w * m.z + x * m.y - y * m.x + z * m.w;
		w = newW;
		x = newX;
		y = newY;
		z = newZ;
	}
	void Quaternion::divide(const Quaternion& m) {
		Quaternion q = m.getInverse();
		multiply(q);
	}

	Quaternion Quaternion::multiply(const Quaternion& m, const Quaternion& n) {
		return Quaternion(m.w * n.w - m.x * n.x - m.y * n.y - m.z * n.z,
			m.w * n.x + m.x * n.w + m.y * n.z - m.z * n.y,
			m.w * n.y - m.x * n.z + m.y * n.w + m.z * n.x,
			m.w * n.z + m.x * n.y - m.y * n.x + m.z * n.w);
	}
	Quaternion Quaternion::divide(const Quaternion& z, const Quaternion& w) {
		return z * w.getInverse();
	}

	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Quaternion& m) {
		os << m.w;
		if (m.x >= 0)
			os << "+";
		os << m.x << "i";
		if (m.y >= 0)
			os << "+";
		os << m.y << "j";
		if (m.z >= 0)
			os << "+";
		os << m.z << "k";
		return os;
	}

	Quaternion operator+(const Quaternion& m, const Quaternion& n) {
		return Quaternion::add(m, n);
	}
	Quaternion operator-(const Quaternion& m, const Quaternion& n) {
		return Quaternion::substract(m, n);
	}
	Quaternion operator*(const Quaternion& m, const Quaternion& n) {
		return Quaternion::multiply(m, n);
	}
	Quaternion operator/(const Quaternion& m, const Quaternion& n) {
		return Quaternion::divide(m, n);
	}

	void Quaternion::operator+=(const Quaternion& m) {
		add(m);
	}
	void Quaternion::operator-=(const Quaternion& m) {
		substract(m);
	}
	void Quaternion::operator*=(const Quaternion& m) {
		multiply(m);
	}
	void Quaternion::operator/=(const Quaternion& m) {
		divide(m);
	}

	bool operator==(const Quaternion& m, const Quaternion& n) {
		return (m.w == n.w && m.x == n.x && m.y == n.y && m.z == n.z);
	}
	bool operator!=(const Quaternion& m, const Quaternion& n) {
		return !(m.w == n.w && m.x == n.x && m.y == n.y && m.z == n.z);
	}

	// ==========================================================
	// =================== /Quaternion class ====================
	// ==========================================================

}