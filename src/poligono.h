//
// Created by natha on 28/11/2025.
//

#ifndef POLIGONO_H
#define POLIGONO_H

#include "forma.h"
#include "lista.h"

/*
 Módulo encarregado de coordenar um poligono com operações de criar, get, adicionar, verificar e eliminar
 */

/*
 Ponteiro void Poligono
 Ponteiro void Ponto
 */
typedef void* Poligono;
typedef void* Ponto;

/// @brief Cria um ponto com suas coordenadas.
/// @param x Coordenada x do ponto.
/// @param y Coordenada y do ponto.
/// @return Ponteiro para o ponto criado.
/// @warning
Ponto CriarPonto(double x, double y);

/// @brief Pega a coordenada x do ponto sem modifica-la.
/// @param p Ponteiro para o ponto analisado.
/// @return Um double que representa a coordenada x do ponto.
/// @warning
double getXPonto(Ponto p);

/// @brief Pega a coordenada y do ponto sem modifica-la.
/// @param p Ponteiro para o ponto analisado.
/// @return Um double que representa a coordenada y do ponto.
/// @warning
double getYPonto(Ponto p);

/// @brief Libera a memória alocada para o ponto.
/// @param p Ponteiro para o ponto que será eliminado.
/// @warning
void eliminarPonto(Ponto p);

/// @brief Cria um poligono que representa a região de visibilidade da bomba.
/// @return Ponteiro para o poligono criado.
/// @warning
Poligono CriarPoligono();

/// @brief Adiciona um ponto ao poligono.
/// @param p Ponteiro para o poligono que receberá o ponto.
/// @param pt Ponteiro para o ponto que será adicionado.
/// @warning
void adicionarPontoAoPoligono(Poligono p, Ponto pt);

/// @brief Pega a lista de pontos que formam o poligono.
/// @param p Ponteiro para o poligono analisado.
/// @return Ponteiro para a lista de pontos.
/// @warning
Lista getListaPontosPoligono(Poligono p);

/// @brief Libera a memória alocada para o poligono.
/// @param p Ponteiro para o poligono que será eliminado.
/// @warning
void eliminarPoligono(Poligono p);

/// @brief Verifica se a forma e o poligono estão sobrepostos.
/// @param p Ponteiro para o poligono analisado.
/// @param forma Ponteiro para a forma analisada.
/// @return True (1) se houver sobreposição ou False (0) se não houver sobreposição.
/// @warning
bool verificarSobreposicao(Poligono p, Pacote forma);

#endif //POLIGONO_H