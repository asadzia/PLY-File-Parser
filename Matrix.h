/*
* Created by: Asad Zia
* 
* Description:
* The basic matrix structure used in this project.
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <vector>
#include "Triangle.h"
#include "Colour.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// the matrix class shows the different computations done on the matrices in this program

class Matrix{
  
public:
  
// the function for finding the transpose
void transpose(double matrix[3][3],double Matrix[3][3]);

// the function for dividing the matrix elements by a scaler
void matrixScalerDivision(double scalar,double inputMatrix[3][3],double outputMatrix[3][3]);

// the function for viewing the contents of the matrix
void viewMatrix(double inv[3][3]);

// the function for the cofactor
double cofactorwithsign(double data[3][3],int x,int y);

// the function for finding the matrix determinant
double Determinant(double inputmatrix[3][3]);

// the function for multiplying the matrices	
void multiply(double first[3][3], double second[3][3],double output[3][3]);

// the function for finding the cofactor
void cofactor(double inputmatrix[3][3],double cofactormatrix [3][3]);

// the function for inverting the matrix
double** invert(double inputMatrix[3][3]);

// the function for finding the barycentric coordinates
Point getBarycentricPoints(double** Matrix , Point toCheck);

// checking if barycentric coordinate is inside the triangle
bool check(Point point);

// checking if point coordinates are inside the triangle
bool isPointInsideTriangle(Point toCheck , Triangle triangle);

// the function for scaling the RGB value
int scale(double value);

// the function for making the PPM image
void makePPM(Colour **ppmColour , string filename , int resolution);
};

#endif
