#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Locuinta {
	int id;
	char* strada;
	int numar;

};
void inserare(struct Locuinta** vector, int* dim, struct Locuinta locuinta) {
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++) {
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = locuinta;
	if ((*vector) != NULL) {
		free(*vector);
	}
	(*vector) = copie;
}
void citesteFisier(const char* numeFisier,struct Locuinta** locuinte,
	int* dim) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier,"r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] =",\n";
			while (fgets(buffer,100,f) != NULL) {
				char* token = strtok(buffer, ",\n");
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				inserare(locuinte, dim, locuinta);
			}
			fclose(f);
		}
	}
}
void afisareLocuinte(struct Locuinta l) {
	printf("\nId-ul: %d \nStrada: %s\nNumarul:%d", l.id, l.strada, l.numar);

}
void stergeDupaId(struct Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		//avem de sters
		int k = 0;
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) *
			(--(*dim)));
		for (int i = 0; i < (*dim) + 1; i++) {
			if ((*vector)[i].id != id) {
				copie[k++] = (*vector)[i];
			}
		}
		if ((*vector) != NULL)
			free((*vector));
		(*vector) = copie;
	}
}
void afisareVector(struct Locuinta* vector, int dim) {
	if (dim != 0) {
		for (int i = 0; i < dim; i++) {
			afisareLocuinte(vector[i]);
		}
	}
}
void main() {
	struct Locuinta* locuinte = NULL;
	int dim = 0;
	citesteFisier("locuinte.txt", &locuinte, &dim);
	afisareVector(locuinte, dim);
	printf("\n\n\n\nInitial");
	afisareVector(locuinte, dim);
	stergeDupaId(&locuinte, &dim, 20);
	printf("\n\n\n\nUlterio:");
	afisareVector(locuinte,dim);
	return 0;
}