//
// Created by natha on 09/10/2025.
//

#ifndef GEO_H
#define GEO_H

#include "lista.h"

/*
 Módulo encarregado de ler um arquivo (.geo) e inicializar as formas com as operações de abrir e criar
 */

/*
 Ponteiro do tipo FILE Arquivo
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @rief Abre o arquivo .geo para leitura.
/// @param arquivo Ponteiro para o nome do arquivo que será aberto.
/// @return Ponteiro para o arquivo que foi aberto.
Arquivo abrirGeo(Nome arquivo);

/// @brief Cria formas e estilo lidos do (.geo) e coloca as formas na lista.
/// @param geo Ponteiro para o arquivo (.geo) que será lido.
/// @param forma Ponteiro para a Lista (forma) que receberá as formas.
/// @param EstiloPonteiro Ponteiro para o Estilo global do texto (será alocado se o comando 'ts' for encontrado).
void criarFormasNaLista(Arquivo geo,Lista forma,Estilo* EstiloPonteiro);

#endif //GEO_H