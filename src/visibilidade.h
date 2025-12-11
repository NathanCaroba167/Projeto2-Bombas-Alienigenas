//
// Created by natha on 26/11/2025.
//

#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H

#include "lista.h"
#include "poligono.h"


/*
 Módulo encarregado de calcular um poligono que representa a região de visibilidade da bomba lançada.
 */

/// @brief Calcula a região de visibilidade da bomba.
/// @param anteparos Ponteiro para lista de anteparos analisada.
/// @param bx Coordenada x da queda da bomba.
/// @param by Coordenada y da queda da bomba.
/// @param tipoOrd Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limIns Limite de elementos para começar ordenar com insertionsort.
/// @return Ponteiro para o poligono/região de visibilidade da bomba.
/// @warning
Poligono calcularRegiaoVisibilidade(Lista anteparos, double bx, double by, char tipoOrd, int limIns);

int comparaSegmentosArvore(Segmento a, Segmento b);

void tratarSegmentosQueCruzamInicio(Lista anteparos, double bx, double by);

int calcularInterseccaoRaio(Segmento s, double theta, double* xSaida, double* ySaida);

#endif //VISIBILIDADE_H