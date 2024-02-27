#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct Avion {
	int nrPasageri;
	char* companie;
	float pretBilet;
};
struct Avion initializare(int nrPasageri,const char* companie,float pretBilet) {
	struct Avion avion;
	avion.nrPasageri = nrPasageri;
	avion.companie =(char*) malloc((strlen(companie) + 1)*sizeof(char));
	strcpy_s(avion.companie, (strlen(companie) + 1) * sizeof(char),companie);
	avion.pretBilet = pretBilet;
	return avion;
}
void afisareAvion(struct Avion avion) {
	printf("%s are un avion de %d locuri cu pretul de %5.2f pe loc\n",
		avion.companie, avion.nrPasageri, avion.pretBilet);
}
void afisareVector(struct Avion* vector,int nrAvioane) {
	if (vector != NULL) {
		for (int i = 0; i < nrAvioane; i++) {
			afisareAvion(vector[i]);
		}
	}
}

struct Avion* copierePrimeleNElemente(struct Avion* vector,int nrAvioane,int nrAvioaneCopiate) {
	if (nrAvioaneCopiate < nrAvioane && nrAvioaneCopiate > 0) {
		struct Avion* avioaneCopiate = (struct Avion*)malloc(sizeof(struct Avion) *
			nrAvioane);
		for (int i = 0; i < nrAvioaneCopiate; i++) {
			avioaneCopiate[i] = initializare(vector[i].nrPasageri,
				vector[i].companie,vector[i].pretBilet);
		}
		return avioaneCopiate;
	}
	else
		return NULL;
}
void dezalocare(struct Avion** avioane, int *nrAvioane) {
	if (*avioane != NULL) {
		for (int i = 0; i < *nrAvioane; i++) {
			free((*avioane)[i].companie);
		}
		free(*avioane);
		*nrAvioane = 0;
		*avioane = NULL;
	}
}
void copiazaAvioaneCuBileteReduse(struct Avion* avioane,int nrAvioane,float pragPret
,struct Avion** avionNou,int* dimensiune) {
	if (*avionNou != NULL)
		dezalocare(avionNou, dimensiune);
	else
		(*dimensiune) = 0;
	for (int i = 0; i < nrAvioane; i++) {
		if (avioane[i].pretBilet < pragPret)
			(*dimensiune)++;
	}
	*avionNou = (struct Avion*)malloc((*dimensiune) * sizeof(struct Avion));
	int k = 0;
	for (int i = 0; i < nrAvioane; i++) {
		if (avioane[i].pretBilet < pragPret)
			(*avionNou)[k++] = initializare(avioane[i].nrPasageri,
				avioane[i].companie, avioane[i].pretBilet);
	}
}
struct Avion getPrimulAvionDupaCompanie(struct Avion* avioane,int nrAvioane,const char* companie) {
	
	if (avioane != NULL && companie != NULL) {
		for (int i = 0; i < nrAvioane; i++) {
			if (avioane[i].companie != NULL) {
				if (strcmp(avioane[i].companie, companie) == 0)
					return initializare(avioane[i].nrPasageri,avioane[i].companie,avioane[i].pretBilet);
			}
		}
	}
	return initializare(-1, "N/A", -1);
}
void main() {

	int nrAvioane = 5;
	struct Avion* avioane = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioane);
	for (int i = 0; i < nrAvioane; i++) {
		avioane[i] = initializare(i + 50, "Tarom", 10 * i + 40);
	}
	int v[10];//stack
	int* v1;

	afisareVector(avioane, nrAvioane);

	int nrAvioaneCopiate = 3;
	struct Avion* copiate = copierePrimeleNElemente(avioane, nrAvioane, nrAvioaneCopiate);
	printf("\n");
	afisareVector(copiate, nrAvioaneCopiate);

	int nrAvioaneCuBileteReduse = 0;
	struct Avion* avioaneCuBileteReduse = NULL;

	avioane[4].pretBilet = 30;
	copiazaAvioaneCuBileteReduse(avioane, nrAvioane, 70, &avioaneCuBileteReduse,
		&nrAvioaneCuBileteReduse);

	printf("\n\n");
	afisareVector(avioaneCuBileteReduse, nrAvioaneCuBileteReduse);

	struct Avion avion2 = getPrimulAvionDupaCompanie(avioane, nrAvioane, "Tarom");
	printf("\n");
	afisareAvion(avion2);

	dezalocare(&avioane, &nrAvioane);
	dezalocare(&copiate, &nrAvioaneCopiate);
	dezalocare(&avioaneCuBileteReduse, &nrAvioaneCuBileteReduse);
	free(avion2.companie);
}
