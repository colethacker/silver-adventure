#pragma once
#include <iostream>
#include "Pixel.h"
#include "Complex.h"

using namespace std;

class Fractal
{
private:
	Pixel** grid;
	unsigned int cols;
	unsigned int rows;
	unsigned int maxIter;
	char type;

	void makeJulia();
	void makeMandelbrotFractal();
	unsigned int determinePixelColour(Complex, Complex);
public:
	~Fractal();
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int, char);
	const Fractal& operator=(const Fractal&);
	Fractal& operator=(Fractal&&);

	friend void saveToPGM(const Fractal&, const char*);


};