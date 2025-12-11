//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../sort.h"

// --- AUXILIARES ---

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

// Verifica se um vetor de int está ordenado
int esta_ordenado_int(int* vet, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        if (vet[i] > vet[i+1]) return 0;
    }
    return 1;
}

// --- COMPARADORES (Necessários para passar para o sort) ---

// Comparador de Inteiros
int comp_int(const void* a, const void* b) {
    int va = *(const int*)a;
    int vb = *(const int*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

// Comparador de Structs (Teste de dados complexos)
typedef struct {
    int id;
    float peso;
} Item;

int comp_item_por_peso(const void* a, const void* b) {
    Item* ia = (Item*)a;
    Item* ib = (Item*)b;
    if (ia->peso < ib->peso) return -1;
    if (ia->peso > ib->peso) return 1;
    return 0;
}

// --- TESTES ---

void teste_quicksort_padrao() {
    printf("\n--- Teste 1: QuickSort (q) - Inteiros ---\n");

    int vet[] = {10, 5, 8, 1, 3, 9, 2, 4, 7, 6};
    size_t n = 10;

    // 'q' usa o qsort da stdlib
    ordenarVetor(vet, n, sizeof(int), comp_int, 'q', 0);

    verificar(esta_ordenado_int(vet, n), "Vetor ordenado corretamente com QuickSort");
    verificar(vet[0] == 1 && vet[9] == 10, "Extremos estao corretos");
}

void teste_mergesort_hibrido() {
    printf("\n--- Teste 2: MergeSort Hibrido (m) - Inteiros ---\n");

    // Caso 1: Vetor Grande com Limite Pequeno
    // Força o uso da recursão do Merge e do Merge em si
    int vetA[] = {50, 40, 30, 20, 10, 5, 4, 3, 2, 1};
    size_t n = 10;

    // Limite 2: Vai dividir até ter pedaços de tamanho 2 ou 1
    ordenarVetor(vetA, n, sizeof(int), comp_int, 'm', 2);
    verificar(esta_ordenado_int(vetA, n), "MergeSort ordenou vetor invertido");

    // Caso 2: Vetor Pequeno com Limite Grande
    // Força cair direto no InsertionSort (sem recursão profunda)
    int vetB[] = {9, 7, 5, 3, 1};
    // Limite 10: Como n=5 <= 10, usa InsertionSort direto
    ordenarVetor(vetB, 5, sizeof(int), comp_int, 'm', 10);
    verificar(esta_ordenado_int(vetB, 5), "InsertionSort (via limite) funcionou");
}

void teste_dados_complexos() {
    printf("\n--- Teste 3: Ordenacao de Structs ---\n");

    // Cria vetor de itens desordenados por peso
    Item itens[4];
    itens[0].id = 1; itens[0].peso = 50.5;
    itens[1].id = 2; itens[1].peso = 10.1;
    itens[2].id = 3; itens[2].peso = 30.3;
    itens[3].id = 4; itens[3].peso = 20.2;

    // Ordena usando MergeSort
    ordenarVetor(itens, 4, sizeof(Item), comp_item_por_peso, 'm', 2);

    // Verifica a ordem dos pesos: 10.1 -> 20.2 -> 30.3 -> 50.5
    // IDs esperados: 2, 4, 3, 1
    int ok = (itens[0].id == 2 && itens[1].id == 4 &&
              itens[2].id == 3 && itens[3].id == 1);

    verificar(ok, "Structs ordenadas corretamente pelo campo float");
}

void teste_casos_borda() {
    printf("\n--- Teste 4: Casos de Borda ---\n");

    // 1. Vetor de 1 elemento
    int vet1[] = {42};
    ordenarVetor(vet1, 1, sizeof(int), comp_int, 'm', 5);
    verificar(vet1[0] == 42, "Vetor unitario permanece igual");

    // 2. Vetor com duplicatas
    int vetDup[] = {5, 1, 5, 1, 5};
    ordenarVetor(vetDup, 5, sizeof(int), comp_int, 'm', 2);
    verificar(esta_ordenado_int(vetDup, 5), "Vetor com duplicatas ordenado");
    // Esperado: 1, 1, 5, 5, 5
    verificar(vetDup[0]==1 && vetDup[2]==5, "Valores duplicados preservados");
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO SORT\n");
    printf("==========================================\n");

    teste_quicksort_padrao();
    teste_mergesort_hibrido();
    teste_dados_complexos();
    teste_casos_borda();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}