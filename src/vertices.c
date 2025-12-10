//
// Created by natha on 18/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>

#include "segmento.h"
#include "forma.h"
#include "lista.h"
#include "vertices.h"

#define M_PI 3.14159265358979323846

typedef struct {
    double x,y;
    double angulo;
    double distancia;
    TipoVertice tipo;
    Segmento original;
}vertice;

Vertice CriarVertice(double x, double y, double angulo, double distancia,TipoVertice tipo, Segmento original) {
    vertice* v = (vertice*) malloc(sizeof(vertice));

    if(v == NULL){
        printf("Erro ao alocar memória ao CriarVertice!\n");

        perror("Motivo do erro");
        exit(1);
    }

    v->x = x;
    v->y = y;
    v->angulo = angulo;
    v->distancia = distancia;
    v->tipo = tipo;
    v->original = original;

    return v;
}

double getXVertice(Vertice v) {
    return ((vertice*)v)->x;
}

double getYVertice(Vertice v) {
    return ((vertice*)v)->y;
}

double getAnguloVertice(Vertice v) {
    return ((vertice*)v)->angulo;
}

double getDistanciaVertice(Vertice v) {
    return ((vertice*)v)->distancia;
}

TipoVertice getTipoVertice(Vertice v) {
    return ((vertice*)v)->tipo;
}

Segmento getSegmentoVertice(Vertice v) {
    return ((vertice*)v)->original;
}

void eliminarVertice(Vertice v) {
    vertice* ver = (vertice*)v;
    free(ver);
}

Vetor CriarVetorVertices(Lista anteparo, double xBomba, double yBomba, int* qtdVertices) {

    int qtdSegmentos = getTamanhoLista(anteparo);
    *qtdVertices = qtdSegmentos * 2;

    Vertice* Vertices = malloc(sizeof(Vertice) * (*qtdVertices));
    if (Vertices == NULL) {
        printf("Erro ao alocar memória ao CriarVetorVertices!\n");

        perror("Motivo do erro");
        exit(1);
    }

    int i = 0;
    pont atual = getPrimeiroElementoLista(anteparo);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);
        Segmento seg = getDadosForma(pacote);

        double x1 = getX1Segmento(seg);
        double y1 = getY1Segmento(seg);
        double x2 = getX2Segmento(seg);
        double y2 = getY2Segmento(seg);

        double ang1 = atan2(y1 - yBomba, x1 - xBomba);
        double ang2 = atan2(y2 - yBomba, x2 - xBomba);

        if (ang1 < 0) ang1 += 2 * M_PI;
        if (ang2 < 0) ang2 += 2 * M_PI;

        double dist1 = hypot(x1 - xBomba, y1 - yBomba);
        double dist2 = hypot(x2 - xBomba, y2 - yBomba);

        if (ang1 < ang2) {
            Vertices[i] = CriarVertice(x1, y1, ang1, dist1, INICIO, seg);
            i++;

            Vertices[i] = CriarVertice(x2, y2, ang2, dist2, FIM, seg);
            i++;
        }
        else {
            Vertices[i] = CriarVertice(x2, y2, ang2, dist2, INICIO, seg);
            i++;

            Vertices[i] = CriarVertice(x1, y1, ang1, dist1, FIM, seg);
            i++;
        }

        atual = getProximoElementoLista(atual);
    }
    return (Vetor)Vertices;
}

