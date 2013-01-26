#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
    string s("19");
    double id = strtod(s.c_str(),NULL);
    cout << id << endl;
    
    system("pause");
    return 0;
}
