//
// Created by natha on 13/11/2025.
//

#ifndef ARVORE_H
#define ARVORE_H

/*
 Módulo encarregado de executar e coordenar uma árvore com operações de criar, inserir, remover, get, buscar, 'arvoreavazia' e liberar
 */

/*
 Ponteiro void Arvore
 */
typedef void* Arvore;
typedef struct No* pontArvore;

typedef int (*Comparador) (Segmento a, Segmento b);

/// @brief Cria uma árvore vazia.
/// @param c Ponteiro de Função para comparação.
/// @return Ponteiro para nova árvore criada.
/// @warning
Arvore CriarArvore(Comparador c);

/// @brief Insere um Segmento na árvore.
/// @param a Ponteiro para árvore a qual o Segmento será ligado.
/// @param s Ponteiro para o Segmento que será ligado.
/// @warning
void inserirArvore(Arvore a, Segmento s);

/// @brief
/// @param no
/// @return
/// @warning
pontArvore pontMaisEsquerda(pontArvore no);

/// @brief Remove o Segmento da árvore e libera o nó da árvore.
/// @param a Ponteiro para árvore que será retirada o Segmento.
/// @param s Ponteiro para o Segmento que será removido.
/// @return Ponteiro para o Segmento que foi removido.
/// @warning
Segmento removerArvore(Arvore a, Segmento s);

/// @brief Pega o Segmento mais a esquerda da árvore.
/// @param a Ponteiro para árvore que será analisada.
/// @return Ponteiro para o Segmento mais a esquerda.
/// @warning
Segmento getMaisEsquerdaDado(Arvore a);

/// @brief Pega um Segmento específico da árvore.
/// @param a Ponteiro para a árvore que será analisada.
/// @param s Ponteiro para o Segmento que será buscado.
/// @return Ponteiro para o Segmento que foi buscado.
/// @warning
Segmento buscarArvore(Arvore a, Segmento s);

/// @brief Verifica se a árvore esta vazia.
/// @param a Ponteiro para árvore que será verificada.
/// @return True (1) se a árvore estiver vazia, ou False (0) se a árvore não estiver vazia.
/// @warning
bool arvorevazia(Arvore a);

/// @brief Libera a memória da árvore e de todos os seus elementos (nós).
/// @param a Ponteiro para árvore que será liberada.
/// @warning
void liberarArvore(Arvore a);

#endif //ARVORE_H