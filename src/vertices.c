//
// Created by natha on 18/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "forma.h"
#include "lista.h"
#include "texto.h"
#include "geo.h"
#include "segmento.h"
#include "vertices.h"

#include <math.h>

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

Vetor CriarVetorVertices(Lista anteparo, double xBomba, double yBomba) {

    int qtdSegmentos = getTamanhoLista(anteparo);
    int qtdVertices = qtdSegmentos * 2;

    vertice* Vertices = malloc(sizeof(Vertice) * qtdVertices);
    if (Vertices == NULL) {
        printf("Erro ao alocar memoria ao criarEstoqueVertices!\n");

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

        double dist1 = hypot(x1 - xBomba, y1 - yBomba);
        double dist2 = hypot(x2 - xBomba, y2 - yBomba);

        if (ang1 < ang2) {
            Vertices[i].x = x1;
            Vertices[i].y = y1;
            Vertices[i].angulo = ang1;
            Vertices[i].distancia = dist1;
            Vertices[i].tipo = INICIO;
            Vertices[i].original = seg;
            i++;

            Vertices[i].x = x2;
            Vertices[i].y = y2;
            Vertices[i].angulo = ang2;
            Vertices[i].distancia = dist2;
            Vertices[i].tipo = FIM;
            Vertices[i].original = seg;
            i++;
        }
        else {
            Vertices[i].x = x2;
            Vertices[i].y = y2;
            Vertices[i].angulo = ang2;
            Vertices[i].distancia = dist2;
            Vertices[i].tipo = INICIO;
            Vertices[i].original = seg;
            i++;

            Vertices[i].x = x1;
            Vertices[i].y = y1;
            Vertices[i].angulo = ang1;
            Vertices[i].distancia = dist1;
            Vertices[i].tipo = FIM;
            Vertices[i].original = seg;
            i++;
        }

        atual = getProximoElementoLista(atual);
    }
    return Vertices;
}

