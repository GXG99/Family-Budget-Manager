#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "tranzactie.h"
#include "MyList.h"
#include "service.h"
#include <stdio.h>


void ui_adauga(TrSrv* srv) {
	printf("Zi:");
	int zi = 0;
	scanf_s("%d", &zi);
	printf("Suma:");
	float suma = 0;
	scanf_s("%f", &suma);
	printf("Tip:");
	char tip[30];
	scanf_s("%s", tip, sizeof(tip));
	printf("Descriere:");
	char descriere[30];
	scanf_s("%s", descriere, sizeof(descriere));
	int eroare = srv_adauga(srv, zi, suma, tip, descriere);
	if (eroare != 0)
		printf("Tranzactie invalida!\n");
	else
		printf("Tranzactie adaugata!\n");

}


void ui_modifica(TrSrv* srv) {
	printf("Zi:");
	int zi = 0;
	scanf_s("%d", &zi);
	printf("Suma noua:");
	float suma = 0;
	scanf_s("%f", &suma);
	printf("Tip:");
	char tip[30];
	scanf_s("%s", tip, sizeof(tip));
	printf("Descriere noua:");
	char descriere[30];
	scanf_s("%s", descriere, sizeof(descriere));
	srv_modifica(srv, zi, suma, tip, descriere);
	printf("Tranzactie modificata!\n");
}


void ui_printAll(MyList* l) {
	if (size(l) == 0)
		printf("Lista vida!\n");
	else {
		printf("Tranzactii:\n");
		for (int i = 0; i < size(l); i++) {
			Tranzactie* tr = get(l, i);
			if (tr->zi != -1 && tr->suma != -1) {
				printf("Zi:%d Suma:%f Tip:%s Descriere:%s", tr->zi, tr->suma, tr->tip, tr->descriere);
				printf("\n");
			}
		}
	}
}


void ui_filtrare2(TrSrv* srv) {
	printf("Tip:");
	char tip[30];
	scanf_s("%s", tip, sizeof(tip));
	MyList* rez = getFiltered(srv, tip);
	ui_printAll(rez);
	distruge_lista(rez);
}


void ui_ordonare1(TrSrv* srv) {
	MyList* rez = srv_ordonare_dupa_suma(srv);
	ui_printAll(rez);
	distruge_lista(rez);
}


void ui_ordonare2(TrSrv* srv) {
	MyList* rez = srv_ordonare_dupa_zi(srv);
	ui_printAll(rez);
	distruge_lista(rez);
}


void run() {
	TrSrv srv = creeaza_srv();
	int ruleaza = 1;
	while (ruleaza) {
		printf(
			"1 Adauga\n2 Undo\n3 Redo\n4 Tipareste\n0 Exit\n5 Modifica\n6 Filtrare tip\n7 Ordonare crescator dupa suma\n8 Ordonare crescator dupa zi\nComanda:");
		int cmd = 0;
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			ui_adauga(&srv);
			break;
		case 2:
			undo(&srv);
			break;
		case 3:
			redo(&srv);
			break;
		case 4:
			ui_printAll(srv.toate_tr);
			break;
		case 5:
			ui_modifica(&srv);
			break;
		case 6:
			ui_filtrare2(&srv);
			break;
		case 7:
			ui_ordonare1(&srv);
			break;
		case 8:
			ui_ordonare2(&srv);
			break;
		case 0:
			ruleaza = 0;
			break;
		default:
			printf("Comanda invalida!\n");
		}
	}
	destroy_srv(&srv);
}


void testAll() {
	test_creeaza_tranzactie();
	test_distruge_tranzactie();
	test_copiaza_tranzactie();
	test_creeaza_lista();
	test_distruge_lista();
	test_get();
	test_size();
	test_adauga();
	test_copiere_lista();
	test_srv_adauga();
	test_modifica();
	test_srv_modifica();
	test_ordonare1();
	test_ordonare2();
	test_cmpSuma();
	test_cmpZi();
	testUndo();
	test_filtered();
	testRemoveLast();
	test_asigura_capacitate();
}


int main() {
	testAll();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}
