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
#ifndef _GML_VEC2F_H_
#define _GML_VEC2F_H_

#include <iostream>

namespace GML {

// Forward declarations
struct Mat2f;
struct Vec3f;
struct Complex;

/////////////////////////////////////////////////////////////
// 
// The Vec2f class.
// 
// Vector with two float components.
//
/////////////////////////////////////////////////////////////
struct Vec2f {

	// ==========================================================
	// ====================== Member data =======================
	// ==========================================================

	float x;
	float y;

	// ==========================================================
	// ====================== Constructors ======================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Construct a vector [x, y]
	// 
	// Parameters are set to 0 by default.
	// 
	// @param x
	// @param y
	// 
	/////////////////////////////////////////////////////////////
	Vec2f(float xv, float yv);

	Vec2f();

	/////////////////////////////////////////////////////////////
	// 
	// Construct a vector [x, y] from std::pair (x, y)
	// 
	// @param values
	// 
	/////////////////////////////////////////////////////////////
	explicit Vec2f(std::pair<float, float>);

	// ==========================================================
	// ====================== Set methods =======================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Set the vector's component values.
	// 
	// @param newX
	// @param newY
	// 
	/////////////////////////////////////////////////////////////
	void set(float newX, float newY);

	/////////////////////////////////////////////////////////////
	// 
	// Copy values from another vector.
	// 
	/////////////////////////////////////////////////////////////
	void set(const Vec2f&);

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
	// @return Complex number representation of the vector
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Complex toComplex() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The length of the vector
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float getLength() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The length of the vector squared
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float getLengthSquared() const;

	/////////////////////////////////////////////////////////////
	// 
	// Normalizes the vector.
	// 
	// Forces the length 1.
	// 
	/////////////////////////////////////////////////////////////
	void normalize();

	/////////////////////////////////////////////////////////////
	// 
	// @return The normalized vector
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Vec2f normalized() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The normalized vector
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] static Vec2f normalize(const Vec2f&);

	// ==========================================================
	// ===================== Interpolations =====================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Lerp function for vectors.
	// 
	// Linearly interpolates between a and b by the clamped t parameter.
	// 
	// @param a - Start vector
	// @param b - End vector
	// @param t - interpolation parameter
	// 
	// @return Vector linearly interpolated between a and b
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f lerp(const Vec2f& a, const Vec2f& b, float t);

	/////////////////////////////////////////////////////////////
	// 
	// Lerp function for vectors with unclamped parameter.
	// 
	// Linearly interpolates between a and b by the t parameter.
	// 
	// @param a - Start vector
	// @param b - End vector
	// @param t - interpolation parameter
	// 
	// @return Vector linearly interpolated between a and b
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f lerpUnclamped(const Vec2f& a, const Vec2f& b, float t);

	// TODO: slerp ig

	// ==========================================================
	// ================ Multiplication by scalar ================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Scales the vector by given amount.
	// 
	// @param scale - scale factor
	// 
	/////////////////////////////////////////////////////////////
	void scale(float scale);

	/////////////////////////////////////////////////////////////
	// 
	// Scales the given vector by given amount.
	// 
	// @param vector - the vector to scale
	// @param scale - scale factor
	// 
	// @return Scaled vector
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f multiplyByScalar(const Vec2f& vector, float scale);

	/////////////////////////////////////////////////////////////
	// 
	// Scales the given vector by given amount.
	// 
	// @param scale - scale factor
	// @param vector - the vector to scale
	// 
	// @return Scaled vector
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f multiplyByScalar(float scale, const Vec2f& vector);

	// ==========================================================
	// ======================== Addition ========================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Adds a given vector.
	// 
	/////////////////////////////////////////////////////////////
	void add(const Vec2f&);

	/////////////////////////////////////////////////////////////
	// 
	// Substracts a given vector.
	// 
	/////////////////////////////////////////////////////////////
	void substract(const Vec2f&);

	/////////////////////////////////////////////////////////////
	// 
	// Adds two vectors together.
	// 
	// @returns The sum of vectors
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f add(const Vec2f&, const Vec2f&);

	/////////////////////////////////////////////////////////////
	// 
	// Substracts two vectors.
	// 
	// @returns The difference of vectors
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f substract(const Vec2f&, const Vec2f&);

	// ==========================================================
	// ==================== Vector products =====================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// @returns The dot product between this vector and a given vector
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float dotProduct(const Vec2f&) const;

	/////////////////////////////////////////////////////////////
	// 
	// @returns The dot product between two vectors
	// 
	/////////////////////////////////////////////////////////////
	static float dotProduct(const Vec2f&, const Vec2f&);

	/////////////////////////////////////////////////////////////
	// 
	// @returns The cross product between this vector and a given vector
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float crossProduct(const Vec2f&) const;

	/////////////////////////////////////////////////////////////
	// 
	// @returns The cross product between two vectors
	// 
	/////////////////////////////////////////////////////////////
	static float crossProduct(const Vec2f&, const Vec2f&);

	// ==========================================================
	// ==================== Mat2f transform =====================
	// ==========================================================

	/////////////////////////////////////////////////////////////
	// 
	// Transforms the vector using a given matrix.
	// 
	// @param m - the transformation matrix
	// 
	/////////////////////////////////////////////////////////////
	void transform(const Mat2f& m);

	/////////////////////////////////////////////////////////////
	// 
	// Transforms given vector using a matrix.
	// 
	// @param m - the transformation matrix
	// @param v - transformated vector
	// 
	// @return The transformation result
	// 
	/////////////////////////////////////////////////////////////
	static Vec2f matrixMultiply(const Mat2f& m, const Vec2f& v);

	// ==========================================================
	// ======================= Operators ========================
	// ==========================================================

	explicit operator Vec3f() const;
	void operator*=(float);
	void operator/=(float);
	void operator+=(const Vec2f&);
	void operator-=(const Vec2f&);

};	// -------- End of class declaration --------

// ==========================================================
// =============== Operators outside of class ===============
// ==========================================================

std::ostream& operator<<(std::ostream& os, const Vec2f& v); // debug purpose operator

Vec2f operator*(float, const Vec2f&); // vector scaling
Vec2f operator*(const Vec2f&, float); // vector scaling
Vec2f operator/(const Vec2f&, float); // vector scaling

Vec2f operator+(const Vec2f&, const Vec2f&); // vector addition
Vec2f operator-(const Vec2f&, const Vec2f&); // vector substraction

float operator*(const Vec2f&, const Vec2f&); // dot product
float operator%(const Vec2f&, const Vec2f&); // cross product

bool operator==(const Vec2f&, const Vec2f&); // equals operator
bool operator!=(const Vec2f&, const Vec2f&); // not equals operator

Vec2f operator*(const Mat2f&, const Vec2f&); // transform using matrix

}

//NOLINTEND(bugprone-easily-swappable-parameters,readability-identifier-length)

#endif // _GML_VEC2F_H_
