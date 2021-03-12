#include "tranzactie.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

Tranzactie* creeaza_tranzactie(int zi, float suma, char* tip, char* descriere) {
	Tranzactie* rez = malloc(sizeof(Tranzactie));
	rez->zi = zi;
	rez->suma = suma;

	size_t dim = strlen(tip) + 1;
	rez->tip = malloc(sizeof(char) * dim);
	strcpy_s(rez->tip, dim, tip);

	dim = strlen(descriere) + 1;
	rez->descriere = malloc(sizeof(char) * dim);
	strcpy_s(rez->descriere, dim, descriere);

	return rez;
}

void distruge_tranzactie(Tranzactie* tr) {
	tr->zi = -1;
	tr->suma = -1;
	free(tr->tip);
	free(tr->descriere);
	free(tr);
}

Tranzactie* copiaza_tranzactie(Tranzactie* tr) {
	return creeaza_tranzactie(tr->zi, tr->suma, tr->tip, tr->descriere);
}


void test_creeaza_tranzactie() {
	Tranzactie* tr = creeaza_tranzactie(1, 12, "intrare", "ok");
	assert(tr->zi == 1);
	assert(tr->suma == 12);
	assert(strcmp(tr->tip, "intrare") == 0);
	assert(strcmp(tr->descriere, "ok") == 0);

	distruge_tranzactie(tr);
}

void test_distruge_tranzactie() {
	Tranzactie* tr = creeaza_tranzactie(1, 12, "intrare", "ok");
	distruge_tranzactie(tr);
}

void test_copiaza_tranzactie() {
	Tranzactie* rez;
	Tranzactie* tr = creeaza_tranzactie(1, 12, "intrare", "ok");
	rez = copiaza_tranzactie(tr);
	assert(rez->zi == 1);
	assert(rez->suma == 12);
	assert(strcmp(rez->tip, "intrare") == 0);
	assert(strcmp(rez->descriere, "ok") == 0);

	distruge_tranzactie(tr);
	distruge_tranzactie(rez);
}
