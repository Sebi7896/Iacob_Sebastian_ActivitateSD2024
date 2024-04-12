#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Galerie Galerie;
typedef struct Nod Nod;

struct Galerie {
	int cod; //se face hashcode
	char* nume;
	float pretIntrare;
};
struct Nod {
	Galerie galerie;
	Nod* next;
};

typedef struct Hashtable HashTable;
struct Hashtable {
	Nod** vector;//vectori de pointeri
	int dim;
	//int dimTotala
};

Galerie initGalerie(int cod, const char* nume, float pretIntrare) {
	Galerie galerie;
	galerie.cod = cod;
	galerie.nume = malloc(strlen(nume) + 1);
	strcpy(galerie.nume, nume);
	galerie.pretIntrare = pretIntrare;
	return galerie;
}

HashTable initializareHashTable(dim) {
	HashTable hash;
	hash.dim = dim;
	hash.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		hash.vector[i] = NULL;
	}
	return hash;
}

int calculHash(int cod,const char* nume,int dim) {
	//returneaza pozitia unde treb inserat
	//suma nr din ascii impartit la cod
	if (dim > 0) {
		int rez = cod * strlen(nume);
		return rez % dim;
	}
	return -1;
}
void inserareInLista(Nod** head,Galerie galerie) {
	Nod* nou = malloc(sizeof(Nod));
	nou->galerie = galerie;
	nou->next = NULL;
	if (*head) {
		Nod* nod = *head;
		while (nod->next != NULL) {
			nod = nod->next;
		}
		nod->next = nou;
	}
	else {
		*head = nou;
	}
	

}
void inserareGalerieInTabela(HashTable hash,Galerie galerie) {
	if (hash.dim > 0) {
		int pozitie = calculHash(galerie.cod, galerie.nume, hash.dim);
		if (hash.vector[pozitie] != NULL) { //situatia de conflict
			inserareInLista(&(hash.vector[pozitie]), galerie);
		}
		else {
			//pune 
			inserareInLista(&(hash.vector[pozitie]), galerie);//intra in else
		}
	}
}

void afisareGalerie(Galerie g) {
	printf("%d. Intrarea la Galeria %s costa %.2f\n", g.cod, g.nume, g.pretIntrare);
}
void afisareListaGaleri(Nod* head) {
	while (head != NULL) {
		afisareGalerie(head->galerie);
		head = head->next;
	}
}
void afisareTabela(HashTable hash) {
	for (int i = 0; i < hash.dim; i++) {
		if (hash.vector[i] != NULL) {
			printf("CLusterul:%d\n", i + 1);
			afisareListaGaleri(hash.vector[i]);
		}
	}
}

Galerie cautaGalerieDupaCheie(int cod,const char* nume,HashTable tabela) {
	int pozitie = calculHash(cod, nume, tabela.dim);

	if (pozitie >= 0 && pozitie < tabela.dim) {
		Nod* p = tabela.vector[pozitie];
		while (p != NULL && p->galerie.cod != cod
			&& strcmp(p->galerie.nume, nume) != 0) {
			p = p->next;
		}
		if (p) {
			//shallow
			return p->galerie;
		}
		else {
			return initGalerie(-1, "-", -1);
		}
	}
}
int main() {
	Galerie g1 = initGalerie(1,"galeriile Orizont",10);
	Galerie g2 = initGalerie(2,"Cercul armatei",6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Geologie", 17);
	Galerie g6 = initGalerie(6, "Istorie", 20);

	HashTable hash = initializareHashTable(5);

	inserareGalerieInTabela(hash, g1);
	inserareGalerieInTabela(hash, g2);
	inserareGalerieInTabela(hash, g3);
	inserareGalerieInTabela(hash, g4);
	inserareGalerieInTabela(hash, g5);
	inserareGalerieInTabela(hash, g6);


	afisareTabela(hash);

	Galerie g = cautaGalerieDupaCheie(3, "Louvre", hash);
	printf("Cautare:\n");
	afisareGalerie(g);
	return 0;
}