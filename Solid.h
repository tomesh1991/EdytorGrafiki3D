#ifndef _SOLID_
#define _SOLID_

#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include "Vector.h"

using namespace std;

class Solid {
    public:
        Solid(unsigned int id, RGBCol& color) : __ID(id), __col(color){};
        virtual ~Solid(){};
    
        RGBCol& getcol() {
            return __col;
        }
    
        void setcol(RGBCol& col) {
            __col = col;
        }
    
        unsigned int getID(){
            return __ID;
        }
        
        void setID(unsigned int ID) {
        	__ID = ID;
        }
        
        int getSize() {
			return __size;
		}
        
        Vector** getVecArr() {
            return __vecArr;    
        }
        //mod by Wach////////////////////
        Vector* getSingleVec(int i){
            return __vecArr[i];    
        }
        //////////////////////////////////
        
        void move(double* param){
            
        }
        
        void rotate(double* param){
            
        }
        
        virtual string toString() = 0;
        virtual string toList() = 0;
    
    protected:        
        int __size;
        Vector** __vecArr;
        unsigned int __ID; 
        RGBCol __col;   
};

class Line : public Solid {
    public:
        Line(unsigned int id, RGBCol color, Coord start, Coord end) 
            : Solid(id, color), __start(start), __end(end) {
            __size = 1;
            __vecArr = new Vector* [__size];
            __vecArr[0] = new Vector(start,end);
        }
        virtual ~Line(){
            delete __vecArr[0];
            delete [] __vecArr;
        }
    
        Coord& getStart() {
            return __start;
        }
        
        void setStart(Coord& start) {
            __start = start;
        }
        
        Coord& getEnd() {
            return __end;
        }
        
        void setEnd(Coord& end) {
            __end = end;
        }
        
       /* void move(double* mvect){
            __start.set_x(__start.get_x() + mvect[1]);
            __start.set_y(__start.get_y() + mvect[2]);
            __start.set_z(__start.get_z() + mvect[3]);
            
            __end.set_x(__end.get_x() + mvect[1]);
            __end.set_y(__end.get_y() + mvect[2]);
            __end.set_z(__end.get_z() + mvect[3]);
        }
        
        void rotate(double* par){}*/
        
        string toString() {
			stringstream strm;
			strm << __ID << ": Line, begins at " << __start.toString() << ", and ends at " << __end.toString() << ".";
			string tmp = strm.str();
			return tmp;
		}
		
		string toList() {
			stringstream strm;
			strm << __ID << " line " << __start.toString() << "," << __end.toString();
			string tmp = strm.str();
			return tmp;
		}
        
    protected:
        Coord __start;
        Coord __end;
};

class Box : public Solid {
    public:
        Box(unsigned int id, RGBCol col, Coord start, Coord end) 
			: Solid(id, col), __start(start), __end(end) {
            __size = 12;
            __vecArr = new Vector* [__size];
            for(int i=0;i<__size;++i) {
                __vecArr[i] = new Vector();
            }
        };
        virtual ~Box() {
            for(int i=0;i<__size;++i) {
                delete __vecArr[i];
            }
            delete [] __vecArr;
        };
        
        Coord& getStart() {
            return __start;
        }
        void setStart(Coord& start) {
            __start = start;
        }
        Coord& getEnd() {
            return __end;
        }
        void setEnd(Coord& end) {
            __end = end;
        }
		
		/*void move(double* mvect){
            __start.set_x(__start.get_x() + mvect[1]);
            __start.set_y(__start.get_y() + mvect[2]);
            __start.set_z(__start.get_z() + mvect[3]);
            
            __end.set_x(__end.get_x() + mvect[1]);
            __end.set_y(__end.get_y() + mvect[2]);
            __end.set_z(__end.get_z() + mvect[3]);
        }
        
        void rotate(double* par){}*/
        
        string toString() {
			stringstream strm;
			strm << __ID << ": Box, begins at " << __start.toString() << ", and ends at " << __end.toString() << ".";
			string tmp = strm.str();
			return tmp;
		}
		
		string toList() {
			stringstream strm;
			strm << __ID << " box " << __start.toString() << "," << __end.toString();
			string tmp = strm.str();
			return tmp;
		}
		
        
    protected:
        Coord __start;
        Coord __end;
};

