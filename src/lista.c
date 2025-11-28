//
// Created by natha on 13/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "forma.h"
#include "lista.h"

typedef struct Elemento{
    Pacote form;
    struct Elemento *prox;
}Elemento;

typedef Elemento* pont;

typedef struct{
    pont inicio;
}lista;

Lista iniciarLista() {
    lista* l = (lista*)malloc(sizeof(lista));
    l->inicio = NULL;
    return l;
}

void inserirListaInicio(Lista l, Pacote p){
    lista* ls = (lista*)l;
    pont novo = malloc(sizeof(Elemento));
    if(novo == NULL){
        printf("Erro ao alocar elemento\n");
        return;
    }
    novo->form = p;
    novo->prox = ls->inicio;
    ls->inicio = novo;
}

void inserirListaFim(Lista l, Pacote p) {
    lista* ls = (lista*)l;
    pont novo = malloc(sizeof(Elemento));
    if(novo == NULL) {
        printf("Erro ao alocar elemento\n");
        return;
    }
    novo->form = p;
    novo->prox = NULL;

    if(ls->inicio == NULL){
        ls->inicio = novo;
        return;
    }

    pont atual = ls->inicio;
    while(atual->prox != NULL){
        atual = atual->prox;
    }
    atual->prox = novo;
}

void remover_elemento(Lista l, Pacote p){
    lista* ls = (lista*)l;
    if(ls->inicio == NULL){
        printf("Nao e possivel excluir algo de uma lista vazia\n");
        exit(1);
    }
    pont atual = ls->inicio;
    pont anterior = NULL;
    while(atual != NULL && atual->form != p){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual == NULL){
        exit(1);

    }
    if(anterior == NULL){
        ls->inicio = atual->prox;
    }else{
        anterior->prox = atual->prox;
    }
    free(atual);
}

Pacote getPorIdLista(Lista l, int id) {
    lista* ls = (lista*)l;
    pont atual = ls->inicio;
    while(atual != NULL){
        if(getIDForma(atual->form) == id){
            printf("Elemento %d encontrado!\n",id);
            return atual;
        }
        atual = atual->prox;
    }
    printf("Elemento %d nao encontrado!\n",id);
    return NULL;
}

void removerPorIdLista(Lista l, int id) {
    lista* ls = (lista*)l;
    if(ls->inicio == NULL){
        printf("Nao e possivel excluir algo de uma lista vazia\n");
        exit(1);
    }
    pont atual = ls->inicio;
    pont anterior = NULL;
    while(atual != NULL && getIDForma(atual->form) != id){
        anterior = atual;
        atual = atual->prox;
    }
    if(atual == NULL){
        exit(1);
    }
    if(anterior == NULL){
        ls->inicio = atual->prox;
    }else{
        anterior->prox = atual->prox;
    }
    free(atual);
}

pont getProximoElementoLista(pont p) {
    return p->prox;
}

pont getPrimeiroElementoLista(Lista l) {
    lista* LISTA = (lista*)l;
    return LISTA->inicio;
}

pont getUltimoElementoLista(Lista l) {
    lista* LISTA = (lista*)l;
    if (LISTA->inicio == NULL) {
        return NULL;
    }

    pont atual = LISTA->inicio;
    while(atual->prox != NULL){
        atual = atual->prox;
    }
    return atual;
}

bool listavazia(Lista l) {
    lista* LISTA = (lista*)l;
    return LISTA->inicio == NULL ? true : false;
}

void liberarLista(Lista l){
    lista* ls = (lista*)l;
    pont atual = ls->inicio;
    while(atual != NULL){
        ls->inicio = atual->prox;
        free(atual);
        atual = ls->inicio;
    }
    ls->inicio = NULL;
}