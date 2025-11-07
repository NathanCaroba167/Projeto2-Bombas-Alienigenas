//
// Created by natha on 19/09/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "linha.h"

typedef struct{
    int id;
    double x1,y1;
    double x2,y2;
    char* cor; // Cor da linha (alocada dinamicamente)
}linha;

Linha CriarLinha(int id,double x1,double y1, double x2,double y2,char* cor) {
    linha* l = (linha*)malloc(sizeof(linha));
    if(l == NULL) {
        printf("Erro ao alocar memória ao criarLinha!\n");

        perror("Motivo do erro");
        exit(1);
    }

    l->id = id;
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;

    l->cor = (char*) malloc (strlen(cor) + 1);
    if (l->cor == NULL) {
        printf("Erro ao alocar memória ao criar cor da linha!\n");
        free(l); // Libera a struct principal

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(l->cor,cor);
    return l;
}

int getIDLinha(Linha l) {
    return ((linha*)l)->id;
}

void setIDLinha(Linha l, int id) {
    ((linha*)l)->id = id;
}

double getX1Linha(Linha l) {
    return ((linha*)l)->x1;
}

void setX1Linha(Linha l, double x1) {
    ((linha*)l)->x1 = x1;
}

double getY1Linha(Linha l) {
    return ((linha*)l)->y1;
}

void setY1Linha(Linha l, double y1) {
    ((linha*)l)->y1 = y1;
}

double getX2Linha(Linha l) {
    return ((linha*)l)->x2;
}

void setX2Linha(Linha l, double x2) {
    ((linha*)l)->x2 = x2;
}

double getY2Linha(Linha l) {
    return ((linha*)l)->y2;
}

void setY2Linha(Linha l, double y2) {
    ((linha*)l)->y2 = y2;
}

char* getCorLinha(Linha l) {
    return ((linha*)l)->cor;
}

void setCorLinha(Linha l, char* cor) {
    linha* lin = (linha*)l;
    lin->cor = realloc (lin->cor,strlen(cor) + 1);
    if (lin->cor == NULL) {
        printf("Erro ao realocar memoria!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(lin->cor,cor);
}

char* CorComplementarLinha(Linha l) {
    linha* lin = (linha*)l;
    char* corB = lin->cor;
    // Aloca 8 bytes: # + RRGGBB + \0
    char* corComplementar = (char*) malloc (8 * sizeof(char));
    if (corComplementar == NULL) {
        printf("Erro ao alocar memoria ao criar cor complementar!\n");

        perror("Motivo do erro");
        exit(1);
    }
    if (corB == NULL) {
        // Cor padrão se a cor for nula
        strcpy(corComplementar,"#FFFFFF");
        return corComplementar;
    }

    int r, g, b;

    // Lida com o '#' opcional
    if (corB[0] == '#') {
        sscanf(corB + 1,"%2x%2x%2x", &r, &g, &b);
    }else {
        sscanf(corB ,"%2x%2x%2x", &r, &g, &b);
    }

    // Calcula a cor complementar (inversão)
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;

    // Formata a string de saída
    sprintf(corComplementar, "#%02X%02X%02X", r, g, b);
    return corComplementar;
}

double calcAreaLinha(Linha l) {
    // 2 * comprimento da linha
    return 2 * sqrt(pow(getX1Linha(l)-getX2Linha(l),2) + pow(getY1Linha(l)-getY2Linha(l),2));
}

void eliminarLinha(Linha l) {
    linha* lin = (linha*)l;
    // Libera a string da cor
    free(lin->cor);
    // Libera a struct principal
    free(lin);
}