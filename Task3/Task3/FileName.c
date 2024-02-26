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
struct Brutarie atribuireDefault() {
	struct Brutarie brutarie;
	brutarie.nume = NULL;
	brutarie.nrPaini = 0;
	brutarie.pretPaine = NULL;
	return brutarie;
}
void freeBrutarie(struct Brutarie brutarie) {
	if (brutarie.nume != NULL)
		free(brutarie.nume);
	if (brutarie.nrPaini != 0 && brutarie.pretPaine != NULL)
		free(brutarie.pretPaine);

}
void atribuireBrutarie(struct Brutarie* brutarie, const char* nume, int nrPaini, float* preturi, const char* locatie) {
	if (brutarie->nume != NULL) {
		free(brutarie->nume);
	}
	brutarie->nume =(char*) malloc(strlen(nume) + 1);
	strcpy_s(brutarie->nume, strlen(nume) + 1, nume);

	brutarie->nrPaini = nrPaini;
	if (brutarie->pretPaine != NULL) {
		free(brutarie->pretPaine);
	}
	brutarie->pretPaine =(float*) malloc(brutarie->nrPaini * sizeof(float));
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
void afisareVector(struct Brutarie* VectorBrutarie, int lungime) {
	if (VectorBrutarie != NULL) {
		for (int i = 0; i < lungime; i++) {
			afisare(&VectorBrutarie[i]);
		}
	}
	else
		printf("\nNull vector");
}
int lungimeObiecte = 0;
void preiaInVector(int lungime,struct Brutarie ** vectorNou,const char* numeFisier) {
	if (lungime <= lungimeObiecte) {	
		FILE* f;
		fopen_s(&f, numeFisier, "rb");
		if (f != NULL) {
			(*vectorNou) = (struct Brutarie*)malloc(lungime * sizeof(struct Brutarie));
			for (int i = 0; i < lungime; i++) {
				int length;
				fread(&length, sizeof(int), 1, f);
				(*vectorNou)[i].nume = (char*)malloc((length + 1) * sizeof(char));
				fread((*vectorNou)[i].nume, length + 1, 1, f);
				fread(&((*vectorNou)[i].nrPaini), sizeof(int), 1, f);
				(*vectorNou)[i].pretPaine = (float*)malloc((*vectorNou)[i].nrPaini);
				fread((*vectorNou)[i].pretPaine, sizeof(float), (*vectorNou)[i].nrPaini, f);
				fread(((*vectorNou)[i].locatie), sizeof(char), sizeof((*vectorNou)[i].locatie), f);
			}	
			printf("Citire din fisier cu succes!");
		}
		else {
			printf("Nu s-a putut deschide fisierul!");
			(*vectorNou) = NULL;
		}
	}
	else {
		printf("Lungime mai mare ca nr de obiecte!");
		(*vectorNou) = NULL;
	}
}

void salvareObiectInFisierText(const char* numeFisier,struct Brutarie b) {
	FILE* f;
	fopen_s(&f, numeFisier, "w");
	if (f == NULL) {
		printf("nu s-a putut deschide fisierul!");
	}
	else {
		fprintf(f,"%s\n", b.nume);
		fprintf(f,"%d\n", b.nrPaini);
		for (int i = 0; i < b.nrPaini; i++) {
			fprintf(f, "%.2f ", b.pretPaine[i]);
		}
		fprintf(f, "\n%s\n", b.locatie);
		fclose(f);
	}
}
void salvareVectorDeObiectInFisierText(const char* numeFisier, struct Brutarie* b,int lungime) {
	FILE* f;
	fopen_s(&f, numeFisier, "w");
	if (f == NULL) {
		printf("nu s-a putut deschide fisierul!");
	}
	else {
		for (int i = 0; i < lungime; i++) {
			fprintf(f, "%s\n", b[i].nume);
			fprintf(f, "%d\n", b[i].nrPaini);
			for (int i = 0; i < b[i].nrPaini; i++) {
				fprintf(f, "%.2f ", b[i].pretPaine[i]);
			}
			fprintf(f, "\n%s\n", b[i].locatie);
		}
		fclose(f);
	}
}
int main() {
	float preturi[] = { 2.34f,11.32f };
	float preturi1[] = { 12.45f,11.32f };
	struct Brutarie brutarie1 = atribuireDefault();
	atribuireBrutarie(&brutarie1, "Ioana", 2, preturi, "Nord");
	struct Brutarie brutarie2 = atribuireDefault();;
	atribuireBrutarie(&brutarie2, "Mihai", 2, preturi, "Sud");
	struct Brutarie brutarie3 = atribuireDefault();;
	atribuireBrutarie(&brutarie3, "PaineBuna", 2, preturi, "Est");
	struct Brutarie brutarie4 = atribuireDefault();;
	atribuireBrutarie(&brutarie4, "PaineRea", 2, preturi1, "Centru");
	struct Brutarie brutarie5 = atribuireDefault();;
	atribuireBrutarie(&brutarie5, "Ionel", 2, preturi1, "Nord-Vest");
	struct Brutarie brutarie6 = atribuireDefault();
	atribuireBrutarie(&brutarie6, "Cristina", 2, preturi, "Nord");
	struct Brutarie brutarie7 = atribuireDefault();;
	atribuireBrutarie(&brutarie7, "Adrian", 2, preturi, "Sud");
	struct Brutarie brutarie8 = atribuireDefault();;
	atribuireBrutarie(&brutarie8, "Robert", 2, preturi, "Est");
	struct Brutarie brutarie9 = atribuireDefault();;
	atribuireBrutarie(&brutarie9, "PaineCalumea", 2, preturi1, "Centru");
	struct Brutarie brutarie10 = atribuireDefault();;
	atribuireBrutarie(&brutarie10, "Sebastian", 2, preturi1, "Nord-Vest");

	struct Brutarie brutarie[] = {brutarie1,brutarie2,brutarie3,brutarie4,brutarie5,brutarie6,
	brutarie7,brutarie8,brutarie9,brutarie10 };

	FILE* f;
	fopen_s(&f,"brutarie.bin", "wb");
	if (f == NULL) {
		printf("nu s-a putut deschide fisierul!");
	}
	else {
		for (int i = 0; i < 10; i++) {
			int numeLength = strlen(brutarie[i].nume);
			fwrite(&numeLength, sizeof(int), 1, f);
			fwrite(brutarie[i].nume, sizeof(char), strlen(brutarie[i].nume) + 1, f);
			fwrite(&brutarie[i].nrPaini, sizeof(int), 1, f);
			fwrite(brutarie[i].pretPaine, sizeof(float), brutarie[i].nrPaini, f);
			fwrite(brutarie[i].locatie, sizeof(char), sizeof(brutarie[i].locatie), f);
			lungimeObiecte++;
		}
		fclose(f);
	}

	int lungime = 10;
	struct Brutarie ** brutarieVectorPreluatDinFisier = NULL;
	preiaInVector(lungime,&brutarieVectorPreluatDinFisier,"brutarie.bin");
	afisareVector(brutarieVectorPreluatDinFisier, lungime);
	
	salvareObiectInFisierText("brutarieOut.txt", brutarie1);

	salvareVectorDeObiectInFisierText("brutarieOutVector.txt", brutarieVectorPreluatDinFisier, lungime);
	return 0;
}