#pragma once

#include "Settings/FractalType.h"

namespace FractalSettings
{
	// All
	inline FractalType ActiveFractal = FractalType::MandelbrotFast;

	// Mandelbrot (All) & Julia (All)
	inline unsigned int MaxIterations = 256;

	// Mandelbrot (Detailed) & Julia (Detailed)
	inline float LightAngle = 45;
	inline float LightHeight = 1.5f;
	inline float OddIterationsTint = 0;
	inline float EvenIterationsTint = 0;

	// Julia (All)
	inline constexpr double MaxConstant = 2;
	inline constexpr double MinConstant = -MaxConstant;
	inline double ConstantX = 0.285;
	inline double ConstantY = 0.01;
}
