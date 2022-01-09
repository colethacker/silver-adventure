#include "Complex.h"
#include <iostream>
#include <cmath>

using namespace std;

//definitions to follow
//looks complete check again l8r
Complex::Complex() :real(0.0), imag(0.0) {}
Complex::Complex(const Complex& copied) : real(copied.real), imag(copied.imag)	{}
Complex::Complex(double real, double imag): real(real), imag(imag) { }
Complex::~Complex() {}

double& Complex::operator[](const char* field)
{
	if (!strcmp(field, "real"))
		return this->real;
	else if (!strcmp(field, "imag"))
		return this->imag;
	else
		exit(1);
}

const Complex operator*(const Complex& a, const Complex& b)
{	// returns complex multiplication creal = areal * breal - aimag * bimag
	//cimag = areal * breal + aimag * breal
	return Complex((a.real * b.real) - (a.imag * b.imag),
				   (a.real * b.imag) + (a.imag * b.real));
}
const Complex operator+(const Complex& a, const Complex& b)
{ //return complex addition creal = areal + breal
  // cimag = aimag + bimag
	return Complex(a.real + b.real,
					a.imag + b.imag);
}

double getMagnitudeSquared(const Complex& c)
{// not sure if this is different for complex numbers?????

	return (c.real * c.real) + (c.imag * c.imag);
}