#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Quiz Quiz;
typedef struct Heap Heap;
struct Quiz {
    char* materie;
    int grileGresite;
};
struct Heap {
    Quiz* vector;
    int dim;
    int dimTotala;
};
Heap initializareHeap(int nr) {
    Heap heap;
    heap.vector = malloc(nr * sizeof(Quiz));
    heap.dimTotala = nr;
    heap.dim = 0;
    return heap;
}
Heap adaugareQuiz(Quiz quiz, Heap heap) {
    if (heap.dim < heap.dimTotala) {
        heap.vector[heap.dim] = quiz;
        heap.dim++;

    }
    return heap;
}

Quiz initializareQuiz(const char* materie, int grileGresite) {
    Quiz q;
    q.materie = malloc(strlen(materie) + 1);
    strcpy(q.materie, materie);
    q.grileGresite = grileGresite;
    return q;
}
void afisareQuiz(Quiz q) {
    printf("Materie %-10s ,grile gresite:%d\n", q.materie, q.grileGresite);
}

void afisareHeap(Heap heap) {
    for (int i = 0; i < heap.dim; i++) {
        afisareQuiz(heap.vector[i]);
    }
}
void afisareHeapTotala(Heap heap) {
    for (int i = 0; i < heap.dimTotala; i++) {
        afisareQuiz(heap.vector[i]);
    }
}
void filtreazaHeap(Heap heap, int pozRadacina) {
    int  nodSt = pozRadacina * 2 + 1;
    int nodDr = pozRadacina * 2 + 2;
    int idxMin = pozRadacina;
    if (nodSt < heap.dim && heap.vector[nodSt].grileGresite < heap.vector[idxMin].grileGresite) {
        idxMin = nodSt;
    }
    if (nodDr < heap.dim && heap.vector[nodDr].grileGresite < heap.vector[idxMin].grileGresite) {
        idxMin = nodDr;
    }
    if (idxMin != pozRadacina) {
        Quiz aux = heap.vector[pozRadacina];
        heap.vector[pozRadacina] = heap.vector[idxMin];
        heap.vector[idxMin] = aux;
        if (idxMin * 2 + 1 < heap.dim - 1) {
            filtreazaHeap(heap, idxMin);
        }
    }
}
Quiz extragereMinim(Heap* heap) {
    if (heap->dim > 0) {
        Quiz aux = heap->vector[0];
        heap->vector[0] = heap->vector[heap->dim - 1];
        heap->vector[heap->dim - 1] = aux;
        heap->dim--;

        for (int i = (heap->dim) / 2 - 1; i >= 0; i--) {
            filtreazaHeap(*heap, i);
        }
        return aux;
    }
    else
        return initializareQuiz("N/A", -1);
}
void dezlocareHeapTotala(Heap* heap) {
    for (int i = 0; i < heap->dimTotala; i++) {
        free(heap->vector[i].materie);
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->dim = 0;
    heap->dimTotala = 0;
}
void main() {
    Heap heap = initializareHeap(6);

    heap.vector[0] = initializareQuiz("Structuri de date", 3);
    heap.vector[1] = initializareQuiz("Java", 7);
    heap.vector[2] = initializareQuiz("Piton", 5);
    heap.vector[3] = initializareQuiz("Atp", 2);
    heap.vector[4] = initializareQuiz("Analiza", 9);
    heap.vector[5] = initializareQuiz("MRAI", 4);

    heap.dim = 6;
    afisareHeap(heap);
    printf("\n");
    for (int i = (heap.dim) / 2 - 1; i >= 0; i--) {
        filtreazaHeap(heap, i);
    }
    afisareHeap(heap);
    printf("\n");
    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));
    printf("\n");
    afisareHeap(heap);
    printf("\n");
    afisareHeapTotala(heap);

    dezlocareHeapTotala(&heap);

}