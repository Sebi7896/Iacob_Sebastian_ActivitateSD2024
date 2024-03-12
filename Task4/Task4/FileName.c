#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Brutarie {
	char* nume;
	int nrPaini;
	float* pretPaine;
	char locatie[30];
};
struct Brutarie atribuireDefault() {
	struct Brutarie brutarie;
	brutarie.nume = NULL;
	brutarie.nrPaini = 0;
	brutarie.pretPaine = NULL;
	strcpy_s(brutarie.locatie,strlen("Necunoscut") + 1, "Necunoscut");
	return brutarie;
}
void freeBrutarie(struct Brutarie* brutarie) {
	if (brutarie->nume != NULL)
		free(brutarie->nume);
	if (brutarie->nrPaini != 0 && brutarie->pretPaine != NULL)
		free(brutarie->pretPaine);

}
void afisareBrutarie(struct Brutarie brutarie) {
	printf("\nNume:%s\n", brutarie.nume);
	printf("Nr Paini:%d\n", brutarie.nrPaini);
	for (int i = 0; i < brutarie.nrPaini; i++) {
		printf("Painea %d:%.2f\n", i + 1, brutarie.pretPaine[i]);
	}
	printf("Locatie:%s\n", brutarie.locatie);
}
void afisareVector(struct Brutarie* VectorBrutarie, int lungime) {
	if (VectorBrutarie != NULL) {
		for (int i = 0; i < lungime; i++) {
			afisareBrutarie(VectorBrutarie[i]);
		}
	}
	else
		printf("\nNull vector");
}
void inserare(struct Brutarie** vector, int* dim, struct Brutarie brutarie) {
	struct Brutarie* copie;
	copie=malloc(sizeof(struct Brutarie) * ((*dim) + 1));
	for (int i = 0; i < (*dim); i++) {
		copie[i] = (*vector)[i];
	}
	copie[(*dim)] = brutarie;
	if ((*vector) != NULL) {
		free(*vector);
	}
	(*vector) = copie;
	(*dim)++;
}

void citireBrutariiFisier(struct Brutarie** brutarii,
	const char* numeFisier,int *dim) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f =fopen(numeFisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			char delimitatorVectorPreturi[] = " ";
			while (fgets(buffer, 100, f) != NULL) {
				char* token = strtok(buffer, delimitator);
				struct Brutarie brutarie;
				brutarie.nume = (char*)malloc(strlen(token) + 1);
				strcpy(brutarie.nume,token);
				token = strtok(NULL, delimitator);
				brutarie.nrPaini = atoi(token);
				token = strtok(NULL, delimitator);
				brutarie.pretPaine = (float*)malloc(brutarie.nrPaini*(sizeof(float)));
				for (int i = 0; i < brutarie.nrPaini; i++) {
					brutarie.pretPaine[i] = atof(token);
					token = strtok(NULL, delimitator);
				}
				strcpy(brutarie.locatie, token);
				inserare(brutarii, dim, brutarie);
			}
			fclose(f);
		}
	}

}
void copiereInMatrice(struct Brutarie* vector,int dimVec, struct Brutarie** matrice,int nrLinii,int *nrColoane) {
	//ne luam dupa nrPaini
	//prima linie nrPaini intre 0 si 3
	//a-2-a 3-10
	//a-3-a restul
	for (int i = 0; i < dimVec; i++) {
		if (vector[i].nrPaini <= 3)
			nrColoane[0]++;
		else
			if (vector[i].nrPaini <= 10)
				nrColoane[1]++;
			else
				nrColoane[2]++;
	}
	for (int i = 0; i < nrLinii; i++) {

	}
	



}

int main() {

	//2
	int dim;
	struct Brutarie* brutarie = NULL;
	citireBrutariiFisier(&brutarie, "brutarie.txt", &dim);
	afisareVector(brutarie, dim);

	//3
	printf("\n\n");
	int nrLinii = 3;
	struct Brutarie** matrice =malloc(nrLinii * sizeof(struct Brutarie*));
	int* nrColoane = malloc(3 * sizeof(int));
	for (int i = 0; i < nrLinii; i++) {
		matrice[i] = NULL;
		nrColoane[i] = 0;
	}

	return 0;
}