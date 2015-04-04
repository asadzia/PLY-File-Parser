/*
* Created by: Asad Zia
* 
* Description:
* The header file for the colour class.
*/

#include <iostream>

using namespace std;

#ifndef COLOUR_H
#define COLOUR_H

class Colour{

private:
	//	the main attributes for the RGB cube
	double r;
	double g;
	double b;

public:

	// the default constructor of this class
	Colour();

	// the constructor for adding the RGB values
	Colour(double,double,double);

	// the setter for R
	void setR(double);

	// the setter for G
	void setG(double);

	// the setter for B
	void setB(double);

	// the getter for R
	double getR();

	// the getter for G
	double getG();

	// the getter for B
	double getB();
};

#endif
