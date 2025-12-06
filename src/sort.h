//
// Created by natha on 19/11/2025.
//

#ifndef SORT_H
#define SORT_H

/*
 Módulo encarregado de coordenar um sort com operação de ordenar.
 */

typedef int (*Comparador)(Vertice, Vertice);

/// @brief Ordena um vetor de vertices de acordo com seu ângulo.
/// @param vetor Vetor que será ordenado.
/// @param numElementos Número de elementos do vetor.
/// @param tamanhoElemento Tamanho do elemento do vetor.
/// @param comp Ponteiro de Função para comparação.
/// @param metodo Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limiteInsertion Limite de elementos para começar ordenar com insertionsort.
/// @warning
void ordenarVetor(void* vetor, size_t numElementos, size_t tamanhoElemento, Comparador comp, char metodo, int limiteInsertion);

#endif //SORT_H