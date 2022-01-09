#pragma once
class Complex
{
private:
	double imag;
	double real;
public:
	Complex();
	~Complex();
	Complex(const Complex&);
	Complex(double, double);
	double& operator[](const char*);

	friend const Complex operator*(const Complex&, const Complex&);
	friend const Complex operator+(const Complex&, const Complex&);
	friend double getMagnitudeSquared(const Complex&);


};