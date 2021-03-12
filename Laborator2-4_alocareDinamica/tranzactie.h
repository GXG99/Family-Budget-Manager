#pragma once

typedef struct {
	int zi;
	float suma;
	char* tip;
	char* descriere;
} Tranzactie;

/*
	functia creeaza o noua trazactie
	input: l-lista de tranzactii
			zi-numar natural care apartine intervalului [1,31]
			suma-numar real pozitiv
			tip-string care poate fi intrare sau iesire
			descriere-string
	output: o tranzactie
*/
Tranzactie* creeaza_tranzactie(int zi, float suma, char* tip, char* descriere);

/*
	functia elibereaza memoria ocupata de o tranzactie
	input: o tranzactie
	output:-
*/
void distruge_tranzactie(Tranzactie* tr);

/*
	functia copiaza o tranzactie
	input: o tranzactie
	output:o copie a tranzactiei date
*/
Tranzactie* copiaza_tranzactie(Tranzactie* tr);

/*
	functia valideaza o tranzactie sa fie in conformitate cu cerintele problemei 
	returneaza 0 daca tranzactia este valida
*/
int valideaza_tranzactie(Tranzactie* tr);

void test_creeaza_tranzactie();
void test_distruge_tranzactie();
void test_copiaza_tranzactie();