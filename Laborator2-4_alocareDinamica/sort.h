#ifndef SORT_H_
#define SORT_H_

#include "MyList.h"
/*
   tipul functiei de comparare
   se bazeaza pe principiul functiei strcmp: 
		-returneaza 0 daca sunt egale
		-returneaza 1 daca tr1>tr2
		-returneaza -1 altfel

*/
typedef int(*FunctieComparare)(Tranzactie* tr1, Tranzactie* tr2);

/*
	cmpf - relatia dupa care se sorteaza
*/
void sort(MyList* l, FunctieComparare cmpF);

#endif

