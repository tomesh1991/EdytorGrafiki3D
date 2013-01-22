#ifndef _RGBCol_H_
#define _RGBCol_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class RGBCol{
    private:
        int m_r, m_g, m_b;
        
    public:
        RGBCol() {
            m_r = 0;
            m_g = 0;
            m_b = 0;
        }
        
        RGBCol(int r, int g, int b){
            m_r = r;
            m_g = g;
            m_b = b;
        }
        
        ~RGBCol(){}
        
        int get_r(){
            return m_r;
        }
        
        int get_g(){
            return m_g;
        }
        
        int get_b(){
            return m_b;
        }
        
        void set_r(int r){
            m_r = r;
        }
        
        void set_g(int g){
            m_g = g;
        }
        
        void set_b(int b){
            m_b = b;
        }
        
        string toString() {
            ostringstream strm;
            strm << "[" << m_r << "," << m_g << "," << m_b << "]";
            return strm.str();
        }
};

#endif //_RGBCol_
