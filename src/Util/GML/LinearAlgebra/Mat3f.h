////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_MAT3F_H_
#define _GML_MAT3F_H_

// Includes
#include <iostream>

namespace GML {

	// Forward declarations
	struct Vec3f;
	struct Mat2f;

	/////////////////////////////////////////////////////////////
	// 
	// The Mat3f class.
	// 
	// 3x3 matrix with float components.
	//
	/////////////////////////////////////////////////////////////
	struct Mat3f {

		/////////////////////////////////////////////////////////////
		//
		//	| m00, m10, m20 |
		//	| m01, m11, m21 |
		//	| m02, m12, m22 |
		//
		/////////////////////////////////////////////////////////////
		float m00, m10, m20,
			  m01, m11, m21,
			  m02, m12, m22;

		// ==========================================================
		// ====================== Constructors ======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Construct a 3x3 matrix
		// 
		// Parameters are set to 0 by default.
		// 
		//	| m00, m10, m20 |
		//	| m01, m11, m21 |
		//	| m02, m12, m22 |
		// 
		/////////////////////////////////////////////////////////////
		Mat3f(float m00 = 0, float m10 = 0, float m20 = 0, float m01 = 0, float m11 = 0, float m21 = 0, float m02 = 0, float m12 = 0, float m22 = 0);

		/////////////////////////////////////////////////////////////
		// 
		// Copy constructor.
		// 
		/////////////////////////////////////////////////////////////
		Mat3f(const Mat3f&);

		/////////////////////////////////////////////////////////////
		// 
		// Construct a 3x3 matrix using basis vectors.
		// 
		// @param i - i hat vector
		// @param j - j hat vector
		// @param k - k hat vector
		// 
		/////////////////////////////////////////////////////////////
		Mat3f(const Vec3f& i, const Vec3f& j, const Vec3f& k);

		// ==========================================================
		// ====================== Set methods =======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Set the matrix's component values.
		// 
		/////////////////////////////////////////////////////////////
		void set(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12, float m22);

		/////////////////////////////////////////////////////////////
		// 
		// Copy values from another matrix.
		// 
		/////////////////////////////////////////////////////////////
		void set(const Mat3f&);

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
		std::string toString();

		/////////////////////////////////////////////////////////////
		// 
		// @return i hat component ([m00, m01, m02] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec3f getIHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return j hat component ([m10, m11, m12] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec3f getJHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return k hat component ([m20, m21, m22] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec3f getKHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return The determinant of the matrix
		// 
		/////////////////////////////////////////////////////////////
		float getDeterminant() const;

		/////////////////////////////////////////////////////////////
		// 
		// Inverts the matrix.
		// 
		/////////////////////////////////////////////////////////////
		void invert();

		/////////////////////////////////////////////////////////////
		// 
		// @param m - matrix to invert
		// 
		// @return Inverted matrix
		// 
		/////////////////////////////////////////////////////////////
		static Mat3f invert(const Mat3f&);

		/////////////////////////////////////////////////////////////
		// 
		// Transposes the matrix.
		// 
		/////////////////////////////////////////////////////////////
		void transpose();

		/////////////////////////////////////////////////////////////
		// 
		// @param m - matrix to transpose
		// 
		// @return Transposed matrix
		// 
		/////////////////////////////////////////////////////////////
		static Mat3f transpose(const Mat3f&);

		// ==========================================================
		// ================= Matrix multiplication ==================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Multiplies the matrix with a given matrix.
		// 
		// This matrix is considered to be the one being operated on
		// 
		// @param m - operating matrix
		// 
		/////////////////////////////////////////////////////////////
		void multiply(const Mat3f&);

		/////////////////////////////////////////////////////////////
		// 
		// Multiplies the matrices.
		// 
		// matrix A is considered to be on the left of B ( it's AxB )
		// 
		// @param A - second matrix (first from left)
		// @param B - first matrix (second from left)
		// 
		// @return Matrix product
		// 
		/////////////////////////////////////////////////////////////
		static Mat3f multiply(const Mat3f&, const Mat3f&);

		// ==========================================================
		// ======================= Operators ========================
		// ==========================================================

		explicit operator Mat2f() const;
		void operator*=(const Mat3f&);

	};	// -------- End of class declaration --------

	// ==========================================================
	// =============== Operators outside of class ===============
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Mat3f& m); // debug purpose operator

	Mat3f operator*(const Mat3f&, const Mat3f&); // matrix multiplication

	Mat3f operator!(const Mat3f&); // matrix inversion
	Mat3f operator~(const Mat3f&); // matrix transposition

	bool operator==(const Mat3f&, const Mat3f&); // equals operator
	bool operator!=(const Mat3f&, const Mat3f&); // not equals operator

}

#endif // _GML_MAT3F_H_