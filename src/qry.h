//
// Created by natha on 09/10/2025.
//

#ifndef QRY_H
#define QRY_H

#include "lista.h"

/*
 Módulo encarregado de ler um arquivo (.qry) e executar os comandos com as operações de abrir e ler
 */

/*
 Ponteiro do tipo FILE Arquivo
 Ponteiro char Nome
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Abre o arquivo .qry para leitura.
/// @param arquivo Ponteiro para o nome do arquivo que será aberto.
/// @return Ponteiro para o arquivo que será aberto.
Arquivo abrirQry(Nome arquivo);

/// @brief Lê comandos do (.qry) e executa na area, registrando resultados.
/// @param svg Ponteiro para o arquivo SVG (para visualização dinâmica).
/// @param txt Ponteiro para o arquivo TXT (para reportar resultados).
/// @param qry Ponteiro para o arquivo .qry que será lido.
/// @param formas Ponteiro para a lista de formas.
/// @param anteparos Ponteiro para a lista de anteparos.
/// @param tipoOrd Tipo de ordenação a ser usado (q: qsort ou m: mergesort).
/// @param limIns Limite de elementos para começar ordenar com insertionsort.
/// @param caminhoBaseSaida Caminho base para saida de arquivo no caso de criação de novo svg.
/// @warning
void LerComandosExecutar(Arquivo svg,Arquivo txt,Arquivo qry,Lista formas,Lista anteparos,char tipoOrd,int limIns, char* caminhoBaseSaida);

#endif //QRY_H