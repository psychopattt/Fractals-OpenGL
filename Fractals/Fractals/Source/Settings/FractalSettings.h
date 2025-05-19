#pragma once

#include "Settings/FractalType.h"

namespace FractalSettings
{
	// Common
	inline FractalType ActiveFractal = FractalType::MandelbrotFast;

	// Mandelbrot (Common)
	inline unsigned int MaxIterations = 256;

	// Mandelbrot (Detailed)
	inline float LightAngle = 45;
	inline float LightHeight = 1.5f;

	inline float OddIterationsTint = 0;
	inline float EvenIterationsTint = 0;
}
