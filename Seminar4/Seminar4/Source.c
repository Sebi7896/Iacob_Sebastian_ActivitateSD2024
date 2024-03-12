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
void citesteFisier(const char* numeFisier, struct Locuinta** locuinte,
	int* dim) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
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
	printf("\nId-ul: %d \tStrada: %-20s\tNumarul:%d", l.id, l.strada, l.numar);

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
void citesteMatriceLocuinteFisier(const char* numeFisier, struct Locuinta** matrice,
	int nrLinii,int* nrColoane) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL) {
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token = strtok(buffer, ",\n");
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				int pozitie = locuinta.numar % 2;
				inserare(&(matrice[pozitie]), &(nrColoane[pozitie]), locuinta);
			}
			fclose(f);
		}
	}
}
void afisareMatrice(struct Locuinta** matrice, int nrLinii, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			afisareLocuinte(matrice[i][j]);
		}
		printf("\n");
	}
}
void afisareIdDePeOParte(int paritate,struct Locuinta** matrice,int nrLinii
	,int* nrColoane) {
	paritate = paritate % 2;
		for(int j = 0; j< nrColoane[paritate]; j++)
			printf("%d ", matrice[paritate][j].id);	
}

struct Locuinta locuintaDupaId(int idCautat, struct Locuinta** matrice, int nrLinii
	, int* nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane[i]; j++) {
			if (matrice[i][j].id == idCautat) {
				return matrice[i][j];
			}
		}
	}
	struct Locuinta copie;
	copie.id = -1;
	copie.numar = -1;
	copie.strada = NULL;
	return copie;
}
void dezalocareMatrice(struct Locuinta*** matrice, int *nrLinii, int** nrColoane) {
	for (int i = 0; i < (*nrLinii); i++) {
		for (int j = 0; j < (*nrColoane)[i]; j++) {
			free((*matrice)[i][j].strada);
		}
		free((*matrice)[i]);
	}
	free(*matrice);
	*matrice = NULL;
	*nrLinii = 0;
	free(*nrColoane);
	*nrColoane = NULL;


}
void schimbareNrLocuinta(struct Locuinta** matrice, int nrLinii, int* nrColoane,
	int nrLocuinta) {
	int pozitie = nrLocuinta % 2;
	int idLocuinta = -1;
	int indexInVector = -1;
	for (int i = 0; i < nrColoane[pozitie]; i++) {
		if (matrice[pozitie][i].numar == nrLocuinta) {
			matrice[pozitie][i].numar++;
			idLocuinta = matrice[pozitie][i].id;
			indexInVector = i;
		}
	}
	if (idLocuinta != -1) {
		int index = (nrLocuinta + 1) % 2;
		inserare(&(matrice[index]), &(nrColoane[index]), matrice[pozitie][indexInVector]);
		stergeDupaId(&(matrice[pozitie]), &(nrColoane[pozitie]), idLocuinta);
	}
}
void main() {
	int nrLinii;
	int* nrColoane;
	struct Locuinta** matrice;
	nrLinii = 2;
	nrColoane = (int*)malloc(nrLinii * sizeof(int));
	matrice = (struct Locuinta**)malloc(sizeof(struct Locuinta*) * nrLinii);
	for (int i = 0; i < nrLinii; i++) {
		matrice[i] = NULL;
		nrColoane[i] = 0;
	}
	citesteMatriceLocuinteFisier("locuinte.txt", matrice, nrLinii, nrColoane);
	afisareMatrice(matrice, nrLinii, nrColoane);
	afisareIdDePeOParte(11, matrice, nrLinii, nrColoane);

	struct Locuinta locuinta = locuintaDupaId(20, matrice, nrLinii, nrColoane);
	afisareLocuinte(locuinta);
	schimbareNrLocuinta(matrice, nrLinii, nrColoane, 34);
	afisareMatrice(matrice, nrLinii, nrColoane);
	dezalocareMatrice(&matrice, &nrLinii, &nrColoane);
	return 0;
}