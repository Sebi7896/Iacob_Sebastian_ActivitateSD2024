#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Cafenea Cafenea;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Cafenea {
	char* nume;
	int nrLocuri;
	float suprafata;
};
struct Nod {
	struct Cafenea cafenea;
	Nod* anterior;
	Nod* urmator;
};
struct ListaDubla {
	Nod* cap;
	Nod* coada;
};
Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
	Cafenea cafenea;
	cafenea.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(cafenea.nume, nume);
	cafenea.nrLocuri = nrLocuri;
	cafenea.suprafata = suprafata;
	return cafenea;
}
void afisareFunctieCafenea(Cafenea cafea) {
	printf("\nNume=%-10s NrScaune=%-4d Suprafata=%.2f", cafea.nume, cafea.nrLocuri, cafea.suprafata);
}

void inserareLaInceputLista(ListaDubla* lista,Cafenea cafenea) {
	Nod* nou = malloc(sizeof(Nod));
	nou->cafenea = cafenea;
	nou->anterior = NULL;
	nou->urmator = lista->cap;
	if (lista->cap != NULL) {
		lista->cap->anterior = nou;
	}
	else {
		lista->cap = nou;
		lista->coada = nou;
	}
	lista->cap = nou;
		
}
ListaDubla stergeCafeneaUnica(ListaDubla listaDubla,const char*nume) {
	Nod* nod = listaDubla.cap;
	while (nod != NULL && strcmp(nod->cafenea.nume, nume) != 0) {
		nod = nod->urmator;
	}
	if (nod != NULL) {
		if (nod->urmator == NULL && nod->anterior == NULL) {
			listaDubla.cap = NULL;
			listaDubla.coada = NULL;
		}
		else {
			if (nod->urmator == NULL) {
				nod->anterior->urmator = NULL;
				listaDubla.coada = nod->anterior;
			}
			else {
				if (nod->anterior == NULL) {
					nod->urmator->anterior = NULL;
					listaDubla.cap = nod->urmator;
				}
				else {
					nod->urmator->anterior = nod->anterior;
					nod->anterior->urmator = nod->urmator;
				}
			}
		}
		free(nod->cafenea.nume);
		free(nod);
		
		}
	return listaDubla;
}
int nrTotal(ListaDubla listaDubla) {
	if (listaDubla.cap == NULL) {
		return 0;
	}
	int nrTotal = 0;
	Nod* temp = listaDubla.coada;
	while (temp != NULL) {
		nrTotal += temp->cafenea.nrLocuri;
		temp = temp->anterior;
	}
	return nrTotal;
}
void afisareLista(ListaDubla listaDubla) {
	if (listaDubla.cap == NULL) {
		printf("Lista Goala");
	}
	else {
		while (listaDubla.cap != NULL) {
			afisareFunctieCafenea(listaDubla.cap->cafenea);
			listaDubla.cap = listaDubla.cap->urmator;
		}
		printf("\n");
	}
}

ListaDubla freeLista(ListaDubla listaDubla) {
	Nod* nod = listaDubla.cap;
	while (nod != NULL) {
		Nod* next = nod->urmator; 
		free(nod->cafenea.nume);
		free(nod);
		nod = next;
	}
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	return listaDubla;
}
void afisareDinCoada(ListaDubla lista) {
	Nod* nod = lista.coada;
	while (nod != NULL) {
		afisareFunctieCafenea(nod->cafenea);
		nod = nod->anterior;
	}
	printf("\n");
}
void main() {
	Cafenea c1 = initializareCafenea("Matei", 23, 12.45);
	Cafenea c2 = initializareCafenea("Luca", 20, 10.45);
	Cafenea c3 = initializareCafenea("StarBucks", 28, 112.45);
	Cafenea c4 = initializareCafenea("Yacobs", 20, 110.45);

	ListaDubla listaDubla;
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	inserareLaInceputLista(&listaDubla, c1);
	inserareLaInceputLista(&listaDubla, c2);
	inserareLaInceputLista(&listaDubla, c3);
	inserareLaInceputLista(&listaDubla, c4);

	afisareLista(listaDubla);
	listaDubla =stergeCafeneaUnica(listaDubla, "Luca");

	afisareLista(listaDubla);
	listaDubla = stergeCafeneaUnica(listaDubla, "Matei");

	afisareLista(listaDubla);
	printf("Nr total locuri:%d", nrTotal(listaDubla));
	afisareDinCoada(listaDubla);
	listaDubla = freeLista(listaDubla);
	afisareDinCoada(listaDubla);
}
