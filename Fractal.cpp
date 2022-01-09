#include "Pixel.h"
#include "Complex.h"
#include "Fractal.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


Pixel convertToPixel(int colour)
{
	Pixel f((colour / 64) % 8,
				 (colour / 8) % 8,
				  colour % 8);
	return f;


}

Fractal::Fractal() : cols(0), rows(0), type(NULL),grid(nullptr) , maxIter(512)
{ 
	cout << "Default construtor" << endl; 
}

Fractal::Fractal(Fractal&& temp) : cols(temp.cols), rows(temp.rows), type(temp.type), maxIter(temp.maxIter)
{
	cout << "Move constructor called" << endl;

	grid = temp.grid;
	temp.grid = nullptr;
	temp.cols = 0;
	temp.rows = 0;
	temp.type = NULL;
	temp.maxIter = 0;
}



//copy constructor
Fractal::Fractal(const Fractal& copied) : cols(copied.cols), rows(copied.rows), type(copied.type), maxIter(copied.maxIter)
{
	cout << "Copy constructor" << endl;
	grid = new Pixel* [rows];

	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}

	if (type == 'j')
		cout << "making julia fractal" << endl;
	else if (type == 'm')
		cout << "making mandelbrot fractal" << endl;

	//use copy constructor for dynamic array somehow?
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			grid[i][j] = copied.grid[i][j];
		}
	}


}

Fractal::Fractal(unsigned int inputCol, unsigned int inputRow, char inputType) : cols(inputCol), rows(inputRow), type(inputType), maxIter(512)
{
	grid = new Pixel * [rows];

	for (unsigned int i = 0; i < rows; ++i)
		grid[i] = new Pixel[cols];


	cout << "3arg constructor" << endl;

	if (type == 'm')
		makeMandelbrotFractal();
	else if (type == 'j')
		makeJulia();
}

Fractal::~Fractal()
{
	cout << "Destructor called" << endl;
	
	for (unsigned int i = 0; i < rows; ++i)
	{
		delete[] grid[i];
	}
	delete[] grid;


}

const Fractal& Fractal::operator=(const Fractal& frac) 
{
	cout << "regular assignment operator" << endl;
	this->cols = frac.cols;
	this->rows = frac.rows;
	this->type = frac.type;

	for (unsigned int i = 0; i < rows; ++i)
	{
		delete[] grid[i];
	}
	delete[] grid;

	grid = new Pixel * [rows];

	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}


	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			grid[i] = frac.grid[i];
		}
	}
	return *this;
}

Fractal& Fractal::operator=(Fractal&& frac)
{
	cout << "Move assignment operator" << endl;
	if (this != &frac)
	{
		swap(this->grid, frac.grid);
		swap(this->cols, frac.cols);
		swap(this->rows, frac.rows);
		swap(this->maxIter, frac.maxIter);
		swap(this->type, frac.type);
	}
	return *this;

}

unsigned int Fractal::determinePixelColour(Complex Z, Complex C)
{
	double lengthMagnitudeSquared;
	unsigned int iter = 0;
	while(iter < maxIter)
	{
		iter = iter +1;
		Z = Z * Z;
		Z = Z + C;
		lengthMagnitudeSquared = getMagnitudeSquared(Z);
		if (lengthMagnitudeSquared > 4.0)
			return iter;
	}
	return this->maxIter;
}

void Fractal::makeMandelbrotFractal()
{

	
	cout << "Making mandelbrot fractal" << endl;
	Complex Z, C;

	double stepHeight = 4.0 / static_cast<double>(this->rows);
	double stepWidth = 4.0 / static_cast<double>(this->cols);

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			Z["imag"] = 0.0;
			Z["real"] = 0.0;
			C["real"] = (static_cast<double>(i) * stepHeight) - 2.0;
			C["imag"] = (static_cast<double>(j) * stepWidth) - 2.0;

			int colour = determinePixelColour(Z, C);
			this->grid[i][j] = convertToPixel(colour);

		}
	}
}

void Fractal::makeJulia()
{
	grid = new Pixel * [rows];

	for (unsigned int i = 0; i < rows; ++i)
	{
		grid[i] = new Pixel[cols];
	}
	cout << "Making julia fractal" << endl;
	Complex Z, C;

	double stepHeight = 4.0 / static_cast<double>(this->rows);
	double stepWidth = 4.0 / static_cast<double>(this->cols);

	for (unsigned int i = 0; i < this->rows; i++)
	{
		for (unsigned int j = 0; j < this->cols; j++)
		{
			Z["real"] = (static_cast<double>(i) * stepHeight) - 2.0;
			Z["imag"] = (static_cast<double>(j) * stepWidth) - 2.0;
			C["real"] = -0.8;
			C["imag"] = 0.156;

			int colour = determinePixelColour(Z, C);
			this->grid[i][j] = convertToPixel(colour);

		}
	}
}

void saveToPGM(const Fractal& frac, const char* name)
{
	ofstream output(name);
	output << "P3" << endl << "#" << endl << frac.cols << " " << frac.rows << endl << 7
		<< endl;

	for (unsigned int height = 0; height < frac.rows; height++)
	{
		for (unsigned int width = 0; width < frac.cols; width++)
		{
			output << frac.grid[height][width];

		}
		output << endl;
	}
	cout << "saving fractal to ASCII file" << endl;
	output.close();

}
