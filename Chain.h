#ifndef _CHAIN_
#define _CHAIN_

#include <stdlib.h>
#include "String_Splitter.h"

using namespace std;

class Link {
public:
    Link(Link* next, PtrStrVec splitted_str) : __next(next), __splitted_str(splitted_str) {};
    virtual ~Link(){
        delete __next;
        delete __splitted_str;
    };
    
    Link* getnext() {
        return __next;
    }
    void setnext(Link* next) {
        __next = next;
    }
    
    virtual int* solve() = 0;
        
protected:  
    Link* __next;
    int* __result;
    PtrStrVec __splitted_str;
};

class Line_link : public Link {
public:
    Line_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new int[7];
    };
    ~Line_link(){
        delete [] __result;
    };
    
    int* solve() {
        if(__splitted_str->front() == "line") {
            __result[0] = 1;
            return __result;
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }
    };    
};

class Box_link : public Link {
public:
    Box_link(Link* next, PtrStrVec splitted_str) : Link(next,splitted_str) {
        __result = new int[7];
    };
    ~Box_link(){
        delete [] __result;
    };
    
    int* solve() {
        if(__splitted_str->front() == "box") {
            __result[0] = 2;
            return __result;
        }
        else {
            delete [] __result;
            __result = __next->solve();
        }
    };    
};

class Default : public Link {
public:
    Default(PtrStrVec splitted_str) : Link(NULL,splitted_str) {
        __result = new int[1];
    };
    ~Default(){
        delete [] __result;
    };
    
    int* solve() {
        __result[0] = 0;
        return __result;
    };    
};

class Chain{
public:
    Chain(PtrStrVec splitted_str){
        __default = new Default(splitted_str);
        __box = new Box_link(__default, splitted_str);
        __line = new Line_link(__box, splitted_str);
    };
    
    int* solve() {
        return __line->solve();
    }
    
    ~Chain(){
        delete __line;
        delete __box;
        delete __default;
    };
private:
    Line_link* __line;
    Box_link* __box;
    Default* __default;
};

#endif //_CHAIN_
