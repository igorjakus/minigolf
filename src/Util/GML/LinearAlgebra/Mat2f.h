////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_MAT2F_H_
#define _GML_MAT2F_H_

// Includes
#include <iostream>

namespace GML {

	// Forward declarations
	struct Vec2f;
	struct Mat3f;
	struct Complex;

	/////////////////////////////////////////////////////////////
	// 
	// The Mat2f class.
	// 
	// 2x2 matrix with float components.
	//
	/////////////////////////////////////////////////////////////
	struct Mat2f {

		// ==========================================================
		// ====================== Member data =======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		//
		// | m00  m10 |
		// | m01  m11 |
		//
		/////////////////////////////////////////////////////////////
		float m00, m01, m10, m11;

		// ==========================================================
		// ====================== Constructors ======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Construct a 2x2 matrix
		// 
		// Parameters are set to 0 by default.
		// 
		// | m00  m10 |
		// | m01  m11 |
		// 
		/////////////////////////////////////////////////////////////
		Mat2f(float m00 = 1, float m10 = 0, float m01 = 0, float m11 = 1);

		/////////////////////////////////////////////////////////////
		// 
		// Copy constructor.
		// 
		/////////////////////////////////////////////////////////////
		Mat2f(const Mat2f&);

		/////////////////////////////////////////////////////////////
		// 
		// Construct a 2x2 matrix using basis vectors.
		// 
		// @param i - i hat vector
		// @param j - j hat vector
		// 
		/////////////////////////////////////////////////////////////
		Mat2f(const Vec2f& i, const Vec2f& j);

		// ==========================================================
		// ====================== Set methods =======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Set the matrix's component values.
		// 
		// @param m00
		// @param m10
		// @param m01
		// @param m11
		// 
		/////////////////////////////////////////////////////////////
		void set(float m00, float m10, float m01, float m11);

		/////////////////////////////////////////////////////////////
		// 
		// Copy values from another matrix.
		// 
		/////////////////////////////////////////////////////////////
		void set(const Mat2f&);

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
		// @return i hat component ([m00, m01] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec2f getIHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return j hat component ([m10, m11] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec2f getJHat() const;

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
		static Mat2f invert(const Mat2f&);

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
		static Mat2f transpose(const Mat2f&);

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
		void multiply(const Mat2f& m);

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
		static Mat2f multiply(const Mat2f& A, const Mat2f& B);

		// ==========================================================
		// ======================= Operators ========================
		// ==========================================================

		explicit operator Mat3f() const;
		void operator*=(const Mat2f&);

	};	// -------- End of class declaration --------

	// ==========================================================
	// =============== Operators outside of class ===============
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Mat2f& m); // debug purpose operator

	Mat2f operator*(const Mat2f&, const Mat2f&); // matrix multiplication

	Mat2f operator!(const Mat2f&); // matrix inversion
	Mat2f operator~(const Mat2f&); // matrix transposition

	bool operator==(const Mat2f&, const Mat2f&); // equals operator
	bool operator!=(const Mat2f&, const Mat2f&); // not equals operator

}

#endif // _GML_MAT2F_H_