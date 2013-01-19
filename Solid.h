#ifndef _SOLID_
#define _SOLID_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Vector.h"

using namespace std;

class Solid {
    public:
        Solid(unsigned int id, RGB& color) : __ID(id), __col(color){};
        virtual ~Solid(){};
    
        RGB& getcol() {
            return __col;
        }
    
        void setcol(RGB& col) {
            __col = col;
        }
    
        unsigned int getID(){
            return __ID;
        }
        
        void setID(int ID) {
        	__ID = ID;
        }
        
        int getSize() {
			return __size;
		}
        
        virtual void draw(/* wxDC *dc */) = 0;
    
    protected:        
        int __size;
        Vector** __vecArr;
        RGB __col;
        int __ID;    
};

class Line : public Solid {
    public:
        Line(unsigned int id, RGB color, Coord start, Coord end) 
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
        
        Vector** getVecArr() {
            return __vecArr;    
        }
        
        void draw(/* wxDC *dc */){
			//TO DO
        }
        
    protected:
        Coord __start;
        Coord __end;
};

class Box : public Solid {
    public:
        Box(unsigned int id, RGB col, Coord start, Coord end) 
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
        
        Vector** getVecArr() {
            return __vecArr;    
        }
        
        void draw(/* wxDC *dc */){
			//TO DO
		}
        
    protected:
        Coord __start;
        Coord __end;
};

class Sphere : public Solid {
    public:
        Sphere(unsigned int id, RGB col, Coord center, unsigned int rad, unsigned int mer, unsigned int par) 
			: Solid(id, col), __center(center), __radius(rad),
				__meridian(mer), __parallel(par) {
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
        
        unsigned int getRadius() {
            return __radius;
        }
        
        void setRadius(int radius) {
            __radius = radius;
        }
        
        unsigned int getMeridian() {
            return __meridian;
        }
        
        void setMeridian(int meridian) {
            __meridian = meridian;
        }
        
        unsigned int getParallel() {
            return __parallel;
        }
        
        void setParallel(int parallel) {
            __parallel = parallel;
        }
        
        Vector** getVecArr() {
            return __vecArr;    
        }
        
        void draw(/* wxDC *dc */){
			//TO DO
		}
        
    protected:
        Coord __center;
        unsigned int __radius;
        unsigned int __meridian;
        unsigned int __parallel;
};

class Cone : public Solid {
	public:
		Cone(unsigned int id, RGB& col, Coord& lowerCenter, unsigned int lowerRadius,
										Coord& upperCenter, unsigned int upperRadius,
										unsigned int surfaceDivision)
			: Solid(id, col), __lowerRadixCenter(lowerCenter), __lowerRadixRadius(lowerRadius),
	  						  __upperRadixCenter(upperCenter), __upperRadixRadius(upperRadius),
	  						  __lateralSurfaceDivision(surfaceDivision) {
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
		
		unsigned int getLowerRadixRadius(){
			return __lowerRadixRadius;
		}
		void setLowerRadixRadius(unsigned int radix){
			__lowerRadixRadius = radix;
		}
		
		unsigned int getUpperRadixRadius(){
			return __upperRadixRadius;
		}
		void setUpperRadixRadius(unsigned int radix){
			__upperRadixRadius = radix;
		}
		
		unsigned int getLateralSurfaceDivision(){
			return __lateralSurfaceDivision;
		}
		void setLateralSurfaceDivision(unsigned int div){
			__lateralSurfaceDivision = div;
		}
        
        Vector** getVecArr() {
            return __vecArr;    
        }
		
		void draw(/* wxDC *dc */){
			//TO DO
		}
		
	protected:
		Coord __lowerRadixCenter;
		Coord __upperRadixCenter;
		unsigned int __lowerRadixRadius;
		unsigned int __upperRadixRadius;
		unsigned int __lateralSurfaceDivision;
};

class Cylinder : public Solid {
	public:
		Cylinder(unsigned int id, RGB& col, Coord& lowerCenter, Coord& upperCenter, 
					unsigned int radius, unsigned int surfaceDivision)
			: Solid(id, col), __lowerRadixCenter(lowerCenter), __upperRadixCenter(upperCenter), 
	  						  __radixRadius(radius),
	  						  __lateralSurfaceDivision(surfaceDivision) {
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
		
		unsigned int getRadixRadius(){
			return __radixRadius;
		}
	  	void setRadixRadius(unsigned int radius){
			__radixRadius = radius;
		}
 		
	  	unsigned int getLateralSurfaceDivision(){
			return __lateralSurfaceDivision;
		}
		void setLateralSurfaceDivision(unsigned int div){
			__lateralSurfaceDivision = div;
		}
        
        Vector** getVecArr() {
            return __vecArr;    
        }
		
		void draw(/* wxDC *dc */){
			//TO DO
		}
		
	protected:
		Coord __lowerRadixCenter;
		Coord __upperRadixCenter;
		unsigned int __radixRadius;
		unsigned int __lateralSurfaceDivision;
};

#endif //_SOLID_
