#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Chain.h"
#include "Solid.h"
#include "Factory.h"

using namespace std;

int main(int argc, const char* argv[]) {
	stringstream strm;
	strm << "line (5.12,0.11,-2.5),(10,-7.5,2.4)";
	string str = strm.str();
	PtrStrVec str_vec = string_splitter(str);	
	Chain* ch = new Chain(str_vec);
	double* params = ch->solve();
	/*Solid* s = factory(5,RGB(0,0,0),params);
	delete s;*/
	delete [] params;
	delete ch;
	delete str_vec;
	return 0;
};
