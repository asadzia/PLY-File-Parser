/*
* Created by: Asad Zia
* 
* Description:
* The implementation of the colour class.
*/

#include "Colour.h"

Colour::Colour(){
	r = 0.0;
	g = 0.0;
	b = 0.0;
}

Colour::Colour(double red, double green, double blue){
	r = red;
	g = green;
	b = blue;
}


void Colour::setR(double red){
	r = red;
};

void Colour::setG(double green){
	g = green;
};

void Colour::setB(double blue){
	b = blue;
};

double Colour::getR(){
	return r;
};

double Colour::getB(){
	return b;
};

double Colour::getG(){
	return g;
};
