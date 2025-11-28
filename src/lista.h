//
// Created by natha on 13/11/2025.
//

#ifndef LISTA_H
#define LISTA_H

/*
 Módulo encarregado de executar e coordenar uma lista com operações de iniciar, inserir, remover, getPorID e removerPorId, 'listavazia' e liberar
 */

/*
 Ponteiro void Lista
 */
typedef void* Lista;
typedef struct Elemento* pont;

/// @brief Inicializa uma lista vazia.
/// @return Ponteiro para nova lista iniciada.
/// @warning
Lista iniciarLista();

/// @brief Lista um Pacote no inicio da lista.
/// @param l Ponteiro para lista a qual o Pacote será listado.
/// @param p Ponteiro para o Pacote que será listado.
/// @warning
void inserirListaInicio(Lista l, Pacote p);

/// @brief Lista um Pacote no fim da lista.
/// @param l Ponteiro para lista a qual o Pacote será listado.
/// @param p Ponteiro para o Pacote que será listado.
/// @warning
void inserirListaFim(Lista l, Pacote p);

/// @brief Remove o Pacote da lista e libera o nó da lista.
/// @param l Ponteiro para lista que será retirada a forma.
/// @param p Ponteiro para o Pacote que será removido.
/// @warning
void remover_elemento(Lista l, Pacote p);

/// @brief Pega o Pacote do elemento da lista.
/// @param l Ponteiro para o elemento (nó) da lista.
/// @param id Identificador único que se refere a forma que será pega.
/// @return Ponteiro para o Pacote que foi pego do elemento.
/// @warning
Pacote getPorIdLista(Lista l, int id);

/// @brief Remove o Pacote de referente ID da lista e libera o nó da lista.
/// @param l Ponteiro para lista que será retirada a forma.
/// @param id Identificador único que se refere a forma que será removida.
/// @warning
void removerPorIdLista(Lista l, int id);

/// @brief Pega o próximo elemento (nó) da lista a partir do elemento anterior.
/// @param p Ponteiro para o elemento anterior.
/// @return Ponteiro para o próximo elemento.
/// @warning
pont getProximoElementoLista(pont p);

/// @brief Pega o primeiro elemento (nó) da lista.
/// @param l Ponteiro para a lista analisada.
/// @return Ponteiro para o primeiro elemento da lista.
/// @warning
pont getPrimeiroElementoLista(Lista l);

/// @brief Pega o último elemento (nó) da lista.
/// @param l Ponteiro para a lista analisada.
/// @return Ponteiro para o último elemento.
/// @warning
pont getUltimoElementoLista(Lista l);

/// @brief Verifica se a lista esta vazia.
/// @param l Ponteiro para lista que será verificada.
/// @return True (1) se a lista estiver vazia, ou False (0) se a lista não estiver vazia.
/// @warning
bool listavazia(Lista l);

/// @brief Libera a memória da lista, de todos os seus elementos (nós) e de todos os Pacotes nela contidos.
/// @param l Ponteiro para lista que será liberada.
/// @warning
void liberarLista(Lista l);

#endif //LISTA_H