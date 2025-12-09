//
// Created by natha on 18/10/2025.
//

#ifndef VERTICES_H
#define VERTICES_H

#include "segmento.h"
#include "lista.h"

/*
 Módulo encarregado de coordenar vertices com operações de criar, get, criarVetor e eliminar
 */

typedef enum {
    INICIO,
    FIM
}TipoVertice;

/*
 Ponteiro void Vertice
 Ponteiro void Vetor
 */
typedef void* Vertice;
typedef void* Vetor;

/// @brief Cria um vertice com os atributos indicados.
/// @param x Coordenada x do vertice.
/// @param y Coordenada y do vertice.
/// @param angulo Ângulo do vertice referente a bomba lançada.
/// @param distancia Distância entre o vertice e a bomba lançada.
/// @param tipo Tipo de vertice (INICIO ou FIM) que foi criado.
/// @param original Segmento o qual o vertice deu origem.
/// @return Ponteiro para o vertice criado.
/// @warning
Vertice CriarVertice(double x, double y, double angulo, double distancia,TipoVertice tipo, Segmento original);

/// @brief Pega a coordenada x do vertice sem modifica-la.
/// @param v Ponteiro para o vertice analisado.
/// @return Um double que representa a coordenada x do vertice.
/// @warning
double getXVertice(Vertice v);

/// @brief Pega a coordenada y do vertice sem modifica-la.
/// @param v Ponteiro para o vertice analisado.
/// @return Um double que representa a coordenada y do vertice.
/// @warning
double getYVertice(Vertice v);

/// @brief Pega o ângulo do vertice referente a bomba lançada.
/// @param v Ponteirp para o vertice analisado.
/// @return Um double que representa o ângulo do vertice referente a bomba lançada.
/// @warning
double getAnguloVertice(Vertice v);

/// @brief Pega a distância entre o vertice e a bomba lançada.
/// @param v Ponteiro para o vertice analisado.
/// @return Um double que representa a distância entre o vertice e a bomba lançada.
/// @warning
double getDistanciaVertice(Vertice v);

/// @brief Pega o tipo do vertice que está dentro do vertice sem modifica-lo.
/// @param v Ponteiro para o vertice analisado.
/// @return Ponteiro para o tipo de vertice que foi pego.
/// @warning
TipoVertice getTipoVertice(Vertice v);

/// @brief Pega o segmento que deu origem ao vertice.
/// @param v Ponteiro para o vertice analisado.
/// @return Ponteiro para o segmento que deu origem ao vertice.
/// @warning
Segmento getSegmentoVertice(Vertice v);

/// @brief Libera a memória alocada para o vertice.
/// @param v Ponteiro para o vertice que será eliminado.
/// @warning
void eliminarVertice(Vertice v);

/// @brief Cria um vetor de vertices.
/// @param anteparo Ponteiro para lista de anteparos analisada.
/// @param xBomba Coordenada x da queda da bomba.
/// @param yBomba Coordenada y da queda da bomba.
/// @return Ponteiro para o vetor de vertices.
/// @warning
Vetor CriarVetorVertices(Lista anteparo, double xBomba, double yBomba, int* qtdVertices);

#endif //VERTICES_H