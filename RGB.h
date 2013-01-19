#ifndef _RGB_H_
#define _RGB_H_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class RGB{
    private:
        unsigned short m_r, m_g, m_b;
        
    public:
        RGB(){
            m_r = 255;
            m_g = 255;
            m_b = 255;
        }
        
        RGB(unsigned short r, unsigned short g, unsigned short b){
            m_r = r;
            m_g = g;
            m_b = b;
        }
        
        unsigned short get_r(){
            return m_r;
        }
        
        unsigned short get_g(){
            return m_g;
        }
        
        unsigned short get_b(){
            return m_b;
        }
        
        void set_r(unsigned short r){
            m_r = r;
        }
        
        void set_g(unsigned short g){
            m_g = g;
        }
        
        void set_b(unsigned short b){
            m_b = b;
        }
        
        string toString() {
            ostringstream strm;
            strm << "[" << m_r << "," << m_g << "," << m_b << "]";
            return strm.str();
        }
};

#endif
