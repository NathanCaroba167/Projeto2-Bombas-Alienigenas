//
// Created by natha on 19/09/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "texto.h"

typedef struct{
    char* fFamily;
    char* fWeight;
    char* fSize;
}estilo; // Corresponde ao Estilo

typedef struct{
    int id;
    double x,y;
    char* corB; // Cor de Borda
    char* corP; // Cor de Preenchimento
    char a;     // Âncora ('i', 'm', 'f')
    char* txto; // Conteúdo do texto
}texto; // Corresponde ao Texto

Estilo CriarEstilo(char* fFamily, char* fWeight, char* fSize) {
    estilo* e = (estilo*)malloc(sizeof(estilo));
    if (e == NULL) {
        printf("Erro ao alocar memória ao criarEstilo!\n");

        perror("Motivo do erro");
        exit(1);
    }

    e->fFamily = (char*) malloc (strlen(fFamily) + 1);
    if (e->fFamily == NULL) {
        printf("Erro ao alocar memória ao criar fonte Family!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(e->fFamily,fFamily);

    e->fWeight = (char*) malloc (strlen(fWeight) + 1);
    if (e->fWeight == NULL) {
        printf("Erro ao alocar memória ao criar fonte Weight!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(e->fWeight,fWeight);

    e->fSize = (char*) malloc (strlen(fSize) + 1);
    if (e->fSize == NULL) {
        printf("Erro ao alocar memória ao criar fonte Size!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(e->fSize,fSize);

    return e;
}

Texto CriarTexto(int id, double x, double y, char* corB, char* corP, char a, char* txto) {
    texto* t = (texto*)malloc(sizeof(texto));

    if (t == NULL) {
        printf("Erro ao alocar memória ao criarTexto!\n");

        perror("Motivo do erro");
        exit(1);
    }

    t->id = id;
    t->x = x;
    t->y = y;
    t->corB = (char*) malloc (strlen(corB) + 1);
    if (t->corB == NULL) {
        printf("Erro ao alocar memória ao criar cor de borda do texto!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(t->corB,corB);

    t->corP = (char*) malloc (strlen(corP) + 1);
    if (t->corP == NULL) {
        printf("Erro ao alocar memória ao criar cor de preenchimento do texto!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(t->corP,corP);

    t->a = a;
    t->txto = (char*) malloc (strlen(txto) + 1);
    if (t->txto == NULL) {
        printf("Erro ao alocar memória ao criar conteúdo do texto!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(t->txto,txto);

    return t;
}

int getIDTexto(Texto t) {
    return ((texto*)t)->id;
}

void setIDTexto(Texto t, int id) {
    ((texto*)t)->id = id;
}

double getXTexto(Texto t) {
    return ((texto*)t)->x;
}

void setXTexto(Texto t, double x) {
    ((texto*)t)->x = x;
}

double getYTexto(Texto t) {
    return ((texto*)t)->y;
}

void setYTexto(Texto t, double y) {
    ((texto*)t)->y = y;
}

char* getCorBTexto(Texto t) {
    return ((texto*)t)->corB;
}

void setCorBTexto(Texto t,char* corB) {
    texto* tex = (texto*)t;
    tex->corB = realloc (tex->corB,strlen(corB) + 1);
    if (tex->corB == NULL) {
        printf("Erro ao realocar memória da cor de borda do texto!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(tex->corB,corB);
}

char* getCorPTexto(Texto t) {
    return ((texto*)t)->corP;
}

void setCorPTexto(Texto t,char* corP) {
    texto* tex = (texto*)t;
    tex->corP = realloc (tex->corP,strlen(corP) + 1);
    if (tex->corP == NULL) {
        printf("Erro ao realocar memória da cor de preenchimento do texto!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(tex->corP,corP);
}

char getATexto(Texto t) {
    return ((texto*)t)->a;
}

void setATexto(Texto t, char a) {
    ((texto*)t)->a = a;
}

char* getTxtoTexto(Texto t) {
    return ((texto*)t)->txto;
}

void setTxtoTexto(Texto t, char* txto) {
    texto* tex = (texto*)t;
    tex->txto = realloc (tex->txto,strlen(txto) + 1);
    if (tex->txto == NULL) {
        printf("Erro ao realocar memória do conteúdo do texto!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(tex->txto,txto);
}

char* getFontFamilyTexto(Estilo e) {
    return ((estilo*)e)->fFamily;
}

void setFontFamilyTexto(Estilo e, char* family) {
    estilo* est = (estilo*)e;
    est->fFamily = realloc (est->fFamily,strlen(family) + 1);
    if (est->fFamily == NULL) {
        printf("Erro ao realocar memória da fonte Family!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy (est->fFamily,family);
}

char* getFontWeightTexto(Estilo e) {
    return ((estilo*)e)->fWeight;
}

void setFontWeightTexto(Estilo e, char* weight) {
    estilo* est = (estilo*)e;
    est->fWeight = realloc (est->fWeight,strlen(weight) + 1);
    if (est->fWeight == NULL) {
        printf("Erro ao realocar memória da fonte Weight!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy (est->fWeight,weight);
}

char* getFontSizeTexto(Estilo e) {
    return ((estilo*)e)->fSize;
}

void setFontSizeTexto(Estilo e, char* size) {
    estilo* est = (estilo*)e;
    est->fSize = realloc (est->fSize,strlen(size) + 1);
    if (est->fSize == NULL) {
        printf("Erro ao realocar memória da fonte Size!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy (est->fSize,size);
}

size_t quantidadeCaracteresTexto(Texto t) {
    return strlen(((texto*)t)->txto);
}

double calcAreaTexto(Texto t) {
    // A área é calculada como 20 * número de caracteres
    return 20 * (double) strlen(getTxtoTexto(t));
}

void eliminarEstilo(Estilo e) {
    estilo* est = (estilo*)e;
    free(est->fFamily);
    free(est->fWeight);
    free(est->fSize);
    free(est);
}

void eliminarTexto(Texto t) {
    texto* tex = (texto*)t;
    free(tex->corB);
    free(tex->corP);
    free(tex->txto);
    free(tex);
}