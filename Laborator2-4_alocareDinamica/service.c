#include "service.h"
#include "sort.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>


TrSrv creeaza_srv() {
	TrSrv rez;
	rez.toate_tr = creeaza_lista(distruge_tranzactie);
	rez.undoList = creeaza_lista(distruge_lista);
	rez.redoList = creeaza_lista(distruge_lista);
	return rez;
}


void destroy_srv(TrSrv* srv) {
	distruge_lista(srv->toate_tr);
	distruge_lista(srv->undoList);
	distruge_lista(srv->redoList);
}


int srv_adauga(TrSrv* srv, int zi, float suma, char* tip, char* descriere) {
	Tranzactie* tr = creeaza_tranzactie(zi, suma, tip, descriere);
	MyList* toUndo = copiere_lista(srv->toate_tr, copiaza_tranzactie);
	adauga(srv->toate_tr, tr);
	adauga(srv->undoList, toUndo);
	return 0; //adaugarea a avut loc
}


MyList* getFiltered(TrSrv* srv, char* substringTip) {
	MyList* rez = creeaza_lista(distruge_tranzactie);
	for (int i = 0; i < size(srv->toate_tr); i++) {
		Tranzactie* tr = get(srv->toate_tr, i);
		if (strstr(tr->tip, substringTip) != NULL) {
			adauga(rez, copiaza_tranzactie(tr));
		}
	}
	return rez;
}


void test_filtered() {
	TrSrv srv = creeaza_srv();

	srv_adauga(&srv, 11, 200, "intrare", "b");
	srv_adauga(&srv, 11, 201, "iesire", "c");

	MyList* temp = getFiltered(&srv, "iesire");
	assert(size(temp) == 1);
	distruge_lista(temp);
	destroy_srv(&srv);
}


int undo(TrSrv* srv) {
	if (size(srv->undoList) == 0) {
		return 1;
	}

	MyList* toRedo = copiere_lista(srv->toate_tr, copiaza_tranzactie);
	adauga(srv->redoList, toRedo);

	MyList* l = removeLast(srv->undoList);
	distruge_lista(srv->toate_tr);
	srv->toate_tr = l;
	return 0;
}


int redo(TrSrv* srv) {
	if (size(srv->redoList) == 0) {
		return 1;
	}

	MyList* l = removeLast(srv->redoList);
	MyList* toUndo = copiere_lista(srv->toate_tr, copiaza_tranzactie);
	adauga(srv->undoList, toUndo);
	distruge_lista(srv->toate_tr);
	srv->toate_tr = l;
	return 0;
}


MyList* get_alltr(TrSrv* srv) {

	MyList* rez = creeaza_lista(distruge_tranzactie);
	for (int i = 0; i < size(srv->toate_tr); i++) {
		Tranzactie* tr = get(srv->toate_tr, i);
		adauga(rez, copiaza_tranzactie(tr));
	}
	return rez;
}

int srv_modifica(TrSrv* srv, int zi, float suma, char* tip, char* descriere) {
	Tranzactie* tr = creeaza_tranzactie(zi, suma, tip, descriere);
	modifica(srv->toate_tr, tr);
	return 0; //modificarea a avut loc 
}

int cmpSuma(Tranzactie* tr1, Tranzactie* tr2) {
	if (tr1->suma > tr2->suma)
		return 1;
	else if (tr1->suma < tr2->suma)
		return -1;
	else
		return 0;

}


int cmpZi(Tranzactie* tr1, Tranzactie* tr2) {
	if (tr1->zi > tr2->zi)
		return 1;
	else if (tr1->zi < tr2->zi)
		return -1;
	else
		return 0;
}


MyList* srv_ordonare_dupa_suma(TrSrv* srv) {
	MyList* rez = copiere_lista(srv->toate_tr, copiaza_tranzactie);
	sort(rez, cmpSuma);
	return rez;
}


MyList* srv_ordonare_dupa_zi(TrSrv* srv) {
	MyList* rez = copiere_lista(srv->toate_tr, copiaza_tranzactie);
	sort(rez, cmpZi);
	return rez;
}


void test_srv_adauga() {
	TrSrv srv = creeaza_srv();
	//incercam sa adaugam tranzactii invalide 
	srv_adauga(&srv, 25, 200, "intrare", "transfer1");
	assert(size(srv.toate_tr) == 1);

	destroy_srv(&srv);
}


void test_srv_modifica() {
	TrSrv srv = creeaza_srv();

	srv_adauga(&srv, 11, 200, "iesire", "b");
	srv_modifica(&srv, 11, 201, "iesire", "c");

	Tranzactie* tr = get(srv.toate_tr, 0);
	assert(tr->suma == 201);
	destroy_srv(&srv);
}


void test_ordonare1() {
	TrSrv srv = creeaza_srv();
	srv_adauga(&srv, 11, 200, "intrare", "b");
	srv_adauga(&srv, 21, 100, "iesire", "d");
	MyList* rez = srv_ordonare_dupa_suma(&srv);
	Tranzactie* tr1 = get(rez, 0);
	assert(tr1->suma==100);
	distruge_lista(rez);
	destroy_srv(&srv);
}


void test_ordonare2() {
	TrSrv srv = creeaza_srv();
	srv_adauga(&srv, 31, 200, "intrare", "b");
	srv_adauga(&srv, 21, 100, "iesire", "d");
	MyList* rez = srv_ordonare_dupa_zi(&srv);
	Tranzactie* tr1 = get(rez, 0);
	Tranzactie* tr2 = get(rez, 1);
	assert(tr1->zi < tr2->zi);
	distruge_lista(rez);
	destroy_srv(&srv);
}


void test_cmpSuma() {
	Tranzactie* tr1 = creeaza_tranzactie(11, 11, "iesire", "ok");
	Tranzactie* tr2 = creeaza_tranzactie(11, 110, "iesire", "ok");
	Tranzactie* tr3 = creeaza_tranzactie(11, 11, "iesire", "ok");
	assert(cmpSuma(tr1, tr2) == -1);
	assert(cmpSuma(tr1, tr3) == 0);
	assert(cmpSuma(tr2, tr3) == 1);
	distruge_tranzactie(tr1);
	distruge_tranzactie(tr2);
	distruge_tranzactie(tr3);
}


void test_cmpZi() {
	Tranzactie* tr1 = creeaza_tranzactie(11, 11, "iesire", "ok");
	Tranzactie* tr2 = creeaza_tranzactie(21, 110, "iesire", "ok");
	Tranzactie* tr3 = creeaza_tranzactie(11, 11, "iesire", "ok");
	assert(cmpZi(tr1, tr2) == -1);
	assert(cmpZi(tr1, tr3) == 0);
	assert(cmpZi(tr2, tr3) == 1);
	distruge_tranzactie(tr1);
	distruge_tranzactie(tr2);
	distruge_tranzactie(tr3);
}


void testUndo() {
	TrSrv srv = creeaza_srv();
	assert(redo(&srv) == 1);
	srv_adauga(&srv, 11, 11, "iesire", "ok");
	srv_adauga(&srv, 21, 110, "iesire", "ok");
	undo(&srv);
	MyList* l = get_alltr(&srv);
	assert(size(l) == 1);
	redo(&srv);
	assert(size(srv.toate_tr) == 2);
	distruge_lista(l);

	undo(&srv);
	l = get_alltr(&srv);
	assert(size(l) == 1);
	distruge_lista(l);

	undo(&srv);
	assert(undo(&srv) != 0);
	assert(undo(&srv) != 0);

	destroy_srv(&srv);
}
