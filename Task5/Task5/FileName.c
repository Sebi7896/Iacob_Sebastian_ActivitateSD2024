#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct Brutarie {
	char* nume;
	int nrPaini;
	float* pretPaine;
	char locatie[30];
};
struct Nod {
	struct Brutarie brutarie;
	struct Nod* next;
};
void adaugareLista(struct Nod** head, struct Brutarie brutarie) {
	struct Nod* nodNou = (struct Nod*)malloc(sizeof(struct Nod));
	nodNou->next = NULL;
	nodNou->brutarie = brutarie;
	if (*head == NULL) {
		*head = nodNou;
		return;
	}
	struct Nod* last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = nodNou;
}
void afisareBrutarie(struct Brutarie brutarie) {
	printf("\nNume:%s", brutarie.nume);
	printf("	Nr Paini:%d", brutarie.nrPaini);
	printf("	Paini:");
	for (int i = 0; i < brutarie.nrPaini; i++) {
		printf("%.2f,", brutarie.pretPaine[i]);
	}
	printf("	Locatie:%s\n", brutarie.locatie);
}

void citireDinFisier(struct Nod** head, const char* numefisier) {
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
				adaugareLista(head, brutarie);
			}
			fclose(f);
		}
	}
}
void freeBrutarie(struct Brutarie* brutarie) {
	if (brutarie->nume != NULL)
		free(brutarie->nume);
	if (brutarie->nrPaini != 0 && brutarie->pretPaine != NULL)
		free(brutarie->pretPaine);
}
void stergeNodIndex(struct Nod** head, int index) {
	if ((*head) != NULL) {
		struct Nod* temp = *head;
		if (index == 0) {
			freeBrutarie(&(*head)->brutarie);
			*head = temp->next;
			free(temp);
			return;
		}
		for (int i = 0; temp != NULL && i < index - 1; i++)
			temp = temp->next;
		if (temp == NULL || temp->next == NULL)
			return;
		struct Nod* next = temp->next->next;
		freeBrutarie(&(temp->next->brutarie));
		free(temp->next);
		temp->next = next;
	}

}
//criteriul
float mediePreturi(int nrPreturi, float* preturi) {
	if (nrPreturi == 0)
		return 0;
	float medie = 0;
	for (int i = 0; i < nrPreturi; i++) {
		medie += preturi[i];
	}
	return medie / nrPreturi;

}
void afisareLista(struct Nod* head) {

	if (head == NULL)
		printf("Lista Goala");
	else
		while (head != NULL) {
			afisareBrutarie(head->brutarie);
			printf("Media este:%.2f\n", mediePreturi(head->brutarie.nrPaini, head->brutarie.pretPaine));
			head = head->next;
		}
}
void adaugareSortata(struct Nod** head, struct Brutarie brutarie) {
	struct Nod* nod = (struct Nod*)malloc(sizeof(struct Nod));
	nod->brutarie = brutarie;
	if (*head == NULL || mediePreturi((*head)->brutarie.nrPaini,
		(*head)->brutarie.pretPaine) >= mediePreturi(nod->brutarie.nrPaini, nod->brutarie.pretPaine)) {
		nod->next = *head;
		*head = nod;
		return;
	}
	struct Nod* current = *head;
	while (current->next != NULL && mediePreturi(current->next->brutarie.nrPaini,
		current->next->brutarie.pretPaine) < mediePreturi(nod->brutarie.nrPaini, nod->brutarie.pretPaine)) {
		current = current->next;
	}

	nod->next = current->next;
	current->next = nod;

}
void interschimbareNoduri(struct Nod* head, int index1, int index2) {

	struct Nod* nod1 = NULL;
	struct Nod* nod2 = NULL;
	int maxim = index1 > index2 ? index1 : index2;
	int min = index1 > index2 ? index2 : index1;
	for (int index = 0; index < maxim && head != NULL; index++) {
		if (index == min) {
			nod1 = head;
		}
		head = head->next;
	}
	nod2 = head;
	if (nod1 != NULL && nod2 != NULL) {
		struct Brutarie aux = nod1->brutarie;
		nod1->brutarie = nod2->brutarie;
		nod2->brutarie = aux;
	}
}

struct Brutarie* filtrare(struct Nod* cap,float medieMinima,int *nrVector) {

	(*nrVector) = 0;
	struct Nod* aux = cap;
	while (cap != NULL) {
		if (mediePreturi(cap->brutarie.nrPaini, cap->brutarie.pretPaine) >= medieMinima)
			(*nrVector)++;
		cap = cap->next;
	}
	if (*nrVector != 0) {
		struct Brutarie* vector = malloc((*nrVector)*sizeof(struct Brutarie));
		int k = 0;
		while (aux != NULL) {

			if (mediePreturi(aux->brutarie.nrPaini, aux->brutarie.pretPaine) >= medieMinima) {
				vector[k].nume = malloc(strlen(aux->brutarie.nume) + 1);
				strcpy(vector[k].nume, aux->brutarie.nume);
				vector[k].nrPaini = aux->brutarie.nrPaini;
				vector[k].pretPaine = malloc(vector[k].nrPaini * sizeof(float));
				for (int i = 0; i < vector[k].nrPaini; i++) {
					vector[k].pretPaine[i] = aux->brutarie.pretPaine[i];
				}
				strcpy(vector[k].locatie, aux->brutarie.locatie);
				k++;
			}
			aux = aux->next;
		}
		return vector;
	}
	return NULL;
}
int main() {


	struct Nod* head = NULL;
	citireDinFisier(&head, "brutarie.txt");
	afisareLista(head);
	stergeNodIndex(&head, 9);
	printf("-----------");
	afisareLista(head);
	printf("-----------");
	struct Nod* headSortat = NULL;
	struct Brutarie brutarie1 = { "Brutarie1", 3, (float[]) { 2.5, 3.0, 2.0 }, "Strada X" };
	struct Brutarie brutarie2 = { "Brutarie2", 2, (float[]) { 1.5, 2.0 }, "Strada Y" };
	struct Brutarie brutarie3 = { "Brutarie3", 2, (float[]) { 0.5, 2.0 }, "Strada z" };

	adaugareSortata(&headSortat, brutarie1);
	adaugareSortata(&headSortat, brutarie2);
	adaugareSortata(&headSortat, brutarie3);
	int dim;
	struct Brutarie* brutarie = filtrare(headSortat, 1.5, &dim);
	printf("-----------");
	for (int i = 0; i < dim; i++) {
		afisareBrutarie(brutarie[i]);
		printf("Media este:%.2f\n", mediePreturi(brutarie[i].nrPaini, brutarie[i].pretPaine));
	}
	for (int i = 0; i < dim; i++) {
		freeBrutarie(&brutarie[i]);
	}
	free(brutarie);
	printf("-----------");
	afisareLista(headSortat);
	printf("-----------");
	interschimbareNoduri(headSortat, 1, 2);
	afisareLista(headSortat);
	return 0;
}
