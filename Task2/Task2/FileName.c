#include<stdio.h>
#include<malloc.h>
#include<string.h>
//Iacob Sebastian
//Brutarie Artizanala
struct Brutarie {
	char* nume;
	int nrPaini;
	float* pretPaine;
	char locatie[30];
};
void freeBrutarie(struct Brutarie brutarie) {
	if (brutarie.nume != NULL)
		free(brutarie.nume);
	if (brutarie.nrPaini != 0 && brutarie.pretPaine != NULL)
		free(brutarie.pretPaine);

}
struct Brutarie atribuireDefault() {
	struct Brutarie brutarie;
	brutarie.nume = NULL;
	brutarie.nrPaini = 0;
	brutarie.pretPaine = NULL;
	return brutarie;
}
void atribuireBrutarie(struct Brutarie* brutarie,const char* nume, int nrPaini, float* preturi, const char* locatie) {
	if (brutarie->nume != NULL) {
		free(brutarie->nume);
	}
	brutarie->nume = malloc(strlen(nume) + 1);
	strcpy_s(brutarie->nume, strlen(nume) + 1, nume);

	brutarie->nrPaini = nrPaini;
	if (brutarie->pretPaine != NULL) {
		free(brutarie->pretPaine);
	}
	brutarie->pretPaine = malloc(brutarie->nrPaini * sizeof(float));
	for (int i = 0; i < brutarie->nrPaini; i++) {
		brutarie->pretPaine[i] = preturi[i];
	}
	strncpy_s(brutarie->locatie, sizeof(brutarie->locatie), locatie, 30);
	brutarie->locatie[sizeof(brutarie->locatie) - 1] = '\0';
}
void afisare(struct Brutarie* brutarie) {
	printf("\nNume:%s\n", brutarie->nume);
	printf("Nr Paini:%d\n", brutarie->nrPaini);
	for (int i = 0; i < brutarie->nrPaini; i++) {
		printf("Painea %d:%.2f\n", i + 1, brutarie->pretPaine[i]);
	}
	printf("Locatie:%s\n", brutarie->locatie);
}

void VectorNouToatePreturi(struct Brutarie* vector,int lungime,struct Brutarie *vectorNou,int* lungimeNou,float target) {
	*lungimeNou = 0;
	for (int i = 0; i < lungime; i++) {
		for (int j = 0; j < lungime; i++) {

		}
 	}

}
int main() {
	float preturi[] = {2.34f,11.32f};
	float preturi1[] = {12.45f,11.32f};
	struct Brutarie brutarie1 =atribuireDefault();
	atribuireBrutarie(&brutarie1, "Ioana", 2, preturi, "Nord");
	struct Brutarie brutarie2 = atribuireDefault();;
	atribuireBrutarie(&brutarie2, "Mihai", 2, preturi, "Sud");
	struct Brutarie brutarie3=atribuireDefault();;
	atribuireBrutarie(&brutarie3, "PaineBuna", 2, preturi, "Est");
	struct Brutarie brutarie4=atribuireDefault();;
	atribuireBrutarie(&brutarie4, "PaineRea", 2, preturi1, "Centru");
	struct Brutarie brutarie5=atribuireDefault();;
	atribuireBrutarie(&brutarie5, "Ioana", 2, preturi1, "Nord-Vest");
	
	
	struct Brutarie* VectorBrutarie = malloc(5 * sizeof(struct Brutarie));
	VectorBrutarie[0] = brutarie1;
	VectorBrutarie[1] = brutarie2;
	VectorBrutarie[2] = brutarie3;
	VectorBrutarie[3] = brutarie4;
	VectorBrutarie[4] = brutarie5;

	for (int i = 0; i < 5; i++) {
		afisare(&VectorBrutarie[i]);
	}
		
	return 0;
}