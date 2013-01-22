#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "RGBCol.h"
#include "Coord.h"

using namespace std;

class Vector{
    private:
        Coord __begin, __end;
        RGBCol __col;
        
    public:
        Vector() :
            __begin(),
            __end(),
            __col() {};
        Vector(Coord begin, Coord end) :
            __begin(begin),
            __end(end),
            __col() {};
        Vector(Coord begin, Coord end, RGBCol col) :
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
        void setColour(const RGBCol& C) {
            __col = C;
        }
        Coord getBegin() {
            return __begin;
        }
        Coord getEnd() {
            return __end;
        }
        RGBCol getColour() {
            return __col;
        }
        
        string toString() {
            ostringstream strm;
            strm << "Vector begins at " << __begin.toString() << ", ends at " << __end.toString() << " with RGBCol colour = " << __col.toString();
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
    Matrix() {
        data[0][0]=0.0; data[0][1]=0.0; data[0][2]=0.0; data[0][3]=0.0;
        data[1][0]=0.0; data[1][1]=0.0; data[1][2]=0.0; data[1][3]=0.0;
        data[2][0]=0.0; data[2][1]=0.0; data[2][2]=0.0; data[2][3]=0.0;
        data[3][0]=0.0; data[3][1]=0.0; data[3][2]=0.0; data[3][3]=1.0;
    };
    Matrix operator*(const Matrix gMatrix) {
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
    };
    void print() {
        cout << "| " << data[0][0] << " " << data[0][1] << " " << data[0][2] << " " << data[0][3] << " |" << endl;
        cout << "| " << data[1][0] << " " << data[1][1] << " " << data[1][2] << " " << data[1][3] << " |" << endl;
        cout << "| " << data[2][0] << " " << data[2][1] << " " << data[2][2] << " " << data[2][3] << " |" << endl;
        cout << "| " << data[3][0] << " " << data[3][1] << " " << data[3][2] << " " << data[3][3] << " |" << endl;
        cout << endl;
    };
    
    void operator*(Coord& gCoord) {
        unsigned int i;
        double gCrd[4]; 
        
        gCrd[0] = gCoord.get_x();
        gCrd[1] = gCoord.get_y();
        gCrd[2] = gCoord.get_z();
        gCrd[3] = 1;
        
        //wymnazanie x
        double sum = 0.;
        for (i=0;i<4;i++) 
             sum += data[0][i] * gCrd[i];
        gCoord.set_x(sum);
        //wymnazanie y
        sum = 0.;
        for (i=0;i<4;i++) 
             sum += data[1][i] * gCrd[i];
        gCoord.set_y(sum);
        //wymnazanie z
        sum = 0.;
        for (i=0;i<4;i++) 
             sum += data[2][i] * gCrd[i];
        gCoord.set_z(sum);    
    };
};
#endif //_VECTOR_H_
