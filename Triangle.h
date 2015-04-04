/*
* Created by: Asad Zia
* 
* Description:
* The header file for the triangle class.
*/

#include <iostream>
#include "Point.h"

using namespace std;

#ifndef TRIANGLE_H
#define TRIANGLE_H

// the triangles class which holds a triangle with 3 points

class Triangle{
  
private:
  
  // the three 3-dimensional coordinates of a triangle
  Point x;
  Point y;
  Point z;
  
public:
  
  // the default constructor for triangle
  Triangle();

  // the constructor for setting the coordinates of the triangle
  Triangle(Point x,Point y,Point z);
  
  // the setter for the x-cooridinate
  void setX(Point x);
  
  // the setter for the y-coordinate
  void setY(Point y);
  
  // the setter for the z-coordinate
  void setZ(Point z);
  
  // the getter for the x-coordinate
  Point getX();

  // the getter for the y-coordinate
  Point getY();

  // the getter for the z-coordinate
  Point getZ();
};

#endif
