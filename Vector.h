#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "RGB.h"
#include "Coord.h"

using namespace std;

class Vector{
    private:
        Coord __begin, __end;
        RGB __col;
        
    public:
        Vector() :
            __begin(),
            __end(),
            __col() {};
        Vector(Coord begin, Coord end) :
            __begin(begin),
            __end(end),
            __col() {};
        Vector(Coord begin, Coord end, RGB col) :
            __begin(begin),
            __end(end),
            __col(col) {};
        ~Vector(){};
        
        void setBegin(double x, double y, double z) {
            __begin = Coord(x,y,z);
        }
        void setBegin(const Coord& C) {
            __begin = C;
        }
        void setEnd(double x, double y, double z) {
            __end = Coord(x,y,z);
        }
        void setEnd(const Coord& C) {
            __end = C;
        }
        void setColour(int R, int G, int B) {
            __col = RGB(R,G,B);
        }
        void setColour(const RGB& C) {
            __col = C;
        }
        Coord getBegin() {
            return __begin;
        }
        Coord getEnd() {
            return __end;
        }
        RGB getColour() {
            return __col;
        }
        
        string toString() {
            ostringstream strm;
            strm << "Vector begins at " << __begin.toString() << ", ends at " << __end.toString() << " with RGB colour = " << __col.toString();
            return strm.str();
        }
        
        string toFile() {
            ostringstream strm;
            strm << __begin.get_x() << " " << __begin.get_y() << " " << __begin.get_z() << " "
                 << __end.get_x() << " " << __end.get_y() << " " << __end.get_z() << " "
                 << __col.get_r() << " " << __col.get_g() << " " << __col.get_b() << endl;
            return strm.str();
        }
        
};

class Matrix
{
 public:
    double data[4][4];
    
 public:
    Matrix();
    Matrix operator*(const Matrix);
    void print();
    
    friend Vector operator*(const Matrix,const Vector);
};

Matrix::Matrix()
{
 data[0][0]=0.0; data[0][1]=0.0; data[0][2]=0.0; data[0][3]=0.0;
 data[1][0]=0.0; data[1][1]=0.0; data[1][2]=0.0; data[1][3]=0.0;
 data[2][0]=0.0; data[2][1]=0.0; data[2][2]=0.0; data[2][3]=0.0;
 data[3][0]=0.0; data[3][1]=0.0; data[3][2]=0.0; data[3][3]=1.0;
}


Matrix Matrix::operator* (const Matrix gMatrix)
{
 int i,j,k;
 Matrix tmp;

 for (i=0;i<4;i++)
    for (j=0;j<4;j++)
     {
      tmp.data[i][j]=0.0;
      for (k=0;k<4;k++)
       tmp.data[i][j]=tmp.data[i][j]+(data[i][k]*gMatrix.data[k][j]);
     }
 return tmp;
}

Vector* operator*(Matrix gMatrix, Vector* gVector) {
 unsigned int i,j;
 Vector* tmp = new Vector();

 double begin[4];
 double end[4];
 double gVec[4]; 
 
 gVec[0] = gVector->getBegin().get_x();
 gVec[1] = gVector->getBegin().get_y();
 gVec[2] = gVector->getBegin().get_z();
 gVec[3] = 1;
 
 
for( i = 0; i < 4; i++ ) {//begin
    begin[i] = 0.0;
   for (j=0;j<4;j++) 
         begin[i] += gMatrix.data[i][j] * gVec[i]; ;
}

 gVec[0] = gVector->getEnd().get_x();
 gVec[1] = gVector->getEnd().get_y();
 gVec[2] = gVector->getEnd().get_z();
 gVec[3] = 1;
 
for( i = 0; i < 4; i++ ) {//end
    end[i] = 0.0;
   for (j=0;j<4;j++) 
         end[i] += gMatrix.data[i][j] * gVec[i];
} 

    tmp->setBegin( begin[0], begin[1], begin[2] );
    tmp->setEnd( end[0], end[1], end[2] );
 return tmp;
}

void Matrix::print(void)
{
 cout << "| " << data[0][0] << " " << data[0][1] << " " << data[0][2] << " " << data[0][3] << " |" << endl;
 cout << "| " << data[1][0] << " " << data[1][1] << " " << data[1][2] << " " << data[1][3] << " |" << endl;
 cout << "| " << data[2][0] << " " << data[2][1] << " " << data[2][2] << " " << data[2][3] << " |" << endl;
 cout << "| " << data[3][0] << " " << data[3][1] << " " << data[3][2] << " " << data[3][3] << " |" << endl;
 cout << endl;
}
#endif //_VECTOR_H_
