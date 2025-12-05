//
// Created by natha on 13/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "segmento.h"

#include "forma.h"

typedef struct {
    int id;
    double x1, y1;
    double x2, y2;
    char* cor;
    TipoSegmento tipo;
}segmento;

Segmento CriarSegmento(int id, double x1, double y1, double x2, double y2, char* cor,TipoSegmento tipo) {
    segmento* seg = (segmento*) malloc (sizeof(segmento));
    if (seg == NULL) {
        printf("Erro ao alocar memória ao criarSegmento!\n");
        exit(1);
    }

    seg->id = id;
    seg->x1 = x1;
    seg->y1 = y1;
    seg->x2 = x2;
    seg->y2 = y2;

    seg->cor = (char*) malloc (strlen(cor) + 1);
    if (seg->cor == NULL) {
        printf("Erro ao alocar memória ao criar cor do segmento!\n");
        free(seg);

        exit(1);
    }
    strcpy (seg->cor, cor);

    seg->tipo = tipo;

    return seg;
}

int getIDSegmento(Segmento s) {
    return ((segmento*)s)->id;
}

void setIDSegmento(Segmento s, int id) {
    ((segmento*)s)->id = id;
}

double getX1Segmento(Segmento s) {
    return ((segmento*)s)->x1;
}

double getY1Segmento(Segmento s) {
    return ((segmento*)s)->y1;
}

double getX2Segmento(Segmento s) {
    return ((segmento*)s)->x2;
}

double getY2Segmento(Segmento s) {
    return ((segmento*)s)->y2;
}

void setP1Segmento(Segmento s, double x1, double y1) {
    ((segmento*)s)->x1 = x1;
    ((segmento*)s)->y1 = y1;
}

void setP2Segmento(Segmento s, double x2, double y2) {
    ((segmento*)s)->x2 = x2;
    ((segmento*)s)->y2 = y2;
}

char* getCorSegmento(Segmento s) {
    return ((segmento*)s)->cor;
}

void setCorSegmento(Segmento s, char* cor) {
    segmento* seg = (segmento*)s;
    seg->cor = realloc (seg->cor,strlen(cor) + 1);
    if (seg->cor == NULL) {
        printf("Erro ao realocar memoria!\n");

        perror("Motivo do erro");
        exit(1);
    }
    strcpy(seg->cor,cor);
}

TipoSegmento getTipoSegmento(Segmento s) {
    return ((segmento*)s)->tipo;
}

double calcTamanhoSegmento(Segmento s) {
    segmento* seg = (segmento*)s;
    double dx = seg->x2 - seg->x1;
    double dy = seg->y2 - seg->y1;
    return sqrt(dx*dx + dy*dy);
}

double orientacaoTresPontos(double x1, double y1, double x2, double y2, double px, double py) {
    return (x2 - x1) * (py - y1) - (y2 - y1) * (px - x1);
}

double orientacaoPontoSegmento(Segmento s, double px, double py) {
    segmento* seg = (segmento*)s;
    return orientacaoTresPontos(seg->x1, seg->y1, seg->x2, seg->y2,px,py);
}

void eliminarSegmento(Segmento s) {
    segmento* seg = (segmento*) s;
    free(seg->cor);
    free(seg);
}
