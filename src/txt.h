//
// Created by natha on 16/10/2025.
//

#ifndef TXT_H
#define TXT_H

/*
 Módulo encarregado de criar um arquivo (.txt) e reportar os resultados de comandos com as operações de abrir e reportar
 */

/*
 Ponteiro do tipo FILE Arquivo
 Ponteiro char Nome
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Cria e abre o arquivo TXT para escrita.
/// @param arquivo Ponteiro para o nome do arquivo que será criado e aberto.
/// @return Ponteiro para o arquivo (FILE*) que será criado e aberto.
/// @warning
Arquivo abrirTXT(Nome arquivo);

/// @brief Escreve no arquivo TXT os dados da forma recebida.
/// @param txt Ponteiro para o arquivo que será escrito os dados.
/// @param p Ponteiro para a forma (Pacote) que os dados seão avaliados.
/// @warning
void reportarForma(Arquivo txt,Pacote p);

#endif //TXT_H