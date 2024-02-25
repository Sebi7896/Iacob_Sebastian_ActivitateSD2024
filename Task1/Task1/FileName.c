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
struct Brutarie citireBrutarie() {
	struct Brutarie brutarie;
	printf("Nume:");
	char buffer[100];
	fgets(buffer,100,stdin);
	printf("Locatie:");
	fgets(brutarie.locatie, 100, stdin);
	if (strlen(buffer) != 0) {
		brutarie.nume = malloc(strlen(buffer) + 1);
		strcpy_s(brutarie.nume,sizeof(buffer),buffer);
	}
	printf("Nr paini=");
	scanf_s("%d", &brutarie.nrPaini);
	printf("Pret Paine=");
	if (brutarie.nrPaini != 0) {
		brutarie.pretPaine = malloc(brutarie.nrPaini * sizeof(float));
		for (int i = 0; i < brutarie.nrPaini; i++) {
			printf("Pret painea %d:", i + 1);
			scanf_s("%f", &brutarie.pretPaine[i]);
		}
	}
	return brutarie;	
}
float MaxPretPaina(float* v,int lungime) {
	if (v != NULL) {
		float max = v[0];
		for (int i = 1; i < lungime; i++) {
			if (v[i] > max)
				max = v[i];
		}
		return max;
	}
	return 0;
}
void preturiMaiMariDecatUnTarget(struct Brutarie myObject, struct Brutarie *returnedObject,int target) {
	if (myObject.nrPaini != 0 && myObject.pretPaine != NULL) {
		returnedObject->nume = malloc(sizeof(myObject.nume) + 1);
		strcpy_s(returnedObject->nume, sizeof(myObject.nume), myObject.nume);
		strcpy_s(returnedObject->locatie,sizeof(myObject.locatie),myObject.locatie);

		int nrPesteTarget = 0;
		for (int i = 0; i < myObject.nrPaini; i++) {
			if (myObject.pretPaine[i] > target)
				nrPesteTarget++;
		}
		printf("%d", nrPesteTarget);
		if (returnedObject->pretPaine != NULL)
			free(returnedObject->pretPaine);
		returnedObject->nrPaini = nrPesteTarget;
		returnedObject->pretPaine = malloc(returnedObject->nrPaini * sizeof(float));
		for (int i = 0; i < myObject.nrPaini; i++) {
			if ((int)myObject.pretPaine[i] % 2 != 0)
				returnedObject->pretPaine[i] = myObject.pretPaine[i];
		}
	}
	else {
		returnedObject = &myObject;
	}

}

void afisare(struct Brutarie brutarie) {
	printf("\nNume:%s", brutarie.nume);
	printf("Nr Paini:%d\n", brutarie.nrPaini);
	for (int i = 0; i < brutarie.nrPaini; i++) {
		printf("Painea %d:%.2f\n",i+1, brutarie.pretPaine[i]);
	}
	printf("Locatie:%s\n", brutarie.locatie);
}
void freeBrutarie(struct Brutarie brutarie) {
	if(brutarie.nume != NULL)
		free(brutarie.nume);
	if (brutarie.nrPaini != 0 && brutarie.pretPaine != NULL)
		free(brutarie.pretPaine);

}
int main() {
	struct Brutarie brutarie = citireBrutarie();
	struct Brutarie brutarie2 = atribuireDefault();
	afisare(brutarie);
	afisare(brutarie);
	float max = MaxPretPaina(brutarie.pretPaine, brutarie.nrPaini);
	printf("\n%.2f",max );

	preturiMaiMariDecatUnTarget(brutarie, &brutarie2,10);
	afisare(brutarie2);
	freeBrutarie(brutarie);
	freeBrutarie(brutarie2);
	return 0;
}