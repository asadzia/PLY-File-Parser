/*
* Created by: Asad Zia
* 
* Description:
* The file for the triangle class.
*/

#include "Triangle.h"

Triangle::Triangle(){}
  
Triangle::Triangle(Point x,Point y,Point z){
    
    this->x = x;
    this->y = y;
    this->z = z;
}
  
void Triangle::setX(Point x){
  this->x = x;
}
  
void Triangle::setY(Point y){
    this->y = y;
}
  
void Triangle::setZ(Point z){
    this->z = z;
}
  
Point Triangle::getX(){
   return x; 
}
  
Point Triangle::getY(){
   return y; 
}
  
Point Triangle::getZ(){
   return z; 
}
