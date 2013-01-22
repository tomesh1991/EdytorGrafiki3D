#ifndef _CHAIN_
#define _CHAIN_

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

typedef std::vector<std::string>* PtrStrVec;

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
    
    PtrStrVec string_splitter(std::string str, std::string ref = " "){
        /*  
        inicjalizujemy pusty wektor wynikowy - nalezy pamietac o tym, ze jest on zlokalizowany na stercie systemowej 
        wiec pamiec musi zostac potem zwolniona 
        */
        PtrStrVec result = new std::vector<std::string>();
        unsigned int start = 0, end = 0;
        
        /* 
        dla elegancji kodu wykorzystane zostaly metody klasy string ;)
        wyszukujemy kolejne wystapienia lancucha referencyjnego i na podstawie otrzymanych wynikow
        generujemy i stawiamy do wektora stringi z pojedynczymi wyrazami
        */
        end = str.find(ref, start);
        while(end != std::string::npos){
            result->push_back( str.substr(start, end-start) );
            start = end+ref.length();
            end = str.find(ref, start);
        }
        /*
        jezeli string sklada sie z pojedynczego slowa - wstawiamy je,
        jezeli z kilku, wrzucamy ostatni wyraz
        */
        result->push_back( str.substr(start, str.length()-start) );
        
        return result;
    }
    
    virtual double* solve() = 0;
        
protected:  
    Link* __next;
    double* __result;
    PtrStrVec __splitted_str;
};

class Colour_link : public Link {
public:
    Colour_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Colour_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "set_line_color" || __splitted_str->front() == "set_line_colour") {
			__result = new double[4];	
            __result[0] = 6;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp >> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }      
        return __result;
    };    
};

class Delete_link : public Link {
public:
    Delete_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Delete_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "delete") {
			__result = new double[2];	
            __result[0] = 7;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp >> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }      
        return __result;
    };    
};

class Move_link : public Link {
public:
    Move_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Move_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "move") {
			__result = new double[5];	
            __result[0] = 8;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp >> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }      
        return __result;
    };    
};

class Rotate_link : public Link {
public:
    Rotate_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Rotate_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "rotate") {
			__result = new double[8];	
            __result[0] = 9;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp >> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }      
        return __result;
    };    
};

class Line_link : public Link {
public:
    Line_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Line_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "line") {
			__result = new double[7];	
            __result[0] = 1;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }      
        return __result;
    };    
};

class Box_link : public Link {
public:
    Box_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Box_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "box") {
			__result = new double[7];
            __result[0] = 2;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }
        return __result;
    };    
};

class Sphere_link : public Link {
public:
    Sphere_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Sphere_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "sphere") {
			__result = new double[7];
            __result[0] = 3;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Cone_link : public Link {
public:
    Cone_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Cone_link(){};
    
    double* solve() {	
        if(__splitted_str->front() == "cone") {
			__result = new double[10];
            __result[0] = 4;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Cylinder_link : public Link {
public:
    Cylinder_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {};
    ~Cylinder_link(){};
    
    double* solve() {
        if(__splitted_str->front() == "cylinder") {
			__result = new double[9];
            __result[0] = 5;
            stringstream strm;
			for (std::vector<std::string>::iterator it = __splitted_str->begin() ; it != __splitted_str->end(); ++it) {
				strm << *it << ",";
			}
			string tmpstr = strm.str();
			PtrStrVec str_vec = string_splitter(tmpstr,",");
			int k = 1;
			for (std::vector<std::string>::iterator it = (str_vec->begin()+1); it != (str_vec->end()-1); ++it) {
				stringstream s;
				s << *it;
				char tmp;
				tmp = it->at(0);
				if(tmp == '(') s >> tmp>> __result[k];
				else s >> __result[k];
				++k;
			}
			delete str_vec;
        }
        else {
            __result = __next->solve();
        }        
        return __result;
    };    
};

class Default : public Link {
public:
    Default(PtrStrVec splitted_str) : Link(NULL,splitted_str) {};
    ~Default(){};
    
    double* solve() {
        __result = new double[1];
        __result[0] = 0;
        return __result;
    };    
};

class Chain{
public:
    Chain(string str){
        splitted_str = string_splitter(str);
        __default = new Default(splitted_str);
        __cylinder = new Cylinder_link(__default,splitted_str);
        __cone = new Cone_link(__cylinder,splitted_str);
        __sphere = new Sphere_link(__cone,splitted_str);
        __box = new Box_link(__sphere, splitted_str);
        __line = new Line_link(__box, splitted_str);
        __rotate = new Rotate_link(__line, splitted_str);
        __move = new Move_link(__rotate, splitted_str);
		__delete = new Delete_link(__move, splitted_str);
        __colour= new Colour_link(__delete, splitted_str);
    };
    
    double* solve() {
        return __colour->solve();
    }
    
    PtrStrVec getSplStr(){
        return splitted_str;
    }
    
    PtrStrVec string_splitter(std::string str, std::string ref = " "){
        /*  
        inicjalizujemy pusty wektor wynikowy - nalezy pamietac o tym, ze jest on zlokalizowany na stercie systemowej 
        wiec pamiec musi zostac potem zwolniona 
        */
        PtrStrVec result = new std::vector<std::string>();
        unsigned int start = 0, end = 0;
        
        /* 
        dla elegancji kodu wykorzystane zostaly metody klasy string ;)
        wyszukujemy kolejne wystapienia lancucha referencyjnego i na podstawie otrzymanych wynikow
        generujemy i stawiamy do wektora stringi z pojedynczymi wyrazami
        */
        end = str.find(ref, start);
        while(end != std::string::npos){
            result->push_back( str.substr(start, end-start) );
            start = end+ref.length();
            end = str.find(ref, start);
        }
        /*
        jezeli string sklada sie z pojedynczego slowa - wstawiamy je,
        jezeli z kilku, wrzucamy ostatni wyraz
        */
        result->push_back( str.substr(start, str.length()-start) );
        
        return result;
    }
    
    ~Chain(){
		delete __colour;
		delete __delete;
		delete __move;
		delete __rotate;
        delete __line;
        delete __box;
        delete __sphere;
        delete __cone;
        delete __cylinder;
        delete __default;
        delete splitted_str;
    };
private:
    PtrStrVec splitted_str;
	Colour_link* __colour;
	Delete_link* __delete;
	Move_link* __move;
	Rotate_link* __rotate;
    Line_link* __line;
    Box_link* __box;
    Sphere_link* __sphere;
    Cone_link* __cone;
    Cylinder_link* __cylinder;
    Default* __default;
};

#endif //_CHAIN_
