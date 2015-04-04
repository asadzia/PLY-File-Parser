/*
* Created by: Asad Zia
* 
* Description:
* The PLY parser header.
*/

#ifndef PARSEPLY_H
#define PARSEPLY_H

#include "Matrix.h"
#include "Point.h"
#include "Colour.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// the class for parsing the PLY file

class ParsePLY{
  
private:

  // the name of the PLY file
  string plyFile;

  // the total number of vertices
  int Vertices;

  // the total number of faces
  int Faces;

  // the vector of points from the PLY file
  vector<Point> points;

  // the index of the triangles from the PLY file
  vector<Point> Index;
  
public:
  
  // the constructor which sets the filename
  ParsePLY(string plyFile);

  // the function for parsing the PLY file
  void parse();
  
  // the function for getting the points from the file
  vector<Point> getPoints();

  // the function for getting the indexes
  vector<Point> getIndexes();
};

#endif
