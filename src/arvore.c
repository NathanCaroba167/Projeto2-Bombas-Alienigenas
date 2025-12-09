//
// Created by natha on 13/11/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <error.h>

#include "segmento.h"
#include "arvore.h"

typedef struct No {
    Segmento segmento;
    struct No* esquerdo;
    struct No* direito;
}No;

typedef No* pontArvore;

typedef struct{
    pontArvore raiz;
    Comparador comp;
}arvore;

Arvore CriarArvore(Comparador c) {
    arvore* a = (arvore*)malloc(sizeof(arvore));
    if(a == NULL){
        printf("Erro ao alocar elemento\n");

        perror("Motivo do erro");
        exit(1);
    }

    a->raiz = NULL;
    a->comp = c;

    return a;
}

pontArvore inserirRec(pontArvore raiz, Segmento s, Comparador comp) {
    if(raiz == NULL) {
        pontArvore novo = malloc(sizeof(No));
        if (novo == NULL) {
            printf("Erro ao alocar memória ao inserirRec!\n");

            perror("Motivo do erro");
            exit(1);
        }

        novo->segmento = s;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        return novo;
    }

    int r = comp(s, raiz->segmento);
    if(r < 0) {
        raiz->esquerdo = inserirRec(raiz->esquerdo, s, comp);
    } else {
        raiz->direito = inserirRec(raiz->direito, s, comp);
    }
    return raiz;
}

void inserirArvore(Arvore a, Segmento s) {
    arvore* ar = (arvore*)a;
    if (ar != NULL) {
        ar->raiz = inserirRec(ar->raiz, s, ar->comp);
    }
}

pontArvore pontMaisEsquerda(pontArvore no) {
    pontArvore atual = no;
    while (atual && atual->esquerdo != NULL) {
        atual = atual->esquerdo;
    }
    return atual;
}

pontArvore removerRec(pontArvore raiz, Segmento s, Comparador comp, Segmento* itemRetorno) {
    if(raiz == NULL) return NULL;//

    int r = comp(s, raiz->segmento);

    if(r < 0) {
        raiz->esquerdo = removerRec(raiz->esquerdo, s, comp, itemRetorno);
    } else if(r > 0) {
        raiz->direito = removerRec(raiz->direito, s, comp, itemRetorno);
    } else {
        if(itemRetorno != NULL) {
            *itemRetorno = raiz->segmento;
        }
        if (raiz->esquerdo == NULL) {
            pontArvore temp = raiz->direito;
            free(raiz);
            return temp;
        } else if (raiz->direito == NULL) {
            pontArvore temp = raiz->esquerdo;
            free(raiz);
            return temp;
        }

        pontArvore temp = pontMaisEsquerda(raiz->direito);
        raiz->segmento = temp->segmento;
        raiz->direito = removerRec(raiz->direito,temp->segmento,comp,NULL);
    }
    return raiz;
}

Segmento removerArvore(Arvore a, Segmento s) {
    arvore* ar = (arvore*)a;
    void* itemRecuperado = NULL;
    if(ar->raiz != NULL) {
        ar->raiz = removerRec(ar->raiz, s, ar->comp, &itemRecuperado);
    }
    return itemRecuperado;
}

Segmento getMaisEsquerdaDado(Arvore a) {
    arvore* ar = (arvore*)a;
    if (arvorevazia(a)) {
        return NULL;
    }
    pontArvore atual = ar->raiz;
    while (atual->esquerdo != NULL) {
        atual = atual->esquerdo;
    }
    return atual->segmento;
}

Segmento buscarRec(pontArvore raiz, Segmento s, Comparador comp) {
    if (raiz == NULL) {
        return NULL;
    }
    int r = comp(s, raiz->segmento);
    if (r == 0) {
        return raiz->segmento;
    }
    if (r < 0 ) {
        return buscarRec(raiz->esquerdo, s, comp);
    }
    return buscarRec(raiz->direito, s, comp);
}

Segmento buscarArvore(Arvore a, Segmento s) {
    arvore* ar = (arvore*)a;
    if (ar != NULL) {
        return buscarRec(ar->raiz, s, ar->comp);
    }
    return NULL;
}

bool arvorevazia(Arvore a) {
    arvore* ARVORE = (arvore*)a;
    return ARVORE->raiz == NULL ? true : false;
}

void liberarRec(pontArvore raiz) {
    if(raiz == NULL) return;
    liberarRec(raiz->esquerdo);
    liberarRec(raiz->direito);
    free(raiz);
}

void liberarArvore(Arvore a) {
    arvore* arv = (arvore*)a;
    if (arv != NULL) {
        if (arv->raiz != NULL) {
            liberarRec(arv->raiz);
        }
        free(arv);
    }
}