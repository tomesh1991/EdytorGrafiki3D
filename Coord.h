#ifndef _COORD_H_
#define _COORD_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Coord{
    private:
        double m_x, m_y, m_z;
        
    public:
        Coord(){
            m_x = 0;
            m_y = 0;
            m_z = 0;
        }
        
        Coord(double x, double y, double z){
            m_x = x;
            m_y = y;
            m_z = z;
        }
        
        double get_x(){
            return m_x;
        }
        
        double get_y(){
            return m_y;
        }
        
        double get_z(){
            return m_z;
        }
        
        void set_x(double x){
            m_x = x;
        }
        
        void set_y(double y){
            m_y = y;
        }
        
        void set_z(double z){
            m_z = z;
        }
        
        string toString() {
            ostringstream strm;
            strm << "(" << m_x << "," << m_y << "," << m_z << ")";
            return strm.str();
        }
};

#endif //_COORD_H_
