////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

//NOLINTBEGIN(bugprone-easily-swappable-parameters,readability-identifier-length)

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
	float m00, m10, m01, m11;

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
	Mat2f(float v00, float v10, float v01, float v11);

	Mat2f();

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
	// @param newm00
	// @param newm10
	// @param newm01
	// @param newm11
	// 
	/////////////////////////////////////////////////////////////
	void set(float newm00, float newm10, float newm01, float newm11);

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
	// [[nodiscard]] std::string toString() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return i hat component ([m00, m01] vector)
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Vec2f getIHat() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return j hat component ([m10, m11] vector)
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] Vec2f getJHat() const;

	/////////////////////////////////////////////////////////////
	// 
	// @return The determinant of the matrix
	// 
	/////////////////////////////////////////////////////////////
	[[nodiscard]] float getDeterminant() const;

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
	// @param A - operating matrix
	// 
	/////////////////////////////////////////////////////////////
	void multiply(const Mat2f& A);

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

std::ostream& operator<<(std::ostream& os, const Mat2f& A); // debug purpose operator

Mat2f operator*(const Mat2f&, const Mat2f&); // matrix multiplication

Mat2f operator!(const Mat2f&); // matrix inversion
Mat2f operator~(const Mat2f&); // matrix transposition

bool operator==(const Mat2f&, const Mat2f&); // equals operator
bool operator!=(const Mat2f&, const Mat2f&); // not equals operator

}

#endif // _GML_MAT2F_H_

//NOLINTEND(bugprone-easily-swappable-parameters,readability-identifier-length)
