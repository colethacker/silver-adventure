#include <iostream>
#include "Pixel.h"

Pixel::~Pixel() {}

Pixel::Pixel() : red(0), blue(0), green(0) {}

Pixel::Pixel(const Pixel& copied) : red(copied.red), green(copied.green), blue(copied.blue) {}

Pixel::Pixel(unsigned int red, unsigned int green, unsigned int blue) : red(red), green(green), blue(blue) {}

const unsigned int& Pixel::operator[](const char* colour)
{

	if (strcmp(colour, "red") == 0)
		return red;
	else if (strcmp(colour, "green") == 0)
		return green;
	else if (strcmp(colour, "blue") == 0)
		return blue;
	
	exit(1);
}


ofstream& operator<<(ofstream& input, Pixel& pix)
{// check function prototype for correctness
	// RGB output of one pixel class

	input << pix["red"] << " " << pix["green"] << " " << pix["blue"] << " ";

	return input;
}