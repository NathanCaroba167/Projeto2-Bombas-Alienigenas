//
// Created by natha on 19/11/2025.
//

#ifndef SEGMENTADOR_H
#define SEGMENTADOR_H

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "txt.h"
#include "lista.h"

/*
 Módulo encarregado de executar e coordenar um segmentador com operações de converte para para tipo de forma.
 */

/// @brief Converte um Circulo em um Segmento.
/// @param txt Ponteiro para o arquivo TXT (que indicará a formas do processo).
/// @param c Ponteiro para o círculo analisado.
/// @param anteparo Ponteiro para a lista que receberá o segmento.
/// @param direcao Indicador de direção do segmento.
/// @warning
void converteCirculoSegmento(Arquivo txt,Circulo c,Lista anteparo,char direcao);

/// @brief Converte um Retângulo em um Segmento.
/// @param txt Ponteiro para o arquivo TXT (que indicará a formas do processo).
/// @param r Ponteiro para o retângulo analisado.
/// @param anteparo Ponteiro para a lista que receberá o segmento.
/// @warning
void converteRetanguloSegmento(Arquivo txt,Retangulo r,Lista anteparo);

/// @brief Converte um Linha em um Segmento.
/// @param txt Ponteiro para o arquivo TXT (que indicará a formas do processo).
/// @param l Ponteiro para a linha analisada.
/// @param anteparo Ponteiro para a lista que receberá o segmento.
/// @warning
void converteLinhaSegmento(Arquivo txt,Linha l,Lista anteparo);

/// @brief Converte um Texto em um Segmento.
/// @param txt Ponteiro para o arquivo TXT (que indicará a formas do processo).
/// @param t Ponteiro para o texto analisado.
/// @param anteparo Ponteiro para a lista que receberá o segmento.
/// @warning
void converteTextoSegmento(Arquivo txt,Texto t,Lista anteparo);

#endif //SEGMENTADOR_H