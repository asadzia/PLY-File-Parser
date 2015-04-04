/*
* Created by: Asad Zia
* 
* Description:
* The file for representing the 3D coordinates.
*/

#include "Point.h"

Point::Point(){
    
  }
  
  Point::Point(double x , double y , double z){
    this->x = x;
    this->y = y;
    this->z = z;
  }
  
  void Point::setX(double x){
    this->x = x;
  }
  
  void Point::setY(double y){
    this->y = y;
  }
  
  void Point::setZ(double z){
    this->z = z;
  }
  
  double Point::getX(){
    return x;
  }
  
  double Point::getY(){
    return y;
  }
  
  double Point::getZ(){
    return z;
  }
