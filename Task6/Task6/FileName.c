#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct Brutarie Brutarie;
typedef struct Nod Nod;
typedef struct NodSimplu NodSimplu;
struct Brutarie {
	char* nume;
	int nrPaini;
	float* pretPaine;
	char locatie[30];
};
struct NodSimplu {
	struct Brutarie brutarie;
	NodSimplu* next;
};
struct Nod {
	struct Brutarie brutarie;
	Nod* prev;
	Nod* next;
};
void afisareBrutarie(struct Brutarie brutarie) {
	printf("\nNume:%-35s", brutarie.nume);
	printf("Locatie: %-20s", brutarie.locatie);
	printf("Nr Paini:%-4d", brutarie.nrPaini);
	printf("Paini:");
	for (int i = 0; i < brutarie.nrPaini; i++) {
		printf("%-4.2f,", brutarie.pretPaine[i]);
	}
	
}
void freeBrutarie(struct Brutarie* brutarie) {
	if (brutarie->nume != NULL)
		free(brutarie->nume);
	if (brutarie->nrPaini != 0 && brutarie->pretPaine != NULL)
		free(brutarie->pretPaine);
}
void afisareListaDublaInlatuita(Nod* head) {
	if (head == NULL) {
		printf("Lista goala\n");
	}
	else
		while (head != NULL) {
			afisareBrutarie(head->brutarie);
			head = head->next;
		}
}
void afisareListaSimpla(NodSimplu* head) {
	if (head == NULL) {
		printf("Lista goala\n");
	}
	else
		while (head != NULL) {
			afisareBrutarie(head->brutarie);
			head = head->next;
		}
}
void inserareLaSfarsit(Nod** head, Brutarie brutarie) {
	if ((*head) == NULL) {
		(*head) = malloc(sizeof(Nod));
		(*head)->brutarie = brutarie;
		(*head)->prev = NULL;
		(*head)->next = NULL;
	}
	else {
		Nod* nou = malloc(sizeof(Nod));
		nou->brutarie = brutarie;

		Nod* ultim = *head;
		while (ultim->next != NULL) {
			ultim = ultim->next;
		}
		ultim->next = nou;
		nou->prev = ultim;
		nou->next = NULL;
	}
}
void stergeNod(Nod ** nod) {
	freeBrutarie(&((*nod)->brutarie));
	free(*nod);
	(*nod) = NULL;
}
void stergeNodLista(Nod** head,int index) {
	int count = 1;
	Nod* nod = *head;
	if (count == index) {
		*head = nod->next;
		if (*head != NULL) {
			(*head)->prev = NULL;
		}
		stergeNod(&nod);
	} 
	else {
		
		while (nod->next != NULL) {
			if (count == index) {
				Nod* stersul = nod;
				nod = nod->prev;
				nod->next = nod->next->next;
				nod = nod->next->next;
				nod->prev = nod->prev->prev;
				stergeNod(&stersul);
				break;
			}
			count++;
			nod = nod->next;
		}
	}
}
//dupa nr paini
void inserareSortata(Nod** head,Brutarie brutarie) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->brutarie = brutarie;
	nou->next = NULL;
	nou->prev = NULL;

	if (*head == NULL || brutarie.nrPaini < (*head)->brutarie.nrPaini) {
		nou->next = *head;
		if (*head != NULL) {
			(*head)->prev = nou;
		}
		*head = nou;
		return;
	}

	Nod* iterator = *head;
	while (iterator->next != NULL && brutarie.nrPaini > iterator->next->brutarie.nrPaini) {
		iterator = iterator->next;
	}

	nou->next = iterator->next;
	nou->prev = iterator;
	if (iterator->next != NULL) {
		iterator->next->prev = nou;
	}
	iterator->next = nou;
}
void citireDinFisier(Nod** head,const char* numefisier) {
	if (numefisier != NULL && strlen(numefisier) > 0)
	{
		FILE* f = fopen(numefisier, "r");
		if (f != NULL) {
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token = strtok(buffer, delimitator);
				struct Brutarie brutarie;
				brutarie.nume = (char*)malloc(strlen(token) + 1);
				strcpy(brutarie.nume, token);
				token = strtok(NULL, delimitator);
				brutarie.nrPaini = atoi(token);
				token = strtok(NULL, delimitator);
				brutarie.pretPaine = (float*)malloc(brutarie.nrPaini * sizeof(float));
				for (int i = 0; i < brutarie.nrPaini; i++) {
					brutarie.pretPaine[i] = atof(token);
					token = strtok(NULL, delimitator);
				}
				strcpy(brutarie.locatie, token);
				inserareLaSfarsit(head, brutarie);
			}
			fclose(f);
		}
	}
}

