/*
* Created by: Asad Zia
* 
* Description:
* The implemetation of the matrix class.
*/

#include "Matrix.h"

  
void Matrix::transpose(double matrix[3][3],double Matrix[3][3])

{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            Matrix[i][j]=matrix[j][i];

}

void Matrix::matrixScalerDivision(double scalar,double input[3][3],double output[3][3])
{
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            output[i][j]=input[i][j]/scalar;

}

void Matrix::viewMatrix(double inv[3][3])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<"\t"<<inv[i][j];
        }
        cout<<"\n";
    }
}

double Matrix::cofactorwithsign(double data[3][3], int x, int y)
{
    double co;

    co   =
        data[(x + 1) % 3][(y + 1) % 3]
        * data[(x + 2) % 3][(y + 2) % 3]
        - data[(x + 1) % 3][(y + 2) % 3]
        * data[(x + 2) % 3][(y + 1) % 3];

    return co;
}

double Matrix::Determinant(double input[3][3])
{
    double determinant =0;
    for (int j=0; j<3 ; j++ )
    {
        determinant+= input[0][j]*cofactorwithsign(input,0,j);

    }
    return determinant;
}
	
void Matrix::multiply(double first[3][3], double second[3][3],double output[3][3])
{
    for (int i=0; i<3 ; i++ )
        for (int j=0; j<3 ; j++ )
        {
            double element=0;
            for (int l=0; l<3 ; l++ )
                element+=first[i][l]*second[l][j];
            output[i][j]=element;
        }
}

void Matrix::cofactor(double input[3][3],double cofactorMat[3][3])
{
    for (int i=0; i<3 ; i++ )
        for (int j=0; j<3 ; j++ )
            cofactorMat[i][j]= cofactorwithsign(input,i,j);
}


double** Matrix::invert(double input[3][3]){
        
	double adjointMatrix[3][3],cofactor1[3][3],inversedMatrix[3][3];
	
	double determinant = Determinant(input);
        cofactor(input,cofactor1);
        transpose(cofactor1,adjointMatrix);
        matrixScalerDivision(determinant,adjointMatrix,inversedMatrix);
	
	double** result;
	result = new double*[3];
	
	for(int i = 0 ; i < 3 ; i++){
	  result[i] = new double[3];
	  for(int j = 0 ; j < 3 ; j++){
	    result[i][j] = inversedMatrix[j][i];
	  }
	}
	
	return result;
}


Point Matrix::getBarycentricPoints(double** Matrix , Point toCheck)
	{
  
  double b1 = Matrix[0][0] * toCheck.getX() + Matrix[0][1] * toCheck.getY() + Matrix[0][2] * toCheck.getZ();
  double b2 = Matrix[1][0] * toCheck.getX() + Matrix[1][1] * toCheck.getY() + Matrix[1][2] * toCheck.getZ();
  double b3 = Matrix[2][0] * toCheck.getX() + Matrix[2][1] * toCheck.getY() + Matrix[2][2] * toCheck.getZ();
  
  for(int i = 0 ; i < 3 ; i++){
    delete[]Matrix[i];
  }
  delete[] Matrix;
  
  Point result(b1,b2,b3);
  
  return result;
}

bool Matrix::check(Point point){
  bool result = true;
  
  if(point.getX() <= 0 || point.getX() >= 1)
    result &= false;
  if(point.getY() <= 0 || point.getY() >= 1)
    result &= false;
  if(point.getZ() <= 0 || point.getZ() >= 1)
    result &= false;
  
  return result;
}

bool Matrix::isPointInsideTriangle(Point toCheck , Triangle triangle){
  double Matrix [3][3];
  
  Matrix[0][0] = triangle.getX().getX();
  Matrix[0][1] = triangle.getX().getY();
  Matrix[0][2] = triangle.getX().getZ();
  Matrix[1][0] = triangle.getY().getX();
  Matrix[1][1] = triangle.getY().getY();
  Matrix[1][2] = triangle.getY().getZ();
  Matrix[2][0] = triangle.getZ().getX();
  Matrix[2][1] = triangle.getZ().getY();
  Matrix[2][2] = triangle.getZ().getZ();
  
  double** inverted = invert(Matrix);
  
  return check(getBarycentricPoints(inverted , toCheck));
}

int Matrix::scale(double value){
  return (int)(value * 255);
}

void Matrix::makePPM(Colour **ppmColour , string filename , int resolution){   
    FILE *fp;
    int i,j;
    
    fp = fopen(filename.c_str(),"w");
    
    if(fp == NULL){
    return;
    }
    
    fprintf(fp,"%s\n%d %d\n%d\n","P3", resolution, resolution,255);

    for(int i = 0 ; i < resolution ; i++){
      for(int j = 0 ; j < resolution ; j++){
	         fprintf(fp,"%d %d %d  ", scale(ppmColour[i][j].getR()) , scale(ppmColour[i][j].getG()), scale(ppmColour[i][j].getB()));
      }
        fprintf(fp,"\n");
    }
    
   for(int i = 0 ; i < resolution ; i++){
      delete[]ppmColour[i] ;
    }

    delete[]ppmColour;
    
    fclose(fp);
}
