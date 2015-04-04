/*
* Created by: Asad Zia
* 
* Description:
* The header file for the 3D coordinates.
*/

using namespace std;

#ifndef POINT_H
#define POINT_H

// This class mainly represents a point with x,y,z coordinates

class Point{
  
private:

  // the coordinates of the Point
  double x;
  double y;
  double z;
  
public:
  
  // the default constructor of this class
  Point();

  // the constructor for setting the values of x,y,z
  Point(double x , double y , double z);
  
  // the setter for x
  void setX(double x);

  // the setter for y
  void setY(double y);
  
  // the setter for z
  void setZ(double z);

  // thegetter for x
  double getX();

  // the getter for y
  double getY();

  // the getter for z
  double getZ();
};

#endif
