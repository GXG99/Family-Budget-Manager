#include "MyList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

MyList* creeaza_lista(DestroyFct f) {
	MyList* rez = malloc(sizeof(MyList));
	rez->capacitate = 4;
	rez->elemente = malloc(sizeof(ElemType) * rez->capacitate);
	rez->lungime = 0;
	rez->dfnc = f;
	return rez;
}

void distruge_lista(MyList* l) {
	for (int i = 0; i < l->lungime; i++)
		l->dfnc(l->elemente[i]);
	free(l->elemente);
	free(l);
	//l->lungime = 0;
}


ElemType removeLast(MyList* l) {
	ElemType rez = l->elemente[l->lungime - 1];
	l->lungime -= 1;
	return rez;
}


ElemType get(MyList* l, int poz) {
	return l->elemente[poz];
}

ElemType set(MyList* l, int poz, ElemType tr) {
	ElemType rez = l->elemente[poz];
	l->elemente[poz] = tr;
	return rez;
}


int size(MyList* l) {
	return l->lungime;
}

void asigura_capacitate(MyList* l) {
	int capacitate_noua = l->capacitate + 4;
	ElemType* elemente_noi = malloc(sizeof(ElemType) * capacitate_noua);
	for (int i = 0; i < l->lungime; i++)
		elemente_noi[i] = l->elemente[i];
	free(l->elemente);
	l->elemente = elemente_noi;
	l->capacitate = capacitate_noua;
}

void adauga(MyList* l, ElemType element) {
	if (l->capacitate <= l->lungime)
		asigura_capacitate(l);
	l->elemente[l->lungime] = element;
	l->lungime++;
}


void modifica(MyList* l, ElemType element) {

	Tranzactie* elem = element;
	for (int i = 0; i < l->lungime; i++) {
		Tranzactie* tr = get(l, i);
		if (tr->zi == elem->zi && strcmp(tr->tip, elem->tip) == 0) {
			set(l, i, element);
			distruge_tranzactie(tr);
		}
	}
}


void test_modifica() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	adauga(l, creeaza_tranzactie(25, 200, "intrare", "transfer1"));
	modifica(l, creeaza_tranzactie(25, 150, "intrare", "descriere1"));

	Tranzactie* tr = get(l, 0);
	assert(tr->suma == 150);

	distruge_lista(l);
}


MyList* copiere_lista(MyList* l, CopyFct cf) {
	MyList* rez = creeaza_lista(l->dfnc);
	for (int i = 0; i < size(l); i++) {
		ElemType tr = get(l, i);
		adauga(rez, cf(tr));
	}
	return rez;
}

void test_creeaza_lista() {
	MyList* rez = creeaza_lista(distruge_tranzactie);
	assert(size(rez) == 0);
	distruge_lista(rez);
}

void test_distruge_lista() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	adauga(l, creeaza_tranzactie(11, 250, "intrare", "transfer3"));
	distruge_lista(l);
}

void test_get() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	Tranzactie* tr = creeaza_tranzactie(25, 200, "intrare", "transfer1");
	adauga(l, tr);
	Tranzactie* tr1 = get(l, 0);
	assert(tr1->zi == 25);
	assert(tr1->suma == 200);
	assert(strcmp(tr1->tip, "intrare") == 0);
	assert(strcmp(tr1->descriere, "transfer1") == 0);
	distruge_lista(l);
}

void test_size() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	assert(size(l) == 0);
	distruge_lista(l);
}

void test_adauga() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	Tranzactie* tr = creeaza_tranzactie(25, 200, "intrare", "transfer1");
	adauga(l, tr);
	assert(size(l) == 1);
	distruge_lista(l);
}

//void test_modifica() {
//	MyList* l = creeaza_lista(distruge_tranzactie);
//	Tranzactie* tr = creeaza_tranzactie(25, 200, "intrare", "transfer1");
//	adauga(l, tr);
//	Tranzactie* tr2 = creeaza_tranzactie(25, 25, "intrare", "ok");
//	modifica(l, tr2);
//	Tranzactie* u = get(l, 0);
//	assert(u->zi == 25);
//	assert(u->suma == 25);
//	distruge_lista(l);
//	distruge_tranzactie(tr2);
//}


void test_copiere_lista() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	adauga(l, creeaza_tranzactie(25, 200, "intrare", "transfer1"));
	adauga(l, creeaza_tranzactie(25, 201, "intrare", "transfer2"));
	MyList* l2 = copiere_lista(l, copiaza_tranzactie);

	assert(size(l2) == 2);

	int i = 0;
	int nr = size(l);

	while (i < nr) {
		Tranzactie* tr1 = get(l, i);
		Tranzactie* tr2 = get(l2, i);
		if (tr1->zi == tr2->zi && tr1->suma == tr2->suma)
			i++;
	}

	assert(i!=size(l)-1);
	distruge_lista(l);
	distruge_lista(l2);

}

void test_asigura_capacitate() {
	MyList* l = creeaza_lista(distruge_tranzactie);
	for (int i = 0; i < 10; i++)
		adauga(l, creeaza_tranzactie(11, 1, "iesire", "ok"));
	asigura_capacitate(l);
	assert(size(l) == 10);
	distruge_lista(l);
}

void testRemoveLast() {
	MyList* list_tr = creeaza_lista(distruge_tranzactie);
	adauga(list_tr, creeaza_tranzactie(25, 200, "intrare", "transfer1"));
	adauga(list_tr, creeaza_tranzactie(25, 201, "intrare", "transfer2"));

	assert(size(list_tr) == 2);

	Tranzactie* el = removeLast(list_tr);
	assert(size(list_tr) == 1);
	distruge_tranzactie(el);

	el = removeLast(list_tr);
	assert(size(list_tr) == 0);
	distruge_tranzactie(el);

	distruge_lista(list_tr);
}
