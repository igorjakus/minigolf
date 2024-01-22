////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_QUAT_H_
#define _GML_QUAT_H_

// Includes
#include <iostream>

namespace GML {

	// Forward declarations
	struct Vec3f;

	/////////////////////////////////////////////////////////////
	//
	// The Quaternion class.
	// Quaternions with real part (w) and imaginary part (x, y and z).
	// Every component is a float.
	//
	/////////////////////////////////////////////////////////////
	struct Quaternion {

		// ==========================================================
		// ====================== Member data =======================
		// ==========================================================

		// Real part of the quaternion.
		float w;

		// Imaginary ( i ) part of the quaternion.
		float x;

		// Imaginary ( j ) part of the quaternion.
		float y;

		// Imaginary ( k ) part of the quaternion.
		float z;

		// ==========================================================
		// ====================== Constructors ======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Construct a quaternion w + xi + yj + zk.
		// 
		// Parameters are set to 0 by default.
		// 
		// @param w - Real part of the complex number
		// @param x - Imaginary ( i ) part of the complex number
		// @param y - Imaginary ( j ) part of the complex number
		// @param z - Imaginary ( k ) part of the complex number
		// 
		/////////////////////////////////////////////////////////////
		Quaternion(float w = 0, float x = 0, float y = 0, float z = 0);

		/////////////////////////////////////////////////////////////
		// 
		// Copy constructor.
		// 
		/////////////////////////////////////////////////////////////
		Quaternion(const Quaternion&);

		// ==========================================================
		// ====================== Set methods =======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Set the complex number's component values.
		// 
		// @param w - New real part
		// @param x - New imaginary ( i ) part
		// @param y - New imaginary ( j ) part
		// @param z - New imaginary ( k ) part
		// 
		/////////////////////////////////////////////////////////////
		void set(float w, float x, float y, float z);

		/////////////////////////////////////////////////////////////
		// 
		// Copy values from another quaternion.
		// 
		/////////////////////////////////////////////////////////////
		void set(const Quaternion&);

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
		// std::string toString() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The absolute value of a quaternion
		// 
		/////////////////////////////////////////////////////////////
		float getMagnitude() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The absolute value of a quaternion squared
		// 
		/////////////////////////////////////////////////////////////
		float getMagnitudeSquared() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The magnitude of the imaginary part (x,y,z)
		// 
		/////////////////////////////////////////////////////////////
		float getUnrealMagnitude() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The magnitude of the imaginary part (x,y,z) squared
		// 
		/////////////////////////////////////////////////////////////
		float getUnrealMagnitudeSquared() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The conjugate of the quaternion
		// 
		/////////////////////////////////////////////////////////////
		Quaternion getConjugate() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The inverse of the quaternion
		// 
		/////////////////////////////////////////////////////////////
		Quaternion getInverse() const;

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
		// @return The normalized quaternion
		// 
		/////////////////////////////////////////////////////////////
		Quaternion normalized();

		/////////////////////////////////////////////////////////////
		// 
		// @return The normalized quaternion
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion normalize(const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Normalizes the imaginary part of the number.
		// 
		// Forces the imaginary magnitude to be equal to 1.
		// 
		/////////////////////////////////////////////////////////////
		void normalizeUnreal();

		/////////////////////////////////////////////////////////////
		// 
		// @return The imaginary-normalized quaternion
		// 
		/////////////////////////////////////////////////////////////
		Quaternion normalizedUnreal();

		/////////////////////////////////////////////////////////////
		// 
		// @return The imaginary-normalized quaternion
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion normalizeUnreal(const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Create a quaternion that corresponds to a rotation.
		// 
		// Note that in order to rotate a quaternion an inverse of this method result is also required.
		// 
		// The angle should be halved.
		// 
		// @param angle - The angle of rotation
		// @param axis - The axis of rotation
		// 
		// @return Normalized quaternion lying on a hypersphere
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion createRotation(float angle, const Vec3f& axis);

		// TODO
		// ==========================================================
		// ===================== Interpolations =====================
		// ==========================================================

		// ==========================================================
		// ======================== Addition ========================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Adds a given quaternion.
		// 
		/////////////////////////////////////////////////////////////
		void add(const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Substracts a given quaternion.
		// 
		/////////////////////////////////////////////////////////////
		void substract(const Quaternion&);
		
		/////////////////////////////////////////////////////////////
		// 
		// Adds two quaternions together
		// 
		// @return Sum of quaternions
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion add(const Quaternion&, const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Substracts two quaternions.
		// 
		// @return Difference of quaternions
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion substract(const Quaternion&, const Quaternion&);

		// ==========================================================
		// ===================== Multiplication =====================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Multiplies by a given quaternion.
		// 
		/////////////////////////////////////////////////////////////
		void multiply(const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Divides by a given quaternion.
		// 
		/////////////////////////////////////////////////////////////
		void divide(const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Multiplies two quaternions together.
		// 
		// @return Product of quaternions
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion multiply(const Quaternion&, const Quaternion&);

		/////////////////////////////////////////////////////////////
		// 
		// Divides two quaternions.
		// 
		// @return Quotient of quaternions
		// 
		/////////////////////////////////////////////////////////////
		static Quaternion divide(const Quaternion&, const Quaternion&);

		// ==========================================================
		// ======================= Operators ========================
		// ==========================================================

		void operator+=(const Quaternion&);
		void operator-=(const Quaternion&);
		void operator*=(const Quaternion&);
		void operator/=(const Quaternion&);

	};	// -------- End of class declaration --------

	// ==========================================================
	// =============== Operators outside of class ===============
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Quaternion&); // debug purpose operator

	Quaternion operator!(const Quaternion&); // conjugate operator
	Quaternion operator~(const Quaternion&); // inverse operator

	Quaternion operator+(const Quaternion&, const Quaternion&); // addition
	Quaternion operator-(const Quaternion&, const Quaternion&); // substraction

	Quaternion operator*(const Quaternion&, const Quaternion&); // multiplication
	Quaternion operator/(const Quaternion&, const Quaternion&); // division

	bool operator==(const Quaternion&, const Quaternion&); // equals operator
	bool operator!=(const Quaternion&, const Quaternion&); // not equals operator

}

#endif //_GML_QUAT_H_

