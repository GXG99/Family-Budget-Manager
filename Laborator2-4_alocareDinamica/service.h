#pragma once
#include "MyList.h"

typedef struct {
	MyList* toate_tr;
	MyList* undoList;
	MyList* redoList;
} TrSrv;


TrSrv creeaza_srv();

void destroy_srv(TrSrv* srv);
/*
	adaugare tranzactie
	input: l-lista de tranzactii
			zi-numar natural care apartine intervalului [1,31]
			suma-numar real pozitiv 
			tip-string care poate fi intrare sau iesire 
			descriere-string
	output: 0-daca adaugarea a avut loc cu succes 
			in caz contrar fiecare eroare are o cifra 
*/
int srv_adauga(TrSrv* srv, int zi, float suma, char* tip, char* descriere);

/*
	modifica tranzactie
	input: l-lista de tranzactii
			zi-numar natural care apartine intervalului [1,31]
			suma-numar real pozitiv
			tip-string care poate fi intrare sau iesire
			descriere-string
	output: 0-daca adaugarea a avut loc cu succes
			in caz contrar fiecare eroare are o cifra
*/
int srv_modifica(TrSrv* srv, int zi, float suma, char* tip, char* descriere);


MyList* getFiltered(TrSrv* srv, char* substringTip);

/*
	sterge tranzactie
	input: l-lista de tranzactii
			zi-numar natural care apartine intervalului [1,31]
			suma-numar real pozitiv
	output: 0-daca adaugarea a avut loc cu succes
			in caz contrar fiecare eroare are o cifra
*/
//int srv_sterge(MyList* l, int zi, float suma);

/*
	functia returneaza o lista cu tranzactiile de un anumit tip
	input: l-lista de tranzactii
			pass- 0 sau 1 si desemneaza tipul tranzactiei
	output: lista filtrata
*/
//MyList srv_filtrare_tip(TrSrv* l, int pass);

/*
	functia returneaza o lista cu tranzactiile care au suma mai mare decat o anumita suma
	input: l-lista de tranzactii
			suma-numar real pozitiv 
	output: lista filtrata
*/
//MyList srv_filtrare_sumaMaiMare(TrSrv* l, float suma);

/*
	functia returneaza o lista cu tranzactiile care au suma mai mica decat o anumita suma
	input: l-lista de tranzactii
			suma-numar real pozitiv
	output: lista filtrata
*/
MyList* srv_filtrare_sumaMaiMica(TrSrv* l, float suma);

/*
	functia returneaza o lista cu toate tranzactiile ordonate dupa suma
	input: l-lista de tranzactii
	output: lista filtrata
*/
MyList* srv_ordonare_dupa_suma(TrSrv* l);

/*
	functia returneaza o lista cu toate tranzactiile ordonate dupa zi
	input: l-lista de tranzactii
	output: lista filtrata
*/
MyList* srv_ordonare_dupa_zi(TrSrv* l);

/*
	input: doua elemente de tipul Tranzactie
	output: 1 daca tr1.suma > tr2.suma
			-1 daca tr1.suma < tr2.suma
			o altfel
*/
int cmpSuma(Tranzactie* tr1, Tranzactie* tr2);

/*
	input: doua elemente de tipul Tranzactie
	output: 1 daca tr1.zi > tr2.zi
			-1 daca tr1.zi < tr2.zi
			o altfel
*/
int cmpZi(Tranzactie* tr1, Tranzactie* tr2);

int undo(TrSrv* srv);
int redo(TrSrv* srv);

void test_srv_adauga();
void test_srv_modifica();
//void test_srv_sterge();
//void test_filtrare_tip();
//void test_filtrare_sumaMaiMare();
//void test_filtrare_sumaMaiMica();
void test_ordonare1();
void test_ordonare2();
void test_cmpSuma();
void test_cmpZi();
void testUndo();
void test_filtered();
