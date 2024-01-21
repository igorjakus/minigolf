////////////////////////////////////////////////////////////
//
// GML - GoscZnickiem Math Library
// 
// Copyright (C) 2023 Maciej Zgierski.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// Constants.h
// 
// This header contains various mathematical constants.
// All constants are contained in GML namespace. In order
// to access them, please use GML::M_(name).
// For example:
// GML::M_PI = 3.1415...
// 
// "using namespace GML" is not recommended.
// Use "using GML::M_PI" instead.
//
////////////////////////////////////////////////////////////

#pragma once

#ifndef _GML_CONST_H_
#define _GML_CONST_H_

namespace GML {

// float precision constants:

constexpr float F_PI = 3.1415926535897932f;
constexpr float F_PI_2 = 1.5707963267948966f;
constexpr float F_PI_4 = 0.7853981633974483f;
constexpr float F_1_PI = 0.3183098861837906f;
constexpr float F_2_PI = 6.2831853071795864f;

constexpr float F_E = 2.7182818284590452f;

constexpr float F_DEG_TO_RAD = F_PI / 180.f; 
constexpr float F_RAD_TO_DEG = 180.f / F_PI; 

// double precision constants:

constexpr double D_PI = 3.14159265358979323;
constexpr double D_PI_2 = 1.57079632679489661;
constexpr double D_PI_4 = 0.78539816339744830;
constexpr double D_1_PI = 0.31830988618379067;
constexpr double D_2_PI = 6.28318530717958646;

constexpr double D_E = 2.71828182845904523;

constexpr double D_DEG_TO_RAD = 1.0; 
constexpr double D_RAD_TO_DEG = 1.0; 

}

#endif //_GML_CONST_H_
