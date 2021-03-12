#pragma once
#include "tranzactie.h"

typedef void* ElemType;

typedef void (*DestroyFct)(ElemType);

typedef ElemType (*CopyFct)(ElemType);

typedef struct {
	ElemType* elemente;
	int lungime;
	int capacitate;
	DestroyFct dfnc;
} MyList;

/*
	functia creeaza o lista vida
	input:-
	output: o lista vida 
*/
MyList* creeaza_lista();

/*
	functia distruge o lista
	input: l-lista de tranzactii
	output: -
*/
void distruge_lista(MyList* l);

/*
	functia returneaza un element din lista
	input:  l-lista de tranzactii
			poz-pozitia elementului din lista, trebuie sa fie valida
*/
ElemType get(MyList* l, int poz);

/*
	functia modifica elementul de pe pozitia poz cu elementul tr
	input:  l-lista de tranzactii
			poz-pozitia elementului din lista, trebuie sa fie valida
			tr - o tranzactie
	output: elementul modificat
*/
ElemType set(MyList* l, int poz, ElemType tr);

/*
	functia returneaza numarul de elemente din lista
	input: l-lista de tranzactii
	output: numarul de elemente din lista
*/
int size(MyList* l);

/*
	functia asigura capacitatea in cazul in care este nevoie de mai mult spatiu pentru a adauga
	input: l-lista de tranzactii
	output:-
*/
void asigura_capacitate(MyList* l);

/*
	functia modifica un element din lista
	input: l-lista de tranzactii
			elementul de adaugat
	output:-
*/
void adauga(MyList* l, ElemType element);

/*
	functia sterge un element din lista
	input: l-lista de tranzactii
			elementul cu care se va modifica
	output:-
*/
void modifica(MyList* l, ElemType element);

/*
	functia creeaza o copie a listei date
	input: l-lista de tranzactii
			elementul care va fi sters
	output:-
*/
void sterge(MyList* l, ElemType element);

/*
	functia creeaza o copie a listei date
	input: l-lista de tranzactii
	output: o copie a listei l
*/
MyList* copiere_lista(MyList* l, CopyFct cf);


ElemType removeLast(MyList* l);

void test_creeaza_lista();
void test_distruge_lista();
void test_get();
void test_size();
void test_adauga();
void test_modifica();
//void test_sterge();
void test_copiere_lista();
void test_asigura_capacitate();
void testRemoveLast();
