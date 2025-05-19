#pragma once

enum class FractalType
{
	MandelbrotFast = 0,
	MandelbrotDetailed = 1
};

constexpr char FractalTypeLabels[] =
	"Mandelbrot (Fast)\0"
	"Mandelbrot (Detailed)\0\0";
