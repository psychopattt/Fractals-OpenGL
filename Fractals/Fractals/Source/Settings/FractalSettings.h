#pragma once

#include "Settings/FractalType.h"

namespace FractalSettings
{
	// All
	inline FractalType ActiveFractal = FractalType::MandelbrotFast;

	// Mandelbrot (All) & Julia (All)
	inline unsigned int MaxIterations = 256;
	inline constexpr double MaxPosition = 4;
	inline constexpr double MinPosition = -MaxPosition;

	// Mandelbrot (Detailed) & Julia (Detailed)
	inline float LightAngle = 45;
	inline float LightHeight = 1.5f;
	inline float OddIterationsTint = 0;
	inline float EvenIterationsTint = 0;

	// Julia (All)
	inline double ConstantX = 0.285;
	inline double ConstantY = 0.01;

	// Sierpinski Triangle & Sierpinski Carpet
	inline unsigned int MaxDepth = 5;
	inline constexpr unsigned int DepthStep = 1;
	inline constexpr unsigned int DepthStepFast = 3;
	inline double GradientRepetition = 1;
	inline float GradientBrightness = 1;
	inline bool GradientInvert = false;

	// Sierpinski Triangle
	inline bool GradientAxis = true;
}