class Sphere : public Solid {
    public:
        Sphere(unsigned int id, RGBCol col, Coord center, double rad, int mer, int par) 
			: Solid(id, col), __center(center), __radius(rad){
			if(mer < 3) __meridian = 3;
			else __meridian = mer;
			if(par < 3) __parallel = 3;
			else __parallel = par;
            __size = (2*__parallel +1)*__meridian;
            __vecArr = new Vector* [__size];
            for(int i=0;i<__size;++i) {
                __vecArr[i] = new Vector();
            }
        };
				
        virtual ~Sphere() {
            for(int i=0;i<__size;++i) {
                delete __vecArr[i];
            }
            delete [] __vecArr;
        };
        
        Coord getCenter() {
            return __center;
        }
        
        void setCenter(Coord& center) {
            __center = center;
        }
        
        double getRadius() {
            return __radius;
        }
        
        void setRadius(double radius) {
            __radius = radius;
        }
        
        int getMeridian() {
            return __meridian;
        }
        
        void setMeridian(int meridian) {
            __meridian = meridian;
        }
        
        int getParallel() {
            return __parallel;
        }
        
        void setParallel(int parallel) {
            __parallel = parallel;
        }
        
		
		/*void move(double* mvect){
            __center.set_x(__center.get_x() + mvect[1]);
            __center.set_y(__center.get_y() + mvect[2]);
            __center.set_z(__center.get_z() + mvect[3]);
        }
        
        void rotate(double* par){
            
        }*/
        
        string toString() {
			stringstream strm;
			strm << __ID << ": Sphere, center at " << __center.toString() << ", with radius " << __radius << ", rendered with " << __meridian << " meridians and " << __parallel << " parallels";
			string tmp = strm.str();
			return tmp;
		}
		
		string toList() {
			stringstream strm;
			strm << __ID << " sphere " << __center.toString() << "," << __radius;
			string tmp = strm.str();
			return tmp;
		}
        
    protected:
        Coord __center;
        double __radius;
        int __meridian;
        int __parallel;
};

class Cone : public Solid {
	public:
		Cone(unsigned int id, RGBCol col, 	Coord lowerCenter, double lowerRadius,
										Coord upperCenter, double upperRadius,
										int surfaceDivision)
			: Solid(id, col), __lowerRadixCenter(lowerCenter), __upperRadixCenter(upperCenter),
							  __lowerRadixRadius(lowerRadius), __upperRadixRadius(upperRadius) {
	  		if(surfaceDivision < 3) __lateralSurfaceDivision = 3;
	  		else __lateralSurfaceDivision = surfaceDivision;
            __size = (3*__lateralSurfaceDivision);
            __vecArr = new Vector* [__size];
            for(int i=0;i<__size;++i) {
                __vecArr[i] = new Vector();
            }
        }
        
        virtual ~Cone() {
            for(int i=0;i<__size;++i) {
                delete __vecArr[i];
            }
            delete [] __vecArr;
        }
		
		Coord& getLowerRadixCenter(){
			return __lowerRadixCenter;
		}
		void setLowerRadixCenter(Coord& center){
			__lowerRadixCenter = center;
		}
		
		Coord& getUpperRadixCenter(){
			return __upperRadixCenter;
		}
		void setUpperRadixCenter(Coord& center){
			__upperRadixCenter = center;
		}
		
		double getLowerRadixRadius(){
			return __lowerRadixRadius;
		}
		void setLowerRadixRadius(double radix){
			__lowerRadixRadius = radix;
		}
		
		double getUpperRadixRadius(){
			return __upperRadixRadius;
		}
		void setUpperRadixRadius(double radix){
			__upperRadixRadius = radix;
		}
		
		int getLateralSurfaceDivision(){
			return __lateralSurfaceDivision;
		}
		void setLateralSurfaceDivision(int div){
			__lateralSurfaceDivision = div;
		}
		
		/*void move(double* mvect){
            __lowerRadixCenter.set_x(__lowerRadixCenter.get_x() + mvect[1]);
            __lowerRadixCenter.set_y(__lowerRadixCenter.get_y() + mvect[2]);
            __lowerRadixCenter.set_z(__lowerRadixCenter.get_z() + mvect[3]);
            
            __upperRadixCenter.set_x(__upperRadixCenter.get_x() + mvect[1]);
            __upperRadixCenter.set_y(__upperRadixCenter.get_y() + mvect[2]);
            __upperRadixCenter.set_z(__upperRadixCenter.get_z() + mvect[3]);
        }
		
		void rotate(double* par){}
		*/
		string toString() {
			stringstream strm;
			strm << __ID << ": Cone, first base at " << __lowerRadixCenter.toString() << ", with radius " << __lowerRadixRadius << ". Second base at " << __upperRadixCenter.toString() << ", with radius " << __upperRadixRadius << ". Rendered with " << __lateralSurfaceDivision << " quads.";
			string tmp = strm.str();
			return tmp;
		}
		
