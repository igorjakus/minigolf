////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#include "Complex.h"

#include <string>
#include "../Constants.h"
#include "../Utils.h"
#include "../LinearAlgebra/Vec2f.h"
#include "../LinearAlgebra/Mat2f.h"

namespace GML {

	// //////////////////////////////////////////////////////////
	// ===================== Complex class ======================
	// //////////////////////////////////////////////////////////

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	Complex::Complex(float a, float b)
		: re(a), im(b) {}
	Complex::Complex(const Complex& z)
		: re(z.re), im(z.im) {}

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	void Complex::set(float a, float b) {
		re = a;
		im = b;
	}
	void Complex::set(const Complex& c) {
		re = c.re;
		im = c.im;
	}

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	std::string Complex::toString() const {
		std::string s = std::to_string(re);
		if (im >= 0)
			s += "+";
		s += std::to_string(im) + "i";
		return s;
	}
	Vec2f Complex::toVec2f() const {
		return Vec2f(re, im);
	}
	Mat2f Complex::toMat2f() const {
		return Mat2f(re, -im, im, re);
	}
	float Complex::getMagnitude() const {
		return std::sqrt(re * re + im * im);
	}
	float Complex::getMagnitudeSquared() const {
		return re * re + im * im;
	}
	float Complex::getArgument() const {
		if (re == 0 && im == 0)
			return 0;
		return std::atan(im / re);
	}
	Complex Complex::getConjugate() const {
		return Complex(re, -im);
	}
	Complex operator!(const Complex& z) {
		return z.getConjugate();
	}
	void Complex::normalize() {
		float mod = getMagnitude();
		re /= mod;
		im /= mod;
	}
	Complex Complex::normalized() {
		float mod = getMagnitude();
		return Complex(re / mod, im / mod);
	}
	Complex Complex::normalize(const Complex& z) {
		float mod = z.getMagnitude();
		return Complex(z.re / mod, z.im / mod);
	}

	Complex Complex::createRotation(float angle) {
		return Complex(std::cos(angle), std::sin(angle));
	}

	// ==========================================================
	// ===================== Interpolations =====================
	// ==========================================================

	Complex Complex::lerp(const Complex& a, const Complex& b, float t) {
		t = clamp(0, 1, t);
		float re = GML::lerp(a.re, b.re, t);
		float im = GML::lerp(a.im, b.im, t);
		return Complex(re, im);
	}
	Complex Complex::lerpUnclamped(const Complex& a, const Complex& b, float t) {
		float re = GML::lerp(a.re, b.re, t);
		float im = GML::lerp(a.im, b.im, t);
		return Complex(re, im);
	}

	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	void Complex::add(const Complex& z) {
		re += z.re;
		im += z.im;
	}
	void Complex::substract(const Complex& z) {
		re -= z.re;
		im -= z.im;
	}

	Complex Complex::add(const Complex& z, const Complex& w) {
		return Complex(z.re + w.re, z.im + w.im);
	}
	Complex Complex::substract(const Complex& z, const Complex& w) {
		return Complex(z.re - w.re, z.im - w.im);
	}

	// ==========================================================
	// ===================== Multiplication =====================
	// ==========================================================

	void Complex::multiply(const Complex& z) {
		float oldRe = re;
		float oldIm = im;
		re = oldRe * z.re - oldIm * z.im;
		im = oldRe * z.im + oldIm * z.re;
	}
	void Complex::divide(const Complex& z) {
		multiply(!z * (1 / (z.re * z.re + z.im * z.im)));
	}

	Complex Complex::multiply(const Complex& z, const Complex& w) {
		return Complex(z.re * w.re - z.im * w.im, z.re * w.im + z.im * w.re);
	}
	Complex Complex::divide(const Complex& z, const Complex& w) {
		float s = w.re * w.re + w.im * w.im;
		return Complex((z.re * w.re + z.im * w.im) / s, (z.im * w.re - z.re * w.im) / s);
	}

	// ==========================================================
	// ====================== Exponentials ======================
	// ==========================================================

	void Complex::pow(const Complex& z) {
		float r = getMagnitude();
		float a = getArgument();
		float mod = std::pow(r, z.re) * std::pow((float)M_E, -a * z.im);
		float angle = std::log(r) * z.im + a * z.re;
		re = mod * std::cos(angle);
		im = mod * std::sin(angle);
	}
	Complex Complex::pow(const Complex& z, const Complex& w) {
		float r = z.getMagnitude();
		float a = z.getArgument();
		float mod = std::pow(r, w.re) * std::pow((float)M_E, -a * w.im);
		float angle = std::log(r) * w.im + a * w.re;
		return Complex(mod * std::cos(angle), mod * std::sin(angle));
	}

	// TODO
	// ==========================================================
	// ======================= Logarithms =======================
	// ==========================================================


	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	Complex::operator Vec2f() const {
		return Vec2f(re, im);
	}

	std::ostream& operator<<(std::ostream& os, const Complex& z) {
		os << z.re;
		if (z.im >= 0)
			os << "+";
		os << z.im << "i";
		return os;
	}

	Complex operator+(const Complex& z, const Complex& w) {
		return Complex::add(z, w);
	}
	Complex operator-(const Complex& z, const Complex& w) {
		return Complex::substract(z, w);
	}
	Complex operator*(const Complex& z, const Complex& w) {
		return Complex::multiply(z, w);
	}
	Complex operator/(const Complex& z, const Complex& w) {
		return Complex::divide(z, w);
	}
	Complex operator^(const Complex& z, const Complex& w) {
		return Complex::pow(z, w);
	}

	void Complex::operator+=(const Complex& z) {
		add(z);
	}
	void Complex::operator-=(const Complex& z) {
		substract(z);
	}
	void Complex::operator*=(const Complex& z) {
		multiply(z);
	}
	void Complex::operator/=(const Complex& z) {
		divide(z);
	}

	bool operator==(const Complex& z, const Complex& w) {
		return (z.re == w.re && z.im == w.im);
	}
	bool operator!=(const Complex& z, const Complex& w) {
		return !(z.re == w.re && z.im == w.im);
	}

	// ==========================================================
	// ===================== /Complex class =====================
	// ==========================================================

}