/*
* Created by: Asad Zia
* 
* Description:
* The main file for implementing the PLY parsing and image retrieval.
*/

#include <iostream>
#include "Colour.h"
#include "ParsePLY.h"
#include "Point.h"
#include "Matrix.h"
#include "Triangle.h"
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// declaring an opject for carrying out matrix computations
Matrix matrixOps;

// this function is mainly responsible for finding the maximum length in a vector of points
double maxLength(vector<Point> points){
  
    double length = 0.0;
	
	for(int i = 0 ; i < points.size() ; i++){
	   double temp = sqrt(points.at(i).getX() * points.at(i).getX() + points.at(i).getY() * points.at(i).getY() + points.at(i).getZ() * points.at(i).getZ());
	   if(length < temp){
	     length = temp;
	   }
	}
  return length;
}

// the function returns the minimum vector of x, y and z points
Point findMin(vector<Point> points){

   double minX = 0.0;
    double minY = 0.0;
    double minZ = 0.0;

	minX = points.front().getX();
	minY = points.front().getY();
	minZ = points.front().getZ();
	
	for(int i = 0 ; i < points.size() ; i++){

	  if(minX > points.at(i).getX()){
	      minX = points.at(i).getX();
	  }

	  if(minY > points.at(i).getY()){
	      minY = points.at(i).getY();
	  }

	  if(minZ > points.at(i).getZ()){
	      minZ = points.at(i).getZ();
	  }
	}

	Point result(minX , minY , minZ);
	
  return result;
}

// find the maximum coordinate of a 3d point
double findMaxCoord(Point point){
  
    // taking absolute to ensure all coordinates are non-negative
  double x = abs(point.getX());
  double y = abs(point.getY());
  double z = abs(point.getZ());
  
  if(x > y){
    if(x > z){
      return x;
    }
    else{
     return z; 
    }
  }
  else{
   if(y > z){
     return y;
   }
   else{
    return z; 
   }
    
  }
}

// the function for translating the points to ensure none of the points are negative
vector<Point> translate(vector<Point> points , Point translate){

  double val = findMaxCoord(translate);
  
  for(int i = 0 ; i < points.size() ; i++){
    points.at(i).setX(points.at(i).getX() + val);
    points.at(i).setY(points.at(i).getY() + val);
    points.at(i).setZ(points.at(i).getZ() + val);
  }
  return points;
}

// the function for normlaizing the points which places them in a 1x1x1 cube
vector<Point> normalize(vector<Point> points , double length){
  
  for(int i = 0 ; i < points.size() ; i++){
    points.at(i).setX(points.at(i).getX() / length);
    points.at(i).setY(points.at(i).getY() / length);
    points.at(i).setZ(points.at(i).getZ() / length);
  }
  return points;
}

// the function for finding the difference between two points
Point pointDifference(Point one , Point two){
  
  Point result(one.getX() - two.getX() , one.getY() - two.getY() , one.getZ() - two.getZ());
 
  return result;
}

// the function for finding the cross-product
Point crossProduct(Point p1 , Point p2){
  
  double x = p1.getY() * p2.getZ() - p2.getY() * p1.getZ();
  double y = p1.getZ() * p2.getX() - p2.getZ() * p1.getX();
  double z = p1.getX() * p2.getY() - p2.getX() * p1.getY();
  
  Point result(x,y,z);
  
  return result;
}

// the function for finding the intersection point between traingle and ray
// Solve the equation: t = -(Po . N + d) / (V . N) and P = Po + tV
Point findIntersection(Point init , Point v , Triangle triangle){
  
  Point p1 = triangle.getX();
  Point p2 = triangle.getY();
  Point p3 = triangle.getZ();
  
  Point p12 = pointDifference(p1,p2);
  Point p13 = pointDifference(p1,p3);
    
  Point normal = crossProduct(p12 , p13);
  
  double t = (normal.getX() * p1.getX() + normal.getY() * p1.getY() + normal.getZ() * p1.getZ() - normal.getX() * init.getX() - normal.getY() * init.getY() - normal.getZ() * init.getZ())/(normal.getX()*v.getX() + normal.getY() * v.getY() + normal.getZ() * v.getZ());
  
  Point result( init.getX() + t * v.getX() , init.getY() + t * v.getY() , init.getZ() + t * v.getZ() ); 
  
  return result;
}

Colour getFirstIntersectionColour(Point viewPoint , Point pixelCenter , vector<Triangle> triangles){

  // find the difference between the viewpoint and pixel
  Point v = pointDifference(pixelCenter , viewPoint);

  // a boolean flag for confirming first intersection
  bool firstIntersecion = true;
  
  // a variable used for storing the first intersection triangle
  Triangle closestTriangle;

  // the variable used for comparing intersection points in the loop
  Point intersect = findIntersection(viewPoint , v , triangles.at(0));
  
  // loop for checking all traingles for intersection
  for(int i = 1 ; i < triangles.size() ; i++){
    
    Point temp = findIntersection(viewPoint , v , triangles.at(i));
     
    if(matrixOps.isPointInsideTriangle(temp , triangles.at(i))){
      if(firstIntersecion){
      	intersect = temp;
      	closestTriangle = triangles.at(i);
      	firstIntersecion = false;
      }else{
        	if(temp.getZ() < intersect.getZ()){
        	    intersect = temp;
        	    closestTriangle = triangles.at(i);
        	}
      }
    }
  }

  // after the first traingle is found in the loop, its normal is found
  // by using the cross-product function implemented earlier
  // the normal is then normalized as shown below:

  Point p1 = closestTriangle.getX();
  Point p2 = closestTriangle.getY();
  Point p3 = closestTriangle.getZ();

  Point p12 = pointDifference(p1,p2);
  Point p13 = pointDifference(p1,p3);
  Point normal = crossProduct(p12 , p13);

  double length = sqrt(normal.getX() * normal.getX() + normal.getY() * normal.getY() + normal.getZ() * normal.getZ());

    Point normal2(0,0,0);
    normal2.setX(normal.getX()/ length);
    normal2.setY(normal.getY() / length);
    normal2.setZ(normal.getZ() / length);
    
  
  if(!firstIntersecion){
    Colour result(abs(normal2.getX()) , abs(normal2.getY()) , abs(normal2.getZ()));
    return result;
  }
  else{
   Colour result(0,0,0);
   return result;
  }  
}

// the function for getting the triangles from the vector of points and indexes
// Source for making this function: http://www.mathworks.de/matlabcentral/fx_files/5459/1/content/ply.htm
vector<Triangle> getTriangles(vector<Point> points , vector<Point> triIndex){
  
  vector<Triangle> triangles;
  
  for(int i = 0 ; i < triIndex.size() ; i++){
    Triangle temp(points.at((int)triIndex.at(i).getX()) , points.at((int)triIndex.at(i).getY()) , points.at((int)triIndex.at(i).getZ()) );
    triangles.push_back(temp);
  }
  
  return triangles;
}

// the function for setting up the screen according to the resolution and then returning it
Point** InitScreen(int resolution){
  
  double minX = 0.0;
  double minY = 0.0;
  
  // initializing the screen
  Point **screen = new Point*[resolution];
  
  for(int i = 0 ; i < resolution ; i++){
    screen[i] = new Point[resolution];
  }
  
  double diffX = (1 - minX) / resolution;
  double diffY = (1 - minY) / resolution;
  
  double stepX = diffX;
  
  // set up the pixel coordinates 
  for(int i = 0 ; i < resolution ; i++){
    for(int j = 0 ; j < resolution ; j++){
	   
	Point temp(stepX ,minY , 0.0);
	screen[i][j] = temp;
	stepX += diffX;
    }
    minY += diffY;
    stepX = minX;
  }
  
  return screen;
}

void execute(string fileName , int resolution){
  
 ParsePLY parser(fileName);
 parser.parse();

 // storing the points and face data
 vector<Point> points = parser.getPoints();
 vector<Point> triangleIndexes = parser.getIndexes();
 
 // normalizing to keep image in 1x1x1 box
 points = translate(points , findMin(points));
 points = normalize(points , maxLength(points));

 // storing the coordinates from PLY file in a text file
 ofstream po;
 po.open("Points.txt");
 po << "All the coordinates read from the PLY file:\n\n" << endl;
 for (int i =0; i<points.size(); i++){
  po << points.at(i).getX() << "\t" << points.at(i).getY() << "\t" << points.at(i).getZ() <<"\n";
 }
 po.close();
 

 vector<Triangle> triangles = getTriangles(points , triangleIndexes);

 // storing the triangle coordinates in a text file
 ofstream fa;
 fa.open("TrianglePoints.txt");
  fa << "The coordinates of the triangle written as X, Y, Z for EACH of the triangles vertices:\n\n" << endl;
  for (int i = 0; i< triangleIndexes.size(); i++) {
    fa << i <<  " " << triangles.at(i).getX().getX() << " " << triangles.at(i).getX().getY() << " " << triangles.at(i).getX().getZ() << " -- " << triangles.at(i).getY().getX() << " " << triangles.at(i).getY().getY() << " " << triangles.at(i).getY().getZ() << " -- " << triangles.at(i).getZ().getX() << " " << triangles.at(i).getZ().getY() << " " << triangles.at(i).getZ().getZ(); 
    fa << "\n";
  }
  fa.close();
 
 // initialize a screen
 Point **screen = InitScreen(resolution);
 
 // choosing a viewpoint
 Point viewPoint(0.5,0.5,-5.0);

 // making a 2D array for choosing of each pixel on the screen
 Colour **ppmColours;

 ppmColours = new Colour*[resolution];

 for(int i = 0 ; i < resolution ; i++){
   ppmColours[i] = new Colour[resolution];
 }
 
 for(int i = 0 ; i < resolution ; i++){
   for(int j = 0 ; j < resolution ; j++){
     ppmColours[i][j] = getFirstIntersectionColour(viewPoint , screen[i][j] , triangles);
    }
    cout<< " -- Reading -- " << i << endl;
 }
 
  matrixOps.makePPM(ppmColours , "Bunny.ppm" ,resolution);
 
  for(int i = 0 ; i < resolution ; i++){
    delete[]screen[i] ;
  }
    delete[]screen;
 
}

// the main function
int main(int argc , char **argv){

  if(argc == 1){
    cout<<"USAGE: ./make filename [resolution]\n"<<"Default resolution -> 400 x 400 "<<endl;
    return 0;
  }

  string fileName;
  int resolution;
  
  if(argc == 2){
      fileName = argv[1];
      resolution = 400;
  }
  
  if(argc == 3){
      fileName = argv[1];
      istringstream ss(argv[2]);
      ss >> resolution;
  }
  
  // call the execute function is resolution provided
  execute(fileName , resolution);	
 
  return 0; 
}
