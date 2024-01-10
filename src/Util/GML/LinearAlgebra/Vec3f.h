////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_VEC3F_H_
#define _GML_VEC3F_H_

// Includes
#include <iostream>

namespace GML {

	// Forward declarations
	struct Mat3f;
	struct Vec2f;

	/////////////////////////////////////////////////////////////
	// 
	// The Vec3f class.
	// 
	// Vector with two float components.
	//
	/////////////////////////////////////////////////////////////
	struct Vec3f {

		// ==========================================================
		// ====================== Member data =======================
		// ==========================================================

		float x;
		float y;
		float z;

		// ==========================================================
		// ====================== Constructors ======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Construct a vector [x, y, z]
		// 
		// Parameters are set to 0 by default.
		// 
		// @param x
		// @param y
		// @param z
		// 
		/////////////////////////////////////////////////////////////
		Vec3f(float x = 0, float y = 0, float z = 0);

		/////////////////////////////////////////////////////////////
		// 
		// Copy constructor.
		// 
		/////////////////////////////////////////////////////////////
		Vec3f(const Vec3f&);

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
		// 
		/////////////////////////////////////////////////////////////
		void set(float x, float y, float z);

		/////////////////////////////////////////////////////////////
		// 
		// Copy values from another vector.
		// 
		/////////////////////////////////////////////////////////////
		void set(const Vec3f&);

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
		Vec3f normalized();

		/////////////////////////////////////////////////////////////
		// 
		// @return The normalized vector
		// 
		/////////////////////////////////////////////////////////////
		static Vec3f normalize(const Vec3f&);

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
		static Vec3f lerp(const Vec3f& a, const Vec3f& b, float t);

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
		static Vec3f lerpUnclamped(const Vec3f& a, const Vec3f& b, float t);

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
		static Vec3f multiplyByScalar(const Vec3f&, const float);

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
		static Vec3f multiplyByScalar(const float, const Vec3f&);
		
		// ==========================================================
		// ======================== Addition ========================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Adds a given vector.
		// 
		/////////////////////////////////////////////////////////////
		void add(const Vec3f&);

		/////////////////////////////////////////////////////////////
		// 
		// Substracts a given vector.
		// 
		/////////////////////////////////////////////////////////////
		void substract(const Vec3f&);

		/////////////////////////////////////////////////////////////
		// 
		// Adds two vectors together.
		// 
		// @returns The sum of vectors
		// 
		/////////////////////////////////////////////////////////////
		static Vec3f add(const Vec3f&, const Vec3f&);

		/////////////////////////////////////////////////////////////
		// 
		// Substracts two vectors.
		// 
		// @returns The difference of vectors
		// 
		/////////////////////////////////////////////////////////////
		static Vec3f substract(const Vec3f&, const Vec3f&);

		// ==========================================================
		// ==================== Vector products =====================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// @returns The dot product between this vector and a given vector
		// 
		/////////////////////////////////////////////////////////////
		float dotProduct(const Vec3f&) const;

		/////////////////////////////////////////////////////////////
		// 
		// @returns The dot product between two vectors
		// 
		/////////////////////////////////////////////////////////////
		static float dotProduct(const Vec3f&, const Vec3f&);

		/////////////////////////////////////////////////////////////
		// 
		// @returns The cross product between this vector and a given vector
		// 
		/////////////////////////////////////////////////////////////
		Vec3f crossProduct(const Vec3f&) const;

		/////////////////////////////////////////////////////////////
		// 
		// @returns The cross product between two vectors
		// 
		/////////////////////////////////////////////////////////////
		static Vec3f crossProduct(const Vec3f&, const Vec3f&);

		// ==========================================================
		// ==================== Mat3f transform =====================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Transforms the vector using a given matrix.
		// 
		// @param m - the transformation matrix
		// 
		/////////////////////////////////////////////////////////////
		void transform(const Mat3f&);

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
		static Vec3f matrixMultiply(const Mat3f&, const Vec3f&);

		// ==========================================================
		// ======================= Operators ========================
		// ==========================================================

		explicit operator Vec2f() const;
		void operator*=(float);
		void operator/=(float);
		void operator+=(const Vec3f&);
		void operator-=(const Vec3f&);

	};	// -------- End of class declaration --------

	// ==========================================================
	// =============== Operators outside of class ===============
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Vec3f& v); // debug purpose operator

	Vec3f operator*(const float, const Vec3f&); // vector scaling
	Vec3f operator*(const Vec3f&, const float); // vector scaling

	Vec3f operator+(const Vec3f&, const Vec3f&); // vector addition
	Vec3f operator-(const Vec3f&, const Vec3f&); // vector substraction

	float operator*(const Vec3f&, const Vec3f&); // dot product
	Vec3f operator%(const Vec3f&, const Vec3f&); // cross product

	bool operator==(const Vec3f&, const Vec3f&); // equals operator
	bool operator!=(const Vec3f&, const Vec3f&); // not equals operator

	Vec3f operator*(const Mat3f&, const Vec3f&); // transform using matrix

}

#endif // _GML_VEC3F_H_