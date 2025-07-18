#pragma once

enum class FractalType
{
	MandelbrotFast = 0,
	MandelbrotDetailed = 1,
	JuliaFast = 2,
	JuliaDetailed = 3,
	SierpinskiCarpet = 4,
	SierpinskiTriangle = 5
};

constexpr char FractalTypeLabels[] =
	"Mandelbrot (Fast)\0"
	"Mandelbrot (Detailed)\0"
	"Julia (Fast)\0"
	"Julia (Detailed)\0"
	"Sierpinski Carpet\0"
	"Sierpinski Triangle\0\0";
