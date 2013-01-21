#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "Vector.h"

Matrix RotateMatrix(double ox, double oy, double oz){
    const double rad = 180./M_PI;
    
    ox = -ox / rad;
    oy = -oy / rad;
    oz = -oz / rad;
    
    Matrix TmpX, TmpY, TmpZ;
    
    TmpX.data[0][0] = 1;
    TmpX.data[1][1] = cos(ox);
    TmpX.data[1][2] = -sin(ox);
    TmpX.data[2][1] = sin(ox);
    TmpX.data[2][2] = cos(ox);
    
    TmpZ.data[0][0] = cos(oz);
    TmpZ.data[0][1] = -sin(oz);
    TmpZ.data[1][0] = sin(oz);
    TmpZ.data[1][1] = cos(oz);
    TmpZ.data[2][2] = 1;

    TmpY.data[0][0] = cos(oy);
    TmpY.data[0][2] = sin(oy);
    TmpY.data[2][0] = -sin(oy);
    TmpY.data[2][2] = cos(oy);
    TmpY.data[1][1] = 1;
    
    return ( TmpX*TmpY*TmpZ );
}

using namespace std;

bool line(Coord begin, Coord end, Vector** vecArr) {
	vecArr[0] = new Vector(begin,end);
	return true;
}

bool box(Coord begin, Coord end, Vector** vecArr) {
	int x1 = begin.get_x();
	int y1 = begin.get_y();
	int z1 = begin.get_z();
	int x2 = end.get_x();
	int y2 = end.get_y();
	int z2 = end.get_z();
	vecArr[0] = new Vector(begin,Coord(x2,y1,z1));
	vecArr[1] = new Vector(begin,Coord(x1,y2,z1));
	vecArr[2] = new Vector(Coord(x1,y2,z1),Coord(x2,y2,z1));
	vecArr[3] = new Vector(Coord(x2,y1,z1),Coord(x2,y2,z1));
	vecArr[4] = new Vector(begin,Coord(x1,y1,z2));
	vecArr[5] = new Vector(Coord(x1,y2,z1),Coord(x1,y2,z2));
	vecArr[6] = new Vector(Coord(x2,y2,z1),end);
	vecArr[7] = new Vector(Coord(x2,y1,z1),Coord(x2,y1,z2));
	vecArr[8] = new Vector(Coord(x1,y1,z2),Coord(x1,y2,z2));
	vecArr[9] = new Vector(Coord(x1,y1,z2),Coord(x2,y1,z2));
	vecArr[10] = new Vector(Coord(x1,y2,z2),end);
	vecArr[11] = new Vector(Coord(x2,y1,z2),end);
	return true;
}

bool sphere(Coord center, double r, int m, int n, Vector** vecArr) { 
	//m - poludniki n - rownolezniki
	int x = center.get_x();
	int y = center.get_y();
	int z = center.get_z();
	double spacing = 2.*r/(double)(n+1); // odleglosc miedzy rownoleznikami
	double rad = 2*M_PI / m; // odleglosc katowa miedzy poludnikami
	Coord* cArr = new Coord[m*n + 2];
	cArr[0] = Coord(x,(y+r),z);
	cArr[m*n + 1] = Coord(x,(y-r),z);
	for(int i=1;i<=n;++i) {
		double new_y = y+r - i*spacing;
		if(fabs(new_y) < 0.0000001) new_y = 0.;
		Coord tmp_center(x,new_y,z);
		double new_r = ((2*x + sqrt(3*pow(x,2) - pow((new_y-y),2) + pow(r,2)))) - x;
		if(fabs(new_r) < 0.0000001) new_r = 0.;
		for(int j=1;j<=m;++j) {
			double crad = rad * (j-1);
			double new_x = cos(crad)*new_r;
			if(fabs(new_x) < 0.0000001) new_x = 0.;
			double new_z = sin(crad)*new_r;
			if(fabs(new_z) < 0.0000001) new_z = 0.;
			cArr[(i-1)*m + j] = Coord(new_x,new_y,new_z);
		}
	}
	//towrzenie wektorow rownoleznikow
	int base = 0; //iteracja tablicy z wektorami
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			Coord begin = cArr[(i-1)*m + j];
			Coord end;
			if(j==m) {
				end = cArr[(i-1)*m + 1];
			}
			else {
			end = cArr[(i-1)*m + j + 1];
			}
			
			vecArr[base] = new Vector(begin,end);
			++base;
		}
	}
	//towrzenie wektorow poludnikow
	//najpierw wychodzace z czubkow	
	for(int j=1;j<=m;++j) {
		Coord begin = cArr[0];
		Coord end = cArr[j];
		
		vecArr[base] = new Vector(begin,end);
		++base;
	}
	for(int j=1;j<=m;++j) {
		Coord begin = cArr[m*n + 1];
		Coord end = cArr[(n-1)*m + j];
		
		vecArr[base] = new Vector(begin,end);
		++base;
	}
	//miedzy rownoleznikami
	for(int i=1;i<n;++i) {
		for(int j=1;j<=m;++j) {
			Coord begin = cArr[(i-1)*m + j];
			Coord end = cArr[i*m + j];
			
			vecArr[base] = new Vector(begin,end);
			++base;
		}
	}
	delete [] cArr;
	return true;
}

bool cone(Coord bottom, double br, Coord top, double tr, int n, Vector** vec){
	//srodek dolnej podstawy
	const double rad = 180./M_PI;//1 rad (alpha e [0; 359], ex: 45/rad = miara w radianach)
    double angle = 360./(double)n;//kat o jaki przesuwamy promieñ
    
    double x_b, y_b, z_b;//wspó³rzêdne œrodka podstawy dolnej
    double x_t, y_t, z_t;//wspó³rzêdne œrodka podstawy górnej
    
    x_b = bottom.get_x();
    y_b = bottom.get_y();
    z_b = bottom.get_z();
    
    x_t = top.get_x();
    y_t = top.get_y();
    z_t = top.get_z();
    
    double ox = 0, oy = 0, oz = 0;
    ox = x_t - x_b;
    oy = y_t - y_b;
    oz = z_t - z_b;
    //wektory do rysowania dolnej podstawy
    for( int i = 0; i < n; i++ ) {
        vec[i] = new Vector();
        vec[i]->setBegin( x_b + br*cos( (double)i*angle/rad ), y_b, z_b + br*sin( (double)i*angle/rad ) );
        vec[i]->setEnd( x_b + br*cos( (double)(i+1)*angle/rad ), y_b, z_b + br*sin( (double)(i+1)*angle/rad ) );
    }
    
    //wektory do rysowania górnej podstawy
    for( int i = n, j = 0; i < 2*n; i++, j++ ) {
        vec[i] = new Vector();
        vec[i]->setBegin( x_t + tr*cos( (double)j*angle/rad ), y_t, z_t + tr*sin( (double)j*angle/rad ) ); 
        vec[i]->setEnd( x_t + tr*cos( (double)(j+1)*angle/rad ), y_t, z_t + tr*sin( (double)(j+1)*angle/rad ) );
    }
    /////////////////////////////
    //translacja jeœli wymagana
    if(x_t!=x_b || z_t!=z_b){        
        Matrix cvRotation = RotateMatrix( ox, oy, oz );
        cvRotation.print();
        for(int i = 0; i < 2*n; i++) {
            vec[i] = cvRotation*vec[i];
        }
    }
    /////////////////////////////
    
    //wektory od podstawy dolnej do podstawy górnej
    for( int i = 2*n, b = 0, k = n; i < 3*n ; i++, b++, k++ ){
        vec[i] = new Vector();
        vec[i]->setBegin( vec[b]->getBegin().get_x(), vec[b]->getBegin().get_y(), vec[b]->getBegin().get_z() );
        vec[i]->setEnd( vec[k]->getBegin().get_x(), vec[k]->getBegin().get_y(), vec[k]->getBegin().get_z() );
    }
};

int main() {
	Vector** vec = new Vector*[40];
	ofstream out("cone.geo");
	//cout << "main" << endl;
	int div = 10;
	//cout << "div: " << div << endl;
	cone(Coord(1,0,-2),1.5,Coord(-1,1,2),1.0,div,vec);
	//cout << "main" << endl;
	for(int i = 0; i < div*3; ++i){
		out << vec[i]->toFile() << endl ;
	}
	out.close();
	//cout << "main" << endl;
    delete [] vec;
    //cout << "main" << endl;
    system("pause");
    return 0;    
};
