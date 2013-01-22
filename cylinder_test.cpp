#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "Solid.h"
#include "Vector.h"

using namespace std;

Matrix RotateX(double ox){
    
    Matrix TmpX;
    
    TmpX.data[0][0] = 1;
    TmpX.data[1][1] = cos(ox);
    TmpX.data[1][2] = -sin(ox);
    TmpX.data[2][1] = sin(ox);
    TmpX.data[2][2] = cos(ox);
    
    return TmpX;
}
Matrix RotateY(double oy){
    
    Matrix TmpY;
    
    TmpY.data[0][0] = cos(oy);
    TmpY.data[0][2] = sin(oy);
    TmpY.data[2][0] = -sin(oy);
    TmpY.data[2][2] = cos(oy);
    TmpY.data[1][1] = 1;
    
    return TmpY;
}
Matrix RotateZ(double oz){
    
    Matrix TmpZ;
    
    TmpZ.data[0][0] = cos(oz);
    TmpZ.data[0][1] = -sin(oz);
    TmpZ.data[1][0] = sin(oz);
    TmpZ.data[1][1] = cos(oz);
    TmpZ.data[2][2] = 1;
    
    return TmpZ;
}

bool cylinder(Cylinder* cyl) {
    Coord bottom = cyl->getLowerRadixCenter();
    Coord top = cyl->getUpperRadixCenter();
    double r = cyl->getRadixRadius();
    int n = cyl->getLateralSurfaceDivision();
    double x_b, y_b, z_b;//wspolrzedne srodka podstawy dolnej
    double x_t, y_t, z_t;//wspolrzedne srodka podstawy górnej
    
    x_b = bottom.get_x();
    y_b = bottom.get_y();
    z_b = bottom.get_z();    
    x_t = top.get_x();
    y_t = top.get_y();
    z_t = top.get_z();
    //obliczanie wartosci katow
    double ox = 0, oy = 0, oz = 0;
    if((z_t-z_b) != 0 /*&& (y_t-y_b) != 0*/) ox = (atan((z_t-z_b)/(y_t-y_b)));
    else ox = 0.;
    if((z_t-z_b) != 0 /*&& (x_t-x_b) != 0*/) oy = (atan((x_t-x_b)/(z_t-z_b)));
    else oy = 0.;
    if((x_t-x_b) != 0 /*&& (y_t-y_b) != 0*/) oz = (atan((y_t-y_b)/(x_t-x_b)));
    else oz = 0.;
    //tworzymy tymczasawa, zwalniana na koncu, tablice dla wspolrzednych
    Coord* cArr = new Coord[2*n];
    //przemieszczenie, rotacja i odeslanie podstaw
    //przemieszczanie na srodek i wyliczanie punktow na okregu
    double rad = 2*M_PI / n;
	for(int i=1;i<=n;++i) {
		double crad = rad * (i-1);
		double new_x = cos(crad)*r;
		if(fabs(new_x) < 0.0000001) new_x = 0.;
		double new_z = sin(crad)*r;
		if(fabs(new_z) < 0.0000001) new_z = 0.;
		cArr[i-1] = Coord(new_x,0,new_z);
	}
	//rotacja
    for(int i=0;i<n;++i) {
        if(fabs(z_t-z_b) == 0) {
            RotateY(oy)*cArr[i];       
            RotateZ(-oz)*cArr[i];
        }
        else {      
            RotateX(ox)*cArr[i];
            RotateY(oy)*cArr[i]; 
        }
    }    
    //kopiowanie uzyskanych punktow na druga podstawe
    for(int i=0;i<n;++i) {
		cArr[n+i] = cArr[i];
	}    
    //odsylanie pierwszej podstawy
    for(int i=0;i<n;++i) {
		cArr[i].set_x(cArr[i].get_x()+x_b);
		cArr[i].set_y(cArr[i].get_y()+y_b);
		cArr[i].set_z(cArr[i].get_z()+z_b);
	}
    //odsylanie drugiej podstawy
    for(int i=n;i<(2*n);++i) {
		cArr[i].set_x(cArr[i].get_x()+x_t);
		cArr[i].set_y(cArr[i].get_y()+y_t);
		cArr[i].set_z(cArr[i].get_z()+z_t);
	}    
    //tworzenie wektorow
    //pierwsza podstawa
    for(int i=0;i<(n-1);++i) {
		cyl->getVecArr()[i]->setBegin(cArr[i]);
		cyl->getVecArr()[i]->setEnd(cArr[i+1]);
	}
		cyl->getVecArr()[n-1]->setBegin(cArr[n-1]);
		cyl->getVecArr()[n-1]->setEnd(cArr[0]);
    //druga podstawa
    for(int i=n;i<((2*n)-1);++i) {
		cyl->getVecArr()[i]->setBegin(cArr[i]);
		cyl->getVecArr()[i]->setEnd(cArr[i+1]);
	}
		cyl->getVecArr()[2*n-1]->setBegin(cArr[2*n-1]);
		cyl->getVecArr()[2*n-1]->setEnd(cArr[n]);
	//sciany boczne
	for(int i=0;i<(n-1);++i) {
		cyl->getVecArr()[2*n + i]->setBegin(cArr[i]);
		cyl->getVecArr()[2*n + i]->setEnd(cArr[n+i]);
	}
		cyl->getVecArr()[3*n-1]->setBegin(cArr[n-1]);
		cyl->getVecArr()[3*n-1]->setEnd(cArr[(2*n)-1]);
    //zwalnianie pamieci i return
    delete [] cArr;
    return true;
}

int main() {
    int n=20;	
	Cylinder* cyl = new Cylinder(1,RGB(0,0,0),Coord(0,0,0),Coord(1,1,1),0.5,n);
	cylinder(cyl);
	FILE* fp;
	fp = fopen("cylinder.geo", "w");
	for(int i=0;i<cyl->getSize();++i) {
		fprintf( fp, "%s", cyl->getVecArr()[i]->toFile().c_str() );
	}
	fclose(fp);
	delete cyl;
	system("pause");
    return 0;    
};
