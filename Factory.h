#ifndef _FACTORY_
#define _FACTORY_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "Solid.h"

using namespace std;

bool box(Box* bo) {
	Coord begin = bo->getStart();
	Coord end = bo->getEnd();
	double x1 = begin.get_x();
	double y1 = begin.get_y();
	double z1 = begin.get_z();
	double x2 = end.get_x();
	double y2 = end.get_y();
	double z2 = end.get_z();
	bo->getVecArr()[0] = new Vector(begin,Coord(x2,y1,z1));
	bo->getVecArr()[1] = new Vector(begin,Coord(x1,y2,z1));
	bo->getVecArr()[2] = new Vector(Coord(x1,y2,z1),Coord(x2,y2,z1));
	bo->getVecArr()[3] = new Vector(Coord(x2,y1,z1),Coord(x2,y2,z1));
	bo->getVecArr()[4] = new Vector(begin,Coord(x1,y1,z2));
	bo->getVecArr()[5] = new Vector(Coord(x1,y2,z1),Coord(x1,y2,z2));
	bo->getVecArr()[6] = new Vector(Coord(x2,y2,z1),end);
	bo->getVecArr()[7] = new Vector(Coord(x2,y1,z1),Coord(x2,y1,z2));
	bo->getVecArr()[8] = new Vector(Coord(x1,y1,z2),Coord(x1,y2,z2));
	bo->getVecArr()[9] = new Vector(Coord(x1,y1,z2),Coord(x2,y1,z2));
	bo->getVecArr()[10] = new Vector(Coord(x1,y2,z2),end);
	bo->getVecArr()[11] = new Vector(Coord(x2,y1,z2),end);
	return true;
}

bool sphere(Sphere* sp) { 
	//m - poludniki n - rownolezniki
	Coord center = sp->getCenter();
	double r = sp->getRadius();
	int m = sp->getMeridian();
	int n = sp->getParallel();
	double x = center.get_x();
	double y = center.get_y();
	double z = center.get_z();
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
			
			sp->getVecArr()[base] = new Vector(begin,end);
			++base;
		}
	}
	//towrzenie wektorow poludnikow
	//najpierw wychodzace z czubkow	
	for(int j=1;j<=m;++j) {
		Coord begin = cArr[0];
		Coord end = cArr[j];
		
		sp->getVecArr()[base] = new Vector(begin,end);
		++base;
	}
	for(int j=1;j<=m;++j) {
		Coord begin = cArr[m*n + 1];
		Coord end = cArr[(n-1)*m + j];
		
		sp->getVecArr()[base] = new Vector(begin,end);
		++base;
	}
	//miedzy rownoleznikami
	for(int i=1;i<n;++i) {
		for(int j=1;j<=m;++j) {
			Coord begin = cArr[(i-1)*m + j];
			Coord end = cArr[i*m + j];
			
			sp->getVecArr()[base] = new Vector(begin,end);
			++base;
		}
	}
	delete [] cArr;
	return true;
}

Solid* factory(int id, RGB col, double* params){
	int sid = (int)params[0];
	Solid* tmp_solid;
	switch(sid) {
		case 1 : 	tmp_solid = new Line(id,col,Coord(params[1],params[2],params[3]),Coord(params[4],params[5],params[6]));
					break;
		case 2 : 	tmp_solid = new Box(id,col,Coord(params[1],params[2],params[3]),Coord(params[4],params[5],params[6]));
					box((Box*)tmp_solid);
					break;
		case 3 : 	tmp_solid = new Sphere(id,col,Coord(params[1],params[2],params[3]),params[4],(int)params[5],(int)params[6]);
					sphere((Sphere*)tmp_solid);
					break;
		case 4 : 	tmp_solid = new Cone(id,col,Coord(params[1],params[2],params[3]),params[4],Coord(params[5],params[6],params[7]),params[8],params[9]);
					break;
		case 5 : 	tmp_solid = new Cylinder(id,col,Coord(params[1],params[2],params[3]),Coord(params[4],params[5],params[6]),params[7],params[8]);
					break;
		default :   tmp_solid = NULL;
					break;
	}
	return tmp_solid;
};


#endif //_FACTORY_
