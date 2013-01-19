#ifndef _SPLITTER_
#define _SPLITTER_

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

typedef std::vector<std::string>* PtrStrVec;

/*************************************************************************** 
funkcja string_splitter sluzy do dzielenia stringa na krotsze 
jako lancuch referencyjny do podzialu domyslnie sluzy pojedynczy odstep (spacja)
rezultat dzialania funkcji znajduje sie w wektorze o elementach typu string 
***************************************************************************/

PtrStrVec string_splitter(std::string& str, std::string ref = " "){
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

#endif //_SPLITTER_
