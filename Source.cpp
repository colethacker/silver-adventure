#include <iostream>
#include <fstream>
#include "Complex.h"
#include "Fractal.h"
#include "Pixel.h"

Fractal testMoveConstructor(unsigned int columns, unsigned int rows, char c)
{
	Fractal f(columns, rows, c);
	return f;
}



int main()
{
	Fractal m1(768U, 1024U, 'm'), j1(768U, 1024U, 'j'), m2, j2;
	saveToPGM(m1, "mandelbrot.pgm");
	saveToPGM(j1, "julia.pgm");
	m2 = Fractal(m1);
	j2 = testMoveConstructor(600U, 800U, 'j');
	saveToPGM(j2, "julia_2.pgm");
	return 0;
}