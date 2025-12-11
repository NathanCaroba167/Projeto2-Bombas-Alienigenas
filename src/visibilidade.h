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

/// @brief Calcula o ponto onde o eixo X da bomba (ângulo 0°) corte o anteparo.
/// @param s Ponteiro para o segmento analisado.
/// @param theta Ângulo para analise.
/// @param xSaida Coordenada x da interseccao no anteparo.
/// @param ySaida Coordenada y da interseccao no anteparo.
/// @return Retorna uma validação de intersecção 1 há interseccao 0 não há.
/// @warning
int calcularInterseccaoRaio(Segmento s, double theta, double* xSaida, double* ySaida);

/// @brief Compara Segmentos para verificação da árvore.
/// @param a Segmento a analisado.
/// @param b Segmento b analisado.
/// @return Inteiro que indica a direção na árvore que o segmento deve ficar.
/// @warning
int comparaSegmentosArvore(Segmento a, Segmento b);

/// @brief Trata o início da leitura da região de visibilidade.
/// @param anteparos Ponteiro para a lista de anteparos.
/// @param bx Coordenada x da queda da bomba.
/// @param by Coordenada y da queda da bomba.
/// @warning
void tratarSegmentosQueCruzamInicio(Lista anteparos, double bx, double by);

/// @brief Calcula a região de visibilidade da bomba.
/// @param anteparos Ponteiro para lista de anteparos analisada.
/// @param bx Coordenada x da queda da bomba.
/// @param by Coordenada y da queda da bomba.
/// @param tipoOrd Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limIns Limite de elementos para começar ordenar com insertionsort.
/// @return Ponteiro para o poligono/região de visibilidade da bomba.
/// @warning
Poligono calcularRegiaoVisibilidade(Lista anteparos, double bx, double by, char tipoOrd, int limIns);

#endif //VISIBILIDADE_H