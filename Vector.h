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
        
        void setBegin(int x, int y, int z) {
            __begin = Coord(x,y,z);
        }
        void setBegin(const Coord& C) {
            __begin = C;
        }
        void setEnd(int x, int y, int z) {
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
        };
};

#endif //_VECTOR_H_
