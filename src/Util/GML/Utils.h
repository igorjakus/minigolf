////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// Utils.h
// 
// This header contains various functional utilites such as Lerp or Norm.
//
////////////////////////////////////////////////////////////

//NOLINTBEGIN(bugprone-easily-swappable-parameters)

#pragma once

#ifndef _GML_UTILS_H_
#define _GML_UTILS_H_

// Includes
#include "Constants.h"

namespace GML {

/////////////////////////////////////////////////////////////
// 
// Linear interpolation function.
// 
// @param startVal - Value returned when t = 0
// @param endVal - Value returned when t = 1
// @param param - Interpolation parameter
// 
// @return Linear interpolation between number a and b by the parameter t
//
/////////////////////////////////////////////////////////////
inline float lerp(float startVal, float endVal, float param) {
	return startVal + param * (endVal - startVal); 
}

/////////////////////////////////////////////////////////////
// 
// Linear interpolation function.
// 
// @param startVal - Value returned when t = 0
// @param endVal - Value returned when t = 1
// @param param - Interpolation parameter
// 
// @return Linear interpolation between number a and b by the parameter t
//
/////////////////////////////////////////////////////////////
inline double lerp(double startVal, double endVal, double param) {
	return startVal + param * (endVal - startVal); 
}

/////////////////////////////////////////////////////////////
// 
// Normalize function.
// 
// @param startVal - Lower end of spectrum
// @param endVal - Higher end of spectrum
// @param value - Normalized value
// 
// @return Parameter T normalized between a and b
//
/////////////////////////////////////////////////////////////
inline float norm(float startVal, float endVal, float value) {
	const float diff = endVal - startVal;
	if(diff == 0) [[unlikely]] {
		return 0;
	}
	return (value - startVal) / diff;
}

/////////////////////////////////////////////////////////////
// 
// Normalize function.
// 
// @param startVal - Lower end of spectrum
// @param endVal - Higher end of spectrum
// @param value - Normalized value
// 
// @return Parameter T normalized between a and b
//
/////////////////////////////////////////////////////////////
inline double norm(double startVal, double endVal, double value) {
	const double diff = endVal - startVal;
	if(diff == 0) [[unlikely]] {
		return 0;
	}
	return (value - startVal) / diff;
}

/////////////////////////////////////////////////////////////
// 
// Clamp function.
// 
// @param min - Minimal value
// @param max - Maximal value
// @param value - Clamped value
// 
// @return Value clamped between min and max
//
/////////////////////////////////////////////////////////////
inline float clamp(float min, float max, float value) {
	const float temp = value < min ? min : value;
	return temp > max ? max : temp;
}

/////////////////////////////////////////////////////////////
// 
// Clamp function.
// 
// @param min - Minimal value
// @param max - Maximal value
// @param value - Clamped value
// 
// @return Value clamped between min and max
//
/////////////////////////////////////////////////////////////
inline double clamp(double min, double max, double value) {
	const double temp = value < min ? min : value;
	return temp > max ? max : temp;
}

/////////////////////////////////////////////////////////////
// 
// Radians to degree conversion function.
// 
/////////////////////////////////////////////////////////////
inline float radToDeg(float rad) {
	return F_RAD_TO_DEG * rad;
}

/////////////////////////////////////////////////////////////
// 
// Radians to degree conversion function.
// 
/////////////////////////////////////////////////////////////
inline double radToDeg(double rad) {
	return D_RAD_TO_DEG * rad;
}

/////////////////////////////////////////////////////////////
// 
// Degree to radians conversion function.
// 
/////////////////////////////////////////////////////////////
inline float degToRad(float deg) {
	return F_DEG_TO_RAD * deg;
}

/////////////////////////////////////////////////////////////
// 
// Degree to radians conversion function.
// 
/////////////////////////////////////////////////////////////
inline double degToRad(double deg) {
	return D_DEG_TO_RAD * deg;
}

}

#endif //_GML_UTILS_H_

//NOLINTEND(bugprone-easily-swappable-parameters)
