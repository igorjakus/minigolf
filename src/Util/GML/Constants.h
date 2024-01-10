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

	constexpr double M_PI = 3.1415926535897932;
	constexpr double M_PI_2 = 1.5707963267948966;
	constexpr double M_PI_4 = 0.7853981633974483;
	constexpr double M_1_PI = 0.3183098861837906;

	constexpr double M_E = 2.7182818284590452;

}

#endif //_GML_CONST_H_