void afisareDescrescatoareLista(Nod* head) {
	if (head == NULL) {
		printf("Lista goala!");
		return;
	}
	while (head->next != NULL) {
		head = head->next;
	}
	while (head != NULL) {
		afisareBrutarie(head->brutarie);
		head = head->prev;
	}
}
Brutarie atribuireBrutarie(Brutarie brutarie) {
	Brutarie copie;
	copie.nume = malloc(strlen(brutarie.nume) + 1);
	strcpy(copie.nume,brutarie.nume);
	copie.nrPaini = brutarie.nrPaini;
	if (copie.nrPaini != 0) {
		copie.pretPaine = malloc(copie.nrPaini* sizeof(float));
		for (int i = 0; i < copie.nrPaini; i++) {
			copie.pretPaine[i] = brutarie.pretPaine[i];
		}
	}
	strcpy(copie.locatie,brutarie.locatie);
	return copie;
}

void insereazaListaSimpla(NodSimplu** head,Brutarie brutarie) {
	NodSimplu* nou = malloc(sizeof(NodSimplu));
	nou->brutarie = atribuireBrutarie(brutarie);
	nou->next = NULL;
	if (*head == NULL) {
		*head = nou;
	}
	else {
		NodSimplu* it = *head;
		while (it->next != NULL) {
			it = it->next;
		}
		it->next = nou;
	}
}

NodSimplu* inserareFiltrata(Nod* head,int minimPaini) {
	NodSimplu* nod = NULL;

	while (head != NULL) {
		if (head->brutarie.nrPaini >= minimPaini) {
			insereazaListaSimpla(&nod, head->brutarie);
		}
		head = head->next;
	}
	return nod;
}

void interchimbare(Nod* head,int index1,int index2) {
	int maxim = index1 > index2 ? index1 : index2;
	int min = index1 > index2 ? index2 : index1;
	
	Nod* indexNod1 = NULL;
	Nod* indexNod2 = NULL;
	for (int i = 0; i < maxim && head != NULL; i++) {
		if (i == min) {
			indexNod1 = head;
		}
		head = head->next;
	}
	indexNod2 = head;
	if (indexNod1 != NULL && indexNod2 != NULL) {
		struct Brutarie aux = indexNod1->brutarie;
		indexNod1->brutarie = indexNod2->brutarie;
		indexNod2->brutarie = aux;
	}
}
void main() {
	Nod* head = NULL;
	citireDinFisier(&head,"brutarie.txt");
	//printf("%p", head);
	afisareListaDublaInlatuita(head);
	stergeNodLista(&head, 2);
	printf("\n");
	afisareListaDublaInlatuita(head);
	struct Brutarie brutarie1 = { "Brutarie1", 3, (float[]) { 2.5, 3.0, 2.0 }, "Strada X" };
	struct Brutarie brutarie2 = { "Brutarie2", 2, (float[]) { 1.5, 2.0 }, "Strada Y" };
	struct Brutarie brutarie3 = { "Brutarie3", 1, (float[]) { 2.0 }, "Strada z" };

	Nod* headSortat = NULL;
	inserareSortata(&headSortat, brutarie1);
	inserareSortata(&headSortat, brutarie2);
	inserareSortata(&headSortat, brutarie3);
	printf("\n");
	//sortare normala
	afisareListaDublaInlatuita(headSortat);
	printf("\n");
	//sortare inversa
	afisareDescrescatoareLista(headSortat);

	printf("\n");
	NodSimplu* headListaSimpla = inserareFiltrata(head,4);
	afisareListaSimpla(headListaSimpla);


	printf("\n");
	afisareListaDublaInlatuita(head);
	interchimbare(head, 0, 3);
	printf("\n");
	afisareListaDublaInlatuita(head);
}