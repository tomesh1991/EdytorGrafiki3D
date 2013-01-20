#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Chain.h"

using namespace std;

int main() {
	string str = "cylinder (1.2,2.3,3.4),(2.6,8.8,-17.6),-2.2,10";
	PtrStrVec test_str = string_splitter(str);
	
	Chain* ch = new Chain(test_str);
	double* dArr = ch->solve();	
	if(dArr[0])
		for(int i=0;i<9;++i)
			cout << dArr[i] << " ";
	else cout << " NIEZNANA FORMUŁA ";
	cout << endl;
	
	delete [] dArr;
	delete ch;
	delete test_str;
	return 0;
};
