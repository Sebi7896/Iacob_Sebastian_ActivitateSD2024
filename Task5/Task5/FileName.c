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
void adaugareLista(struct Nod** head,struct Brutarie brutarie) {
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
	printf("\nNume:%s\n", brutarie.nume);
	printf("Nr Paini:%d\n", brutarie.nrPaini);
	for (int i = 0; i < brutarie.nrPaini; i++) {
		printf("Painea %d:%.2f\n", i + 1, brutarie.pretPaine[i]);
	}
	printf("Locatie:%s\n", brutarie.locatie);
}

void citireDinFisier(struct Nod** head,const char* numefisier) {	
	if(numefisier != NULL && strlen(numefisier) > 0)
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
void stergeNodIndex(struct Nod** head,int index) {
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
float mediePreturi(int nrPreturi,float* preturi) {
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
	afisareLista(headSortat);

	return 0;
}
