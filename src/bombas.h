//
// Created by natha on 01/12/2025.
//
//
// Created by natha on 01/12/2025.
//

#ifndef BOMBAS_H
#define BOMBAS_H

#include "lista.h"
#include "txt.h"

/*
 Módulo encarregado de coordenar bombas com operações Anteparo(cria os anteparos) e tipos de bomba: Destruição, Pintura e Clone.
 */

/// @brief Converte uma faixa de IDs de formas para Segmentos do tipo Anteparos, através da tinta bloqueante.
/// @param txt Ponteiro para o arquivo TXT (para reportar resultados).
/// @param formas Ponteiro para a lista de formas.
/// @param anteparos Ponteiro para a lista de anteparos.
/// @param inicial ID que inicia a faixa de formas.
/// @param final Id que finaliza a faixa de formas.
/// @param direcao Indicador de direção do segmento que o círculo será convertido.
/// @warning
void Anteparo(Arquivo txt,Lista formas,Lista anteparos,int inicial,int final,char direcao);

/// @brief Bomba de destruição, destroi formas na sua região de visibilidade, incluindo anteparos.
/// @param svg Ponteiro para o arquivo SVG (para visualização dinâmica).
/// @param txt Ponteiro para o arquivo TXT (para reportar resultados).
/// @param formas Ponteiro para a lista de formas.
/// @param anteparos Ponteiro para a lista de anteparos.
/// @param xBomba Coordenada x da queda da bomba.
/// @param yBomba Coordenada y da queda da bomba.
/// @param sfx_modo Sufixo para determinar o svg para desenho da regiao de visibilidade da bomba.
/// @param caminhoBaseSaida Caminho base para saida de arquivo no caso de criação de novo svg.
/// @param tipoOrd Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limIns Limite de elementos para começar ordenar com insertionsort.
/// @warning
void Destruicao(Arquivo svg,Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns);

/// @brief Bomba de Pintura, pinta formas na sua região de visibilidade, incluindo anteparos.
/// @param svg Ponteiro para o arquivo SVG (para visualização dinâmica).
/// @param txt Ponteiro para o arquivo TXT (para reportar resultados).
/// @param formas Ponteiro para a lista de formas.
/// @param anteparos Ponteiro para a lista de anteparos.
/// @param xBomba Coordenada x da queda da bomba.
/// @param yBomba Coordenada y da queda da bomba.
/// @param cor Cor que será lançada pela bomba.
/// @param sfx_modo Sufixo para determinar o svg para desenho da regiao de visibilidade da bomba.
/// @param caminhoBaseSaida Caminho base para saida de arquivo no caso de criação de novo svg.
/// @param tipoOrd Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limIns Limite de elementos para começar ordenar com insertionsort.
/// @warning
void Pintura(Arquivo svg,Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba,char* cor, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns);

/// @brief Bomba de clonagem, clona formas na sua região de visibilidade, incluindo anteparos.
/// @param svg Ponteiro para o arquivo SVG (para visualização dinâmica).
/// @param txt Ponteiro para o arquivo TXT (para reportar resultados).
/// @param formas Ponteiro para a lista de formas.
/// @param anteparos Ponteiro para a lista de anteparos.
/// @param xBomba Coordenada x da queda da bomba.
/// @param yBomba Coordenada y da queda da bomba.
/// @param dx Deslocamento da coordenada x a partir da forma clonada.
/// @param dy Deslocamento da coordenada y a partir da forma clonada.
/// @param sfx_modo Sufixo para determinar o svg para desenho da regiao de visibilidade da bomba.
/// @param caminhoBaseSaida Caminho base para saida de arquivo no caso de criação de novo svg.
/// @param tipoOrd Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limIns Limite de elementos para começar ordenar com insertionsort.
/// @warning
void Clone(Arquivo svg, Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba, double dx, double dy, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns);

#endif //BOMBAS_H