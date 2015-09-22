//
// Copyright (c) 2015 Mahyar Khayatkhoei
// Copyright (c) 2009-2014 Shawn Singh, Glen Berseth, Mubbasir Kapadia, Petros Faloutsos, Glenn Reinman
// See license.txt for complete license.
//

#ifndef __UTIL_ANIMATION_CURVE_H__
#define __UTIL_ANIMATION_CURVE_H__

/// @file AnimationCurve.h
/// @brief Declares a helpful Util::Curve.

#include <iostream>
#include <vector>
#include <util/Geometry.h>
#include "Globals.h"

#ifdef _WIN32
// on win32, there is an unfortunate conflict between exporting symbols for a
// dynamic/shared library and STL code.  A good document describing the problem
// in detail is http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
// the "least evil" solution is just to simply ignore this warning.
#pragma warning( push )
#pragma warning( disable : 4251 )
#endif

namespace Util {

	/**
	* @brief Easy-to-use class for parsing command line arguments.
	*
	* This class allows you to specify the command line options that you expect to see when parsing a command line.
	* To use this class, simply specify each arg you want to parse using #addOption().
	*
	* This parser only initializes options that have a "flag" (i.e., usually starts with a hyphen "-" symbol) followed by
	* a specific number of "values" that follow.
	* If you want to allow "required args" that do not have an associated option flag, use the leftoverArgs parameter
	* from the #parse() function, which returns a list of args that were not recognized as options.
	*
	* Consider using Boost options parser if you need more elaborate functionality.
	*
	* <h3> How to use this class </h3>
	*
	* Simply call #addOption() for each option you would like to parse.  In this function, you describe: an
	* optional target variable you would like to be initialized (use NULL if there is no target), how many args
	* the option will consume, the target data type, and an optional secondary boolean target.
	*/
	class UTIL_API Curve
	{
	public:
		Curve(Point& startPoint) : start(startPoint) {};
		~Curve() {};
		void addControlPoint(Point& position, Point& tangent, Point& time);
		void drawCurve();
		bool getPoint(Point& outputPoint, float time);

	private:
		Point start;
		std::vector<Point> positions;
		std::vector<Point> tangents;
		std::vector<float> times;
	};

} // end namespace Util

#ifdef _WIN32
#pragma warning( pop )
#endif


#endif