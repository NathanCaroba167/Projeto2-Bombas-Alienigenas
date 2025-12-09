//
// Created by natha on 19/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <error.h>

#include "sort.h"

void insertionSort(void* vetor, size_t n, size_t tamElem, ComparadorV comp) {
    char* arr = (char*)vetor;
    char* temp = malloc(tamElem);
    if (temp == NULL) {
        printf("Erro ao alocar memória ao insertionSort!\n");

        perror("Motivo do erro");
        exit(1);
    }

    if (!temp) return;

    for (size_t i = 1; i < n; i++) {
        memcpy(temp, arr + (i * tamElem), tamElem);
        int j = i - 1;

        while (j >= 0 && comp(arr + (j * tamElem), temp) > 0) {

            memcpy(arr + ((j + 1) * tamElem), arr + (j * tamElem), tamElem);
            j--;
        }

        memcpy(arr + ((j + 1) * tamElem), temp, tamElem);
    }
    free(temp);
}

void merge(void* vetor, size_t meio, size_t n, size_t tamElem, ComparadorV comp) {
    char* arr = (char*)vetor;

    size_t i = 0;
    size_t j = meio;
    size_t k = 0;

    char* aux = malloc(n * tamElem);
    if (aux == NULL) {
        printf("Erro ao alocar memória ao merge!\n");

        perror("Motivo do erro");
        exit(1);
    }
    if (!aux) return;

    while (i < meio && j < n) {
        if (comp(arr + (i * tamElem), arr + (j * tamElem)) <= 0) {
            memcpy(aux + (k * tamElem), arr + (i * tamElem), tamElem);
            i++;
        } else {
            memcpy(aux + (k * tamElem), arr + (j * tamElem), tamElem);
            j++;
        }
        k++;
    }

    while (i < meio) {
        memcpy(aux + (k * tamElem), arr + (i * tamElem), tamElem);
        i++;
        k++;
    }

    while (j < n) {
        memcpy(aux + (k * tamElem), arr + (j * tamElem), tamElem);
        j++;
        k++;
    }

    memcpy(arr, aux, n * tamElem);

    free(aux);
}

void mergeSortRecursivo(void* vetor, size_t n, size_t tamElem, ComparadorV comp, int limiteIns) {
    if (n <= (size_t)limiteIns) {
        insertionSort(vetor, n, tamElem, comp);
        return;
    }

    size_t meio = n / 2;
    char* arr = (char*)vetor;

    mergeSortRecursivo(arr, meio, tamElem, comp, limiteIns);
    mergeSortRecursivo(arr + (meio * tamElem), n - meio, tamElem, comp, limiteIns);
    merge(vetor, meio, n, tamElem, comp);
}

void ordenarVetor(void* vetor, size_t numElementos, size_t tamanhoElemento, ComparadorV comp, char metodo, int limiteInsertion) {
    if (numElementos <= 1) return;

    if (metodo == 'q' || metodo == 'Q') {
        qsort(vetor, numElementos, tamanhoElemento, comp);
    }
    else if (metodo == 'm' || metodo == 'M') {
        mergeSortRecursivo(vetor, numElementos, tamanhoElemento, comp, limiteInsertion);
    }
}