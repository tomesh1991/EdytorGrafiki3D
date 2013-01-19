#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include "Vector.h"

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

bool cone(Coord center1, double r1, Coord center2, double r2, int div, Vector* vecArr){
	//srodek dolnej podstawy
	int x1 = center1.get_x();
	int y1 = center1.get_y();
	int z1 = center1.get_z();
	cout << " cone" << endl;
	//srodek gornej podstawy
	int x2 = center2.get_x();
	int y2 = center2.get_y();
	int z2 = center2.get_z();
	cout << " cone" << endl;
	//kat obrotu
	double rotate_angle = 2*M_PI/div;
	//punkty na obwodzie dolnej i gornej podstawy
	Coord* lower = new Coord[div];
	Coord* upper = new Coord[div];
	lower[0] = Coord(x1+r1,y1,z1);
	upper[0] = Coord(x2+r2,y2,z2);
	/*
	double x_axis_traslation = x1 - x2;
	double y_axis_traslation = y1 - y2;
	double z_axis_traslation = z1 - z2;
	*/
	
	cout << " cone" << endl;
	for(int i = 1; i < div; ++i){
		double current_angle = rotate_angle*i;
		lower[i] = Coord(r1*cos(current_angle) + x1, y1, r1*sin(current_angle) + z1);
		upper[i] = Coord(r2*cos(current_angle) + x2, y2, r2*sin(current_angle) + z2);
	}
	
	int v = 0;
	cout << " cone" << endl;
	for(int i = 1; i < div; ++i){
		vecArr[v] = Vector(lower[i-1],lower[i]);
		++v;
	}
	vecArr[v] = Vector(lower[div-1], lower[0]);
	++v;
	cout << " cone" << endl;
	for(int i = 1; i < div; ++i){
		vecArr[v] = Vector(upper[i-1],upper[i]);
		++v;
	}
	vecArr[v] = Vector(upper[div-1], upper[0]);
	++v;
	cout << " cone" << endl;
	for(int i = 0; i < div; ++i){
		vecArr[v] = Vector(upper[i],lower[i]);
		++v;
	}cout << " cone" << endl;
	cout << "  v: " << v << endl;
	
	
	for(int i = 0; i < div; ++i){
		cout << i << " Lower Coord" << lower[i].toString() << endl;
	}
	for(int i = 0; i < div; ++i){
		cout << i << " Upper Coord" << upper[i].toString() << endl;
	}
	
	delete [] lower;
	delete [] upper;
	cout << " cone" << endl;
	return true;
};

int main() {
	Vector* vec = new Vector[40];
	cout << "main" << endl;
	int div = 5;
	cout << "div: " << div << endl;
	cout << cone(Coord(0.0,0.0,0.0),1.0,Coord(2.0,0.0,0.0),2.0,div,vec) << endl;
	cout << "main" << endl;
	for(int i = 0; i < div*3; ++i){
		cout << i << " " << vec[i].toString() << endl;
	}
	cout << "main" << endl;
    delete [] vec;
    cout << "main" << endl;
    system("pause");
    return 0;    
};
