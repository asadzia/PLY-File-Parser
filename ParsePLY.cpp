/*
* Created by: Asad Zia
* 
* Description:
* The implementation of the PLY parser.
*/

#include "ParsePLY.h"

 ParsePLY::ParsePLY(string plyFile){
    this->plyFile = plyFile;
    Vertices = 0;
    Faces = 0;
  }
  
  void ParsePLY::parse(){

   // constructing ifstream file_PLY object and opening the PLY file_PLY
   ifstream file_PLY(plyFile.c_str());
   
   // reading the file line by line
   for(string line; getline(file_PLY , line); ){

     if(line == "end_header"){
       break;
     }

     // finding the number of vertices and storing the value
     if(line.find("element") != string::npos){
       if(line.find("vertex") != string::npos){
           string buf(line.substr(line.rfind(" ") + 1));  // prints everything from " " to the end of the line
           stringstream ss(buf);
           ss >> Vertices;
       }
     }

     // finding the number of faces and storing the value
    if(line.find("element") != string::npos){
       if(line.find("face") != string::npos){
           string buf(line.substr(line.rfind(" ") + 1));
           stringstream ss(buf);
           ss >> Faces;
      }
     }
   }

    // the counter for counting the vertices in the loop
    int count = 0;

    // reading the coordinates from PLY file
    for(string line ;getline(file_PLY , line); ){
     
       istringstream ss(line);
   
       double valX;
       ss>>valX;
       double valY;
       ss>>valY;
       double valZ;
       ss>>valZ;
      
      // store all read coordinates in a vector
       Point storing(valX , valY , valZ);
       points.push_back(storing);
       
       count++;
       
       if(count == Vertices){
         break;
       }
       
    }
    
    // reinitialize count for faces and continue the same process as done for Vertices
    count = 0;
    
    for(string line ;getline(file_PLY , line); ){

     istringstream ss(line);
 
     int valX;
     ss>>valX;
     ss>>valX;
     int valY;
     ss>>valY;
     int valZ;
     ss>>valZ;
     
     Point storing(valX , valY , valZ);
     Index.push_back(storing);
     
     count++;
     
     if(count == Faces){
      break;
     }
     
    }
   
  }
  
  vector<Point> ParsePLY::getPoints(){
    return points;
  }
  
  vector<Point> ParsePLY::getIndexes(){
    return Index;
  }
