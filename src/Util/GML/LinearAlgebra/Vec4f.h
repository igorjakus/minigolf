////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_VEC4F_H_
#define _GML_VEC4F_H_

// Includes
#include <iostream>

namespace GML {

	// Forward declarations
	struct Mat4f;
	struct Vec3f;
	struct Vec2f;

	/////////////////////////////////////////////////////////////
	// 
	// The Vec4f class.
	// 
	// Vector with two float components.
	//
	/////////////////////////////////////////////////////////////
	struct Vec4f {

		// ==========================================================
		// ====================== Member data =======================
		// ==========================================================

		float x;
		float y;
		float z;
		float w;

		// ==========================================================
		// ====================== Constructors ======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Construct a vector [x, y, z, w]
		// 
		// Parameters are set to 0 by default.
		// 
		// @param x
		// @param y
		// @param z
		// @param w
		// 
		/////////////////////////////////////////////////////////////
		Vec4f(float x = 0, float y = 0, float z = 0, float w = 0);

		/////////////////////////////////////////////////////////////
		// 
		// Copy constructor.
		// 
		/////////////////////////////////////////////////////////////
		Vec4f(const Vec4f&);

		// ==========================================================
		// ====================== Set methods =======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Set the vector's component values.
		// 
		// @param x
		// @param y
		// @param z
		// @param w
		// 
		/////////////////////////////////////////////////////////////
		void set(float x, float y, float z, float w);

		/////////////////////////////////////////////////////////////
		// 
		// Copy values from another vector.
		// 
		/////////////////////////////////////////////////////////////
		void set(const Vec4f&);

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
		std::string toString() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The length of the vector
		// 
		/////////////////////////////////////////////////////////////
		float getLength() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The length of the vector squared
		// 
		/////////////////////////////////////////////////////////////
		float getLengthSquared() const;

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
		Vec4f normalized();

		/////////////////////////////////////////////////////////////
		// 
		// @return The normalized vector
		// 
		/////////////////////////////////////////////////////////////
		static Vec4f normalize(const Vec4f&);

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
		static Vec4f lerp(const Vec4f& a, const Vec4f& b, float t);

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
		static Vec4f lerpUnclamped(const Vec4f& a, const Vec4f& b, float t);

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
		void scale(const float);

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
		static Vec4f multiplyByScalar(const Vec4f&, const float);

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
		static Vec4f multiplyByScalar(const float, const Vec4f&);

		// ==========================================================
		// ======================== Addition ========================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Adds a given vector.
		// 
		/////////////////////////////////////////////////////////////
		void add(const Vec4f&);

		/////////////////////////////////////////////////////////////
		// 
		// Substracts a given vector.
		// 
		/////////////////////////////////////////////////////////////
		void substract(const Vec4f&);

		/////////////////////////////////////////////////////////////
		// 
		// Adds two vectors together.
		// 
		// @returns The sum of vectors
		// 
		/////////////////////////////////////////////////////////////
		static Vec4f add(const Vec4f&, const Vec4f&);

		/////////////////////////////////////////////////////////////
		// 
		// Substracts two vectors.
		// 
		// @returns The difference of vectors
		// 
		/////////////////////////////////////////////////////////////
		static Vec4f substract(const Vec4f&, const Vec4f&);

		// ==========================================================
		// ==================== Vector products =====================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// @returns The dot product between this vector and a given vector
		// 
		/////////////////////////////////////////////////////////////
		float dotProduct(const Vec4f&) const;

		/////////////////////////////////////////////////////////////
		// 
		// @returns The dot product between two vectors
		// 
		/////////////////////////////////////////////////////////////
		static float dotProduct(const Vec4f&, const Vec4f&);

		// ==========================================================
		// ==================== Mat4f transform =====================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Transforms the vector using a given matrix.
		// 
		// @param m - the transformation matrix
		// 
		/////////////////////////////////////////////////////////////
		void transform(const Mat4f&);

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
		static Vec4f matrixMultiply(const Mat4f&, const Vec4f&);

		// ==========================================================
		// ======================= Operators ========================
		// ==========================================================

		explicit operator Vec2f() const;
		explicit operator Vec3f() const;
		void operator*=(float);
		void operator/=(float);
		void operator+=(const Vec4f&);
		void operator-=(const Vec4f&);

	};	// -------- End of class declaration --------

	// ==========================================================
	// =============== Operators outside of class ===============
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Vec4f& v); // debug purpose operator

	Vec4f operator*(const float, const Vec4f&); // vector scaling
	Vec4f operator*(const Vec4f&, const float); // vector scaling

	Vec4f operator+(const Vec4f&, const Vec4f&); // vector addition
	Vec4f operator-(const Vec4f&, const Vec4f&); // vector substraction

	float operator*(const Vec4f&, const Vec4f&); // dot product

	bool operator==(const Vec4f&, const Vec4f&); // equals operator
	bool operator!=(const Vec4f&, const Vec4f&); // not equals operator

	Vec4f operator*(const Mat4f&, const Vec4f&); // transform using matrix

}

#endif // _GML_VEC4F_H_