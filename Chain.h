#ifndef _CHAIN_
#define _CHAIN_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "String_Splitter.h"

using namespace std;

class Link {
public:
    Link(Link* next, PtrStrVec splitted_str) : __next(next), __splitted_str(splitted_str) {};
    virtual ~Link(){};
    
    Link* getnext() {
        return __next;
    }
    void setnext(Link* next) {
        __next = next;
    }
    
    virtual double* solve() = 0;
        
protected:  
    Link* __next;
    double* __result;
    PtrStrVec __splitted_str;
};

class Line_link : public Link {
public:
    Line_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new double[7];
    };
    ~Line_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "line") {
            __result[0] = 1;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec test_str = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (test_str->begin()+1); it != (test_str->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Box_link : public Link {
public:
    Box_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new double[7];
    };
    ~Box_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "box") {
            __result[0] = 2;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec test_str = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (test_str->begin()+1); it != (test_str->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }
        return __result;
    };    
};

class Sphere_link : public Link {
public:
    Sphere_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new double[7];
    };
    ~Sphere_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "sphere") {
            __result[0] = 3;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec test_str = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (test_str->begin()+1); it != (test_str->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Cone_link : public Link {
public:
    Cone_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new double[10];
    };
    ~Cone_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "cone") {
            __result[0] = 4;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec test_str = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (test_str->begin()+1); it != (test_str->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Cylinder_link : public Link {
public:
    Cylinder_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new double[9];
    };
    ~Cylinder_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "cylinder") {
            __result[0] = 5;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec test_str = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (test_str->begin()+1); it != (test_str->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Default : public Link {
public:
    Default(PtrStrVec splitted_str) : Link(NULL,splitted_str) {
        __result = new double[1];
    };
    ~Default(){};
    
    double* solve() {
        __result[0] = 0;
        return __result;
    };    
};

class Chain{
public:
    Chain(PtrStrVec splitted_str){
        __default = new Default(splitted_str);
        __cylinder = new Cylinder_link(__default,splitted_str);
        __cone = new Cone_link(__cylinder,splitted_str);
        __sphere = new Sphere_link(__cone,splitted_str);
        __box = new Box_link(__sphere, splitted_str);
        __line = new Line_link(__box, splitted_str);
    };
    
    double* solve() {
        return __line->solve();
    }
    
    ~Chain(){
        delete __line;
        delete __box;
        delete __sphere;
        delete __cone;
        delete __cylinder;
        delete __default;
    };
private:
    Line_link* __line;
    Box_link* __box;
    Sphere_link* __sphere;
    Cone_link* __cone;
    Cylinder_link* __cylinder;
    Default* __default;
};

#endif //_CHAIN_