		string toList() {
			stringstream strm;
			strm << __ID << " cone " << __lowerRadixCenter.toString() << "," << __lowerRadixRadius << "," << __upperRadixCenter.toString() << "," << __upperRadixRadius;
			string tmp = strm.str();
			return tmp;
		}
		
	protected:
		Coord __lowerRadixCenter;
		Coord __upperRadixCenter;
		double __lowerRadixRadius;
		double __upperRadixRadius;
		int __lateralSurfaceDivision;
};

class Cylinder : public Solid {
	public:
		Cylinder(unsigned int id, RGBCol col, Coord lowerCenter, Coord upperCenter, 
					double radius, int surfaceDivision)
			: Solid(id, col), __lowerRadixCenter(lowerCenter), __upperRadixCenter(upperCenter), 
	  						  __radixRadius(radius) {
			if(surfaceDivision < 3) __lateralSurfaceDivision = 3;
	  		else __lateralSurfaceDivision = surfaceDivision;
            __size = (3*__lateralSurfaceDivision);
            __vecArr = new Vector* [__size];
            for(int i=0;i<__size;++i) {
                __vecArr[i] = new Vector();
            }
        }
        
        virtual ~Cylinder() {
            for(int i=0;i<__size;++i) {
                delete __vecArr[i];
            }
            delete [] __vecArr;
        }
	  	
	  	Coord& getLowerRadixCenter(){
			return __lowerRadixCenter;
		}
		void setLowerRadixCenter(Coord& center){
			__lowerRadixCenter = center;
		}
		
		Coord& getUpperRadixCenter(){
			return __upperRadixCenter;
		}
		void setUpperRadixCenter(Coord& center){
			__upperRadixCenter = center;
		}
		
		double getRadixRadius(){
			return __radixRadius;
		}
	  	void setRadixRadius(double radius){
			__radixRadius = radius;
		}
 		
	  	int getLateralSurfaceDivision(){
			return __lateralSurfaceDivision;
		}
		void setLateralSurfaceDivision(int div){
			__lateralSurfaceDivision = div;
		}
		
		/*void move(double* mvect){
            __lowerRadixCenter.set_x(__lowerRadixCenter.get_x() + mvect[1]);
            __lowerRadixCenter.set_y(__lowerRadixCenter.get_y() + mvect[2]);
            __lowerRadixCenter.set_z(__lowerRadixCenter.get_z() + mvect[3]);
            
            __upperRadixCenter.set_x(__upperRadixCenter.get_x() + mvect[1]);
            __upperRadixCenter.set_y(__upperRadixCenter.get_y() + mvect[2]);
            __upperRadixCenter.set_z(__upperRadixCenter.get_z() + mvect[3]);
        }
        
        void rotate(double* par){}*/
		
		void toFile() {
			stringstream strm;
			FILE* fp;
			fp = fopen("file.geo","w");
			for(int i = 0 ;i<__size;i++){
                strm << __vecArr[i]->getBegin().get_x() << " " << __vecArr[i]->getBegin().get_y() << " " << __vecArr[i]->getBegin().get_z() << " " << __vecArr[i]->getEnd().get_x() << " " << __vecArr[i]->getEnd().get_y() << " " << __vecArr[i]->getEnd().get_z() << " " << 0 << " " << 0 << " " << 0 << endl;
                fputs(strm.str().c_str(), fp);    
            }
            fclose(fp);
        }
		
		string toString() {
			stringstream strm;
			strm << __ID << ": Cylinder, first base at " << __lowerRadixCenter.toString() << ", second at " << __upperRadixCenter.toString() << ", with radius " << __radixRadius << ". Rendered with " << __lateralSurfaceDivision << " quads.";
			string tmp = strm.str();
			return tmp;
		}
		
		string toList() {
			stringstream strm;
			strm << __ID << " cylinder " << __lowerRadixCenter.toString() << "," << __upperRadixCenter.toString() << "," << __radixRadius;
			string tmp = strm.str();
			return tmp;
		}
		
	protected:
		Coord __lowerRadixCenter;
		Coord __upperRadixCenter;
		double __radixRadius;
		int __lateralSurfaceDivision;
};

#endif //_SOLID_
