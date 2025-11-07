//
// Created by natha on 02/09/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "retangulo.h"

typedef struct{
    int id;
    double x,y; // Ponto âncora (canto inferior esquerdo)
    double w,h; // Largura e Altura
    char* corB; // Cor de Borda (alocada dinamicamente)
    char* corP; // Cor de Preenchimento (alocada dinamicamente)
}retangulo;

Retangulo CriarRetangulo(int id,double x,double y,double w,double h,char* corB,char* corP) {
    retangulo* r = (retangulo*)malloc(sizeof(retangulo));

    if(r == NULL) {
        printf("Erro ao alocar memória ao criarRetangulo!\n");

        perror("Motivo do erro");
        exit(1);
    }

    r->id = id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;

    // Alocação de Cor de Borda
    r->corB = (char*) malloc (strlen(corB) + 1);
    if (r->corB == NULL) {
        printf("Erro ao alocar memória ao criar cor de borda do retângulo!\n");
        free(r); // Libera a struct principal

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(r->corB,corB);

    // Alocação da Cor de Preenchimento
    r->corP = (char*) malloc (strlen(corP) + 1);
    if (r->corP == NULL) {
        printf("Erro ao alocar memória ao criar cor de preenchimento do retângulo!\n");
        free(r->corB); // Libera o que foi alocado
        free(r);

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(r->corP,corP);
    return r;
}

int getIDRetangulo(Retangulo r) {
    return ((retangulo*)r)->id;
}

void setIDRetangulo(Retangulo r,int id) {
    ((retangulo*)r)->id = id;
}

double getXRetangulo(Retangulo r) {
    return ((retangulo*)r)->x;
}

void setXRetangulo(Retangulo r,double x) {
    ((retangulo*)r)->x = x;

}
double getYRetangulo(Retangulo r) {
    return ((retangulo*)r)->y;

}

void setYRetangulo(Retangulo r,double y) {
    ((retangulo*)r)->y = y;

}

double getWRetangulo(Retangulo r) {
    return ((retangulo*)r)->w;

}

void setWRetangulo(Retangulo r,double w) {
    ((retangulo*)r)->w = w;

}

double getHRetangulo(Retangulo r) {
    return ((retangulo*)r)->h;

}

void setHRetangulo(Retangulo r,double h) {
    ((retangulo*)r)->h = h;

}

char* getCorBRetangulo(Retangulo r) {
    return ((retangulo*)r)->corB;

}

void setCorBRetangulo(Retangulo r,char* corB) {
    retangulo* retan = (retangulo*)r;
    // Realoca para o novo tamanho (strlen(corB) + 1)
    retan->corB = realloc (retan->corB,strlen(corB) + 1);
    if (retan->corB == NULL) {
        printf("Erro ao realocar memória da cor de borda do retângulo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(retan->corB,corB);
}

char* getCorPRetangulo(Retangulo r) {
    return ((retangulo*)r)->corP;

}

void setCorPRetangulo(Retangulo r,char* corP) {
    retangulo* retan = (retangulo*)r;
    // Realoca para o novo tamanho (strlen(corB) + 1)
    retan->corP = realloc (retan->corP,strlen(corP) + 1);
    if (retan->corP == NULL) {
        printf("Erro ao realocar memória da cor de preenchimento do retângulo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(retan->corP,corP);
}

double calcAreaRetangulo(Retangulo r) {
    return getWRetangulo(r) * getHRetangulo(r);
}

void eliminarRetangulo(Retangulo r) {
    retangulo* retan = (retangulo*)r;
    // Libera as strings de cor
    free(retan->corB);
    free(retan->corP);
    // Libera a struct principal
    free(retan);
}

