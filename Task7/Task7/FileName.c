#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef struct Cladire Cladire;
struct Cladire {
	int id;
	char* nume;
	int an;
};
typedef struct Nod Nod;
struct Nod {
	Cladire cladire;
	Nod* next;
};
typedef struct HashTable HashTable;
struct HashTable {
	Nod** vector;
	int dim;
	//int dimTotala
};
Cladire initializareCladire(int id,const char* nume,int an) {
	Cladire cladire;
	cladire.id = id;
	cladire.nume = malloc(strlen(nume) + 1);
	strcpy(cladire.nume, nume);
	cladire.an = an;
	return cladire;
}
void afisareCladire(Cladire cladire) {
	printf("Cladirea: %-2s,an:%-4d,id:%d\n", cladire.nume,cladire.an,cladire.id);
}
HashTable initializareHash(dim) {
	HashTable hash;
	hash.dim = dim;
	hash.vector = malloc(dim * sizeof(Nod*));
	for (int i = 0; i < dim; i++) {
		hash.vector[i] = NULL;
	}
	return hash;
}
int calculHash(int an,int dim) {
	if (dim > 0) {
		return an % dim;
	}
	return -1;
}

void inserareInLista(Nod** head, Cladire cladire) {
	Nod* nod = malloc(sizeof(Nod));
	nod->cladire = cladire;
	nod->next = NULL;
	if (*head == NULL) {	
		*head = nod;
	}
	else {
		Nod* temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nod;
	}
}
void inserareCladireInTabela(HashTable hash,Cladire cladire) {
	if (hash.dim > 0) {
		int pozitie = calculHash(cladire.an, hash.dim);
		//aici va fi o lista
		inserareInLista(&(hash.vector[pozitie]), cladire);
	}
}
void afisareLista(Nod* head) {
	while (head != NULL) {
		afisareCladire(head->cladire);
		head = head->next;
	}
}
void afisareHashTable(HashTable head) {
	if (head.dim != 0) {
		for (int i = 0; i < head.dim; i++ ) {
			printf("CLusterul:%d\n", i + 1);
			afisareLista(head.vector[i]);
		}
	}
}
void afisareListaAni(HashTable hash,int an) {
	if (hash.dim > 0) {
		int pozitie = calculHash(an,hash.dim); 
		Nod* temp = hash.vector[pozitie];
		if (hash.vector[pozitie] == NULL) {
			printf("Nu exista");
		}
		else {
			printf("Anul %d\n", an);
			while(temp != NULL) {
				if (temp->cladire.an == an) {
					afisareCladire(temp->cladire);
				}	
				temp = temp->next;
			}
		}
	}
}
void stergeCladire(HashTable hash, int id, int an) {
	if (hash.dim != NULL) {
		int pozitie = calculHash(an, hash.dim);
		Nod* nod = hash.vector[pozitie];
		if (nod->cladire.id == id) {
			hash.vector[pozitie] = nod->next;
			free(nod);
		}
		else {
			while (nod->next != NULL && nod->next->cladire.id != id) {
				nod = nod->next;
			}
			Nod* sters = nod->next;
			nod->next = nod->next->next;
			free(sters);
		}
		
	}
}
void stergeCladireDupaID(HashTable hash,int id) {
	if (hash.dim != 0) {
		//caut secvential
		for (int i = 0; i < hash.dim; i++) {
			Nod* nod = hash.vector[i];
			if (nod->cladire.id == id) {
				hash.vector[i] = nod->next;
				free(nod);
				i = hash.dim + 1;
				break;
			}
			while (nod->next != NULL && nod->next->cladire.id != id) {
				nod = nod->next;
			}
			
			Nod* sters = nod->next;
			if (sters != NULL) {
				nod->next = nod->next->next;
				free(sters);
				i = hash.dim + 1;
			}		
		}
	}

}

Cladire* salvareVector(HashTable hash,int an,int* dimVector) {
	*dimVector = 0;
	if (hash.dim != 0) {
		int pozitie = calculHash(an, hash.dim);
		int nr = 0;
		Nod* nod = hash.vector[pozitie];
		while (nod != NULL) {
			if (nod->cladire.an == an) {
				(*dimVector)++;
			}
			nod = nod->next;
		}
		Cladire* cladiri = malloc((*dimVector) * sizeof(Cladire));
		nod = hash.vector[pozitie];
		int k = 0;
		while (nod != NULL) {
			if (nod->cladire.an == an) {
				//deep
				cladiri[k].nume = malloc(strlen(nod->cladire.nume) + 1);
				strcpy(cladiri[k].nume, nod->cladire.nume);
				cladiri[k].an = nod->cladire.an;
				cladiri[k].id = nod->cladire.id;
				k++;
			}
			nod = nod->next;
		}
		return cladiri;
	}
	return NULL;
}
void modificareAnConstructie(HashTable hash,int id,int anVechi,int anNou) {
	if (hash.dim != NULL) {
		int pozitie = calculHash(anVechi, hash.dim);
		Nod* nod = hash.vector[pozitie];
		while (nod->next != NULL && nod->next->cladire.id != id) {
			nod = nod->next;
		}
		nod->cladire.an = anNou;
	}

}

void main() {
	Cladire c1 = initializareCladire(1, "Eu", 2020);
	Cladire c2 = initializareCladire(2, "Tu", 2010);
	Cladire c3 = initializareCladire(3, "SIuii", 2019);
	Cladire c4 = initializareCladire(4, "LElele", 2006);
	Cladire c5 = initializareCladire(5, "sdac", 2005);
	Cladire c6 = initializareCladire(6, " gregs", 2004);
	Cladire c7 = initializareCladire(7, "sadwq", 2003);

	afisareCladire(c1);
	HashTable hash = initializareHash(6);

	inserareCladireInTabela(hash, c1);
	inserareCladireInTabela(hash, c2);
	inserareCladireInTabela(hash, c3);
	inserareCladireInTabela(hash, c4);
	inserareCladireInTabela(hash, c5);
	inserareCladireInTabela(hash, c6);
	inserareCladireInTabela(hash, c7);
	//afisareHashTable(hash);
	//afisareListaAni(hash,2010);
	//printf("-----");
	//afisareHashTable(hash);
	//stergeCladire(hash, 4, 2006);
	//printf("-----");
	//afisareHashTable(hash);
	//stergeCladire(hash, 6, 2004);
	//printf("-----");
	//afisareHashTable(hash);
	printf("-----");
	afisareHashTable(hash);
	stergeCladireDupaID(hash, 4);
	printf("-----");
	afisareHashTable(hash);
	stergeCladireDupaID(hash, 6);
	printf("-----");
	afisareHashTable(hash);

	//mult mai eficient dupa id si an

	//6
	int dim = 0;
	printf("-----");
	Cladire* cladiri = salvareVector(hash, 2019, &dim);
	for (int i = 0; i < dim; i++) {
		afisareCladire(cladiri[i]);
	}

	printf("-------");
	afisareHashTable(hash);
	printf("-------");
	modificareAnConstructie(hash, 2, 2010, 2024);
	afisareHashTable(hash);

}