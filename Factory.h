#ifndef _FACTORY_
#define _FACTORY_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "Solid.h"

using namespace std;

class Factory {
public:
    Factory(){};
    ~Factory(){};
    
    Solid* produce(int id, RGBCol col, double* params) {
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
    		            cone((Cone*)tmp_solid);
    					break;
    		case 5 : 	tmp_solid = new Cylinder(id,col,Coord(params[1],params[2],params[3]),Coord(params[4],params[5],params[6]),params[7],params[8]);
    		            cylinder((Cylinder*)tmp_solid);
    					break;
    		default :   tmp_solid = NULL;
    					break;
    	}
    	return tmp_solid;
    }
    
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
    
    bool cone(Cone* co){
        Coord bottom = co->getLowerRadixCenter();
        Coord top = co->getUpperRadixCenter();
        double rb = co->getLowerRadixRadius();
        double rt = co->getUpperRadixRadius();
        int n = co->getLateralSurfaceDivision();
        
        double x_b, y_b, z_b;//wspó³rzêdne œrodka podstawy dolnej
        double x_t, y_t, z_t;//wspó³rzêdne œrodka podstawy górnej
        
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
    		double new_x = cos(crad)*rb;
    		if(fabs(new_x) < 0.0000001) new_x = 0.;
    		double new_z = sin(crad)*rb;
    		if(fabs(new_z) < 0.0000001) new_z = 0.;
    		cArr[i-1] = Coord(new_x,0,new_z);
    	}
    	for(int i=(n+1);i<=(2*n);++i) {
    		double crad = rad * (i-1);
    		double new_x = cos(crad)*rt;
    		if(fabs(new_x) < 0.0000001) new_x = 0.;
    		double new_z = sin(crad)*rt;
    		if(fabs(new_z) < 0.0000001) new_z = 0.;
    		cArr[i-1] = Coord(new_x,0,new_z);
    	}
    	//rotacja pierwszej podstawy
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
        //rotacja drugiej podstawy
        for(int i=n;i<(2*n);++i) {
            if(fabs(z_t-z_b) == 0) {
                RotateY(oy)*cArr[i];       
                RotateZ(-oz)*cArr[i];
            }
            else {      
                RotateX(ox)*cArr[i];
                RotateY(oy)*cArr[i]; 
            }
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
    		co->getVecArr()[i]->setBegin(cArr[i]);
    		co->getVecArr()[i]->setEnd(cArr[i+1]);
    	}
    		co->getVecArr()[n-1]->setBegin(cArr[n-1]);
    		co->getVecArr()[n-1]->setEnd(cArr[0]);
        //druga podstawa
        for(int i=n;i<((2*n)-1);++i) {
    		co->getVecArr()[i]->setBegin(cArr[i]);
    		co->getVecArr()[i]->setEnd(cArr[i+1]);
    	}
    		co->getVecArr()[2*n-1]->setBegin(cArr[2*n-1]);
    		co->getVecArr()[2*n-1]->setEnd(cArr[n]);
    	//sciany boczne
    	for(int i=0;i<(n-1);++i) {
    		co->getVecArr()[2*n + i]->setBegin(cArr[i]);
    		co->getVecArr()[2*n + i]->setEnd(cArr[n+i]);
    	}
    		co->getVecArr()[3*n-1]->setBegin(cArr[n-1]);
    		co->getVecArr()[3*n-1]->setEnd(cArr[(2*n)-1]);
        //zwalnianie pamieci i return
        delete [] cArr;
        return true;
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
};


#endif //_FACTORY_
