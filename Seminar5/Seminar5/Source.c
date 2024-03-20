#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Cafenea Cafenea;
typedef struct Nod Nod;

struct Cafenea{
	char* nume;
	int nrLocuri;
	float suprafata;
};
struct Nod {
	Cafenea info;
	Nod* next;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
	Cafenea cafenea;
	cafenea.nume = (char*) malloc(strlen(nume) + 1);
	strcpy(cafenea.nume, nume);
	cafenea.nrLocuri = nrLocuri;
	cafenea.suprafata = suprafata;
	return cafenea;
}
void afisareFunctieCafenea(Cafenea cafea) {
	printf("\n");
	printf("\nNume=%s", cafea.nume);
	printf("\nNrScaune=%d", cafea.nrLocuri);
	printf("\nSuprafata=%.2f", cafea.suprafata);

}
Nod* inserareLaInceput(Nod* cap, Cafenea cafenea) {
	Nod* nou = (malloc)(sizeof(Nod));
	nou->info = initializareCafenea(cafenea.nume, cafenea.nrLocuri, cafenea.suprafata);
	nou->next = cap;
	return nou;
}
void afisareLista(Nod* head) {
	if (head == NULL) {
		printf("\nLista goala");
	}
	else {
		while (head != NULL) {
			afisareFunctieCafenea(head->info);
			head = head->next;
		}
	}
}
//numele cafenelei care are densitatea cea mai mica
char* numeCafeneaDensitateMinima(Nod* cap) {	
	if (cap != NULL) {
		float densitateMinima = cap->info.nrLocuri 
			/ cap->info.suprafata;
		Nod* nod = cap;
		cap = cap->next;
		while (cap != NULL) {	
			if (cap->info.nrLocuri
				/ cap->info.suprafata < densitateMinima) {
				densitateMinima = cap->info.nrLocuri
					/ cap->info.suprafata;
				nod = cap;
			}
			cap = cap->next;			
		}
		char* nume = malloc(strlen(nod->info.nume) + 1);
		strcpy(nume, nod->info.nume);
		return nume;
	}
	return NULL;
}
void stergeLista(Nod** nod) {
	while (*nod != NULL) {
		Nod* aux = *nod;
		*nod = (*nod)->next;
		free(aux->info.nume);
		free(aux);
		
	}
	*nod = NULL;
}
void inserareFinal(Nod** cap,Cafenea cafea) {
	if ((*cap) == NULL) {
		(*cap) = inserareLaInceput(*cap,cafea);
	}
	else {
		Nod* curent = (*cap);
		while (curent->next != NULL) {
			curent = curent->next;
		}
		Nod* nod = malloc(sizeof(Nod));
		nod->info = initializareCafenea(cafea.nume, cafea.nrLocuri,
			cafea.suprafata);
		nod->next = NULL;
		curent->next = nod;
	}
}
void main() {
	Cafenea c1 = initializareCafenea("Matei", 23, 12.45);
	Cafenea c2 = initializareCafenea("Luca", 20, 10.45);
	Cafenea c3 = initializareCafenea("StarBucks", 28, 112.45);
	Nod* cap = NULL;
	cap = inserareLaInceput(cap, c1);
	cap = inserareLaInceput(cap, c2);
	cap = inserareLaInceput(cap, c3);
	afisareLista(cap);
	char* NumeMinim = numeCafeneaDensitateMinima(cap);
	printf("\nMinimul este:%s", NumeMinim);
	inserareFinal(&cap, c3);
	stergeLista(&cap);
	afisareLista(cap);

	free(c1.nume);
	c1.nume = NULL;
	free(c2.nume);
	c2.nume = NULL;
	free(c3.nume);
	c3.nume = NULL;
}