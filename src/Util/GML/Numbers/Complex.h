////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

//NOLINTBEGIN(bugprone-easily-swappable-parameters,readability-identifier-length)

#pragma once

#include <utility>
#ifndef _GML_COMP_H_
#define _GML_COMP_H_

// Includes
#include <iostream>

namespace GML {

// Forward declarations
struct Vec2f;
struct Mat2f;

/////////////////////////////////////////////////////////////
// 
// The Complex class.
// 
// Complex number with real part (re) and imaginary part (im).
// Both components are floats.
//
/////////////////////////////////////////////////////////////
struct Complex {

	// ==========================================================
	// ====================== Member data =======================
	// ==========================================================

	// Real part of the complex number.
	float re;

	// Imaginary part of the complex number.
	float im;

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Construct a complex number a + bi.
	// 
	// Parameters are set to 0 by default.
	// 
	// @param a - Real part of the complex number
	// @param b - Imaginary part of the complex number
	// 
	/////////////////////////////////////////////////////////////
	Complex(float a, float b);

	Complex();

	explicit Complex(std::pair<float, float>);

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Set the complex number's component values.
	// 
	// @param newre - New real part
	// @param newim - New imaginary part
	// 
	/////////////////////////////////////////////////////////////
	void set(float newre, float newim);

	/////////////////////////////////////////////////////////////
	// 
	// Copy values from another complex number.
	// 
	/////////////////////////////////////////////////////////////
	void set(const Complex&);

	// ==========================================================
	// ======================= Utilities ========================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// toString() method.
	// 
	// @return string representation of this object
	// 
	/////////////////////////////////////////////////////////////
	// [[nodiscard]] std::string toString() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return Vector representation of the object
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Vec2f toVec2f() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return Matrix representation of complex number as transform
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Mat2f toMat2f() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The modulus of a complex number (absolute value)
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float getMagnitude() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The modulus (absolute value) of a complex number squared
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float getMagnitudeSquared() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The argument of a complex number
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float getArgument() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The conjugate of the complex number
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Complex getConjugate() const;

	/////////////////////////////////////////////////////////////
	// 
	// Normalizes the number.
	// 
	// Forces the absolute value to be equal to 1.
	// 
	/////////////////////////////////////////////////////////////
	void normalize();

	/////////////////////////////////////////////////////////////
	// 
	// @return The normalized complex number
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Complex normalized() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The normalized complex number
	// 
	/////////////////////////////////////////////////////////////
	static Complex normalize(const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Create a complex number that corresponds to a rotation.
	// 
	// @param angle - The angle of rotation
	// 
	// @return Normalized complex number lying on a unit circle
	// 
	/////////////////////////////////////////////////////////////
	static Complex createRotation(float angle);

	// ==========================================================
	// ===================== Interpolations =====================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Lerp function for complex numbers.
	// 
	// Linearly interpolates between a and b by the clamped t parameter.
	// 
	// @param a - Start complex number
	// @param b - End complex number
	// @param t - interpolation parameter
	// 
	// @return Complex number linearly interpolated between a and b
	// 
	/////////////////////////////////////////////////////////////
	static Complex lerp(const Complex& a, const Complex& b, float t);

	/////////////////////////////////////////////////////////////
	// 
	// Lerp function for complex numbers with unclamped parameter.
	// 
	// Linearly interpolates between a and b by the t parameter.
	// 
	// @param a - Start complex number
	// @param b - End complex number
	// @param t - interpolation parameter
	// 
	// @return Complex number linearly interpolated between a and b
	// 
	/////////////////////////////////////////////////////////////
	static Complex lerpUnclamped(const Complex& a, const Complex& b, float t);

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// TODO: slerp ig
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////



	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Adds a given complex number.
	// 
	/////////////////////////////////////////////////////////////
	void add(const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Substracts a given complex number.
	// 
	/////////////////////////////////////////////////////////////
	void substract(const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Adds two complex numbers together.
	// 
	// @return Sum of complex numbers
	// 
	/////////////////////////////////////////////////////////////
	static Complex add(const Complex&, const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Substracts two complex numbers.
	// 
	// @return Difference of complex numbers
	// 
	/////////////////////////////////////////////////////////////
	static Complex substract(const Complex&, const Complex&);

	// ==========================================================
	// ===================== Multiplication =====================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Multiplies by a given complex number.
	// 
	/////////////////////////////////////////////////////////////
	void multiply(const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Divides by a given complex number.
	// 
	/////////////////////////////////////////////////////////////
	void divide(const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Multiplies two complex numbers together.
	// 
	// @return Product of complex numbers
	// 
	/////////////////////////////////////////////////////////////
	static Complex multiply(const Complex&, const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Divides two complex numbers.
	// 
	// @return Quotient of complex numbers
	// 
	/////////////////////////////////////////////////////////////
	static Complex divide(const Complex&, const Complex&);

	// ==========================================================
	// ====================== Exponentials ======================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Raises to the complex power.
	// 
	/////////////////////////////////////////////////////////////
	void pow(const Complex&);

	/////////////////////////////////////////////////////////////
	// 
	// Complex power function.
	// 
	// @param base - Base of the exponential
	// @param exp - Exponent of the exponential
	// 
	// @return Value of the exponential
	// 
	/////////////////////////////////////////////////////////////
	static Complex pow(const Complex& base, const Complex& exp);

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	// TODO: slerp ig
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	// TODO
	// ==========================================================
	// ======================= Logarithms =======================
	// ==========================================================



	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	explicit operator Vec2f() const;
	explicit operator float() const;
	void operator+=(const Complex&);
	void operator-=(const Complex&);
	void operator*=(const Complex&);
	void operator/=(const Complex&);

};	// -------- End of class declaration --------

// ==========================================================
// =============== Operators outside of class ===============
// ==========================================================

std::ostream& operator<<(std::ostream& os, const Complex&); // debug purpose operator

Complex operator!(const Complex&); // conjugate operator

Complex operator+(const Complex&, const Complex&); // addition
Complex operator+(const Complex&, float); // addition
Complex operator+(float, const Complex&); // addition
Complex operator-(const Complex&, const Complex&); // substraction
Complex operator-(const Complex&, float); // addition
Complex operator-(float, const Complex&); // addition
Complex operator*(const Complex&, const Complex&); // multiplication
Complex operator*(const Complex&, float); // addition
Complex operator*(float, const Complex&); // addition
Complex operator/(const Complex&, const Complex&); // division
Complex operator/(const Complex&, float); // addition
Complex operator/(float, const Complex&); // addition

Complex operator^(const Complex&, const Complex&); // exponentiation
Complex operator^(const Complex&, float); // exponentiation

bool operator==(const Complex&, const Complex&); // equals operator
bool operator!=(const Complex&, const Complex&); // not equals operator

}

#endif // _GML_COMP_H_

//NOLINTEND(bugprone-easily-swappable-parameters,readability-identifier-length)
