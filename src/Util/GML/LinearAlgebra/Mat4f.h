////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_MAT4F_H_
#define _GML_MAT4F_H_

// Includes
#include <iostream>

namespace GML {

	// Forward declarations
	struct Vec4f;
	struct Mat3f;
	struct Mat2f;

	/////////////////////////////////////////////////////////////
	// 
	// The Mat4f class.
	// 
	// 4x4 matrix with float components.
	//
	/////////////////////////////////////////////////////////////
	struct Mat4f {

		/////////////////////////////////////////////////////////////
		//
		//	| m00, m10, m20, m30 |
		//	| m01, m11, m21, m31 |
		//	| m02, m12, m22, m32 |
		//  | m03, m13, m23, m33 |
		//
		/////////////////////////////////////////////////////////////
		float m00, m10, m20, m30,
			  m01, m11, m21, m31,
			  m02, m12, m22, m32,
			  m03, m13, m23, m33;

		// ==========================================================
		// ====================== Constructors ======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Construct a 4x4 matrix
		// 
		// Parameters are set to 0 by default.
		// 
		//	| m00, m10, m20, m30 |
		//	| m01, m11, m21, m31 |
		//	| m02, m12, m22, m32 |
		//  | m03, m13, m23, m33 |
		// 
		/////////////////////////////////////////////////////////////
		Mat4f(float m00 = 0, float m10 = 0, float m20 = 0, float m30 = 0, float m01 = 0, float m11 = 0, float m21 = 0, float m31 = 0, float m02 = 0, float m12 = 0, float m22 = 0, float m32 = 0, float m03 = 0, float m13 = 0, float m23 = 0, float m33 = 0);

		/////////////////////////////////////////////////////////////
		// 
		// Copy constructor.
		// 
		/////////////////////////////////////////////////////////////
		Mat4f(const Mat4f&);

		/////////////////////////////////////////////////////////////
		// 
		// Construct a 3x3 matrix using basis vectors.
		// 
		// @param i - i hat vector
		// @param j - j hat vector
		// @param k - k hat vector
		// @param w - w hat vector
		// 
		/////////////////////////////////////////////////////////////
		Mat4f(const Vec4f& i, const Vec4f& j, const Vec4f& k, const Vec4f& w);

		// ==========================================================
		// ====================== Set methods =======================
		// ==========================================================

		/////////////////////////////////////////////////////////////
		// 
		// Set the matrix's component values.
		// 
		/////////////////////////////////////////////////////////////
		void set(float m00 = 0, float m10 = 0, float m20 = 0, float m30 = 0, float m01 = 0, float m11 = 0, float m21 = 0, float m31 = 0, float m02 = 0, float m12 = 0, float m22 = 0, float m32 = 0, float m03 = 0, float m13 = 0, float m23 = 0, float m33 = 0);

		/////////////////////////////////////////////////////////////
		// 
		// Copy values from another matrix.
		// 
		/////////////////////////////////////////////////////////////
		void set(const Mat4f&);

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
		// @return i hat component ([m00, m01, m02, m03] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec4f getIHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return j hat component ([m10, m11, m12, m13] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec4f getJHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return k hat component ([m20, m21, m22, m23] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec4f getKHat() const;

		/////////////////////////////////////////////////////////////
		// 
		// @return w hat component ([m30, m31, m32, m33] vector)
		// 
		/////////////////////////////////////////////////////////////
		Vec4f getWHat() const;

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
		static Mat4f invert(const Mat4f&);

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
		static Mat4f transpose(const Mat4f&);

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
		void multiply(const Mat4f&);

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
		static Mat4f multiply(const Mat4f&, const Mat4f&);

		// ==========================================================
		// ======================= Operators ========================
		// ==========================================================

		explicit operator Mat2f() const;
		explicit operator Mat3f() const;
		void operator*=(const Mat4f&);

	};	// -------- End of class declaration --------

	// ==========================================================
	// =============== Operators outside of class ===============
	// ==========================================================

	std::ostream& operator<<(std::ostream& os, const Mat4f& m); // debug purpose operator

	Mat4f operator*(const Mat4f&, const Mat4f&); // matrix multiplication

	Mat4f operator!(const Mat4f&); // matrix inversion
	Mat4f operator~(const Mat4f&); // matrix transposition

	bool operator==(const Mat4f&, const Mat4f&); // equals operator
	bool operator!=(const Mat4f&, const Mat4f&); // not equals operator

}

#endif // _GML_MAT4F_H_