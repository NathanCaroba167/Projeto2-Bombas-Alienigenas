//
// Created by natha on 28/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "segmento.h"
#include "forma.h"

#include "lista.h"
#include "poligono.h"

#include "vertices.h"

typedef struct {
    double x, y;
}ponto;

typedef struct {
    Lista pontos;
}poligono;

Ponto CriarPonto(double x, double y) {
    ponto* p = (ponto*)malloc(sizeof(ponto));
    p->x = x;
    p->y = y;
    return p;
}

double getXPonto(Ponto p) {
    return ((ponto*)p)->x;
}

double getYPonto(Ponto p) {
    return ((ponto*)p)->y;
}

void eliminarPonto(Ponto p) {
    free(p);
}

Poligono CriarPoligono() {
    poligono* poly = malloc(sizeof(poligono));
    poly->pontos = iniciarLista();
    return poly;
}

void adicionarPontoAoPoligono(Poligono p, Ponto pt) {
    poligono* poli = (poligono*)p;
    inserirListaFim(poli->pontos, CriarPacote(pt,PONTO));
}

Lista getListaPontosPoligono(Poligono p) {
    return ((poligono*)p)->pontos;
}

void eliminarPoligono(Poligono p) {
    poligono* poli = (poligono*)p;
    liberarLista(poli->pontos);
    free(poli);
}

bool pontoDentroPoligono(Poligono p, double px, double py) {
    poligono* poli = (poligono*)p;

    int n = getTamanhoLista(poli->pontos);
    if (n < 3) {
        return false;
    }

    Ponto* vet = malloc(sizeof(Ponto) * n);
    int k = 0;

    pont atual = getPrimeiroElementoLista(poli->pontos);
    while (atual != NULL) {
        Pacote pack = getPacoteElementoLista(atual);

        Ponto pt = getDadosForma(pack);
        vet[k] = pt;
        k++;
        atual = getProximoElementoLista(atual);
    }

    bool dentro = false;
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        Ponto pi = vet[i];
        Ponto pj = vet[j];

        if (((getYPonto(pi) > py) != (getYPonto(pj) > py)) &&
            (px < (getXPonto(pj) - getXPonto(pi)) * (py - getYPonto(pi)) / (getYPonto(pj) - getYPonto(pi)) + getXPonto(pi))) {
            dentro = !dentro;
        }
        j = i;
    }

    free(vet);
    return dentro;
}

bool verificarSobreposicao(Poligono p, Pacote forma) {
    poligono* poli = (poligono*)p;

    Forma form = getDadosForma(forma);
    TipoForma tipo = getTipoForma(forma);

    switch (tipo) {
        case RETANGULO: {
            double x = getXRetangulo(form);
            double y = getYRetangulo(form);
            double w = getWRetangulo(form);
            double h = getHRetangulo(form);

            if (pontoDentroPoligono(poli, x, y)) return true;
            if (pontoDentroPoligono(poli, x+w, y)) return true;
            if (pontoDentroPoligono(poli, x, y+h)) return true;
            if (pontoDentroPoligono(poli, x+w, y+h)) return true;

            return false;
        }
        case CIRCULO: {
            double x = getXCirculo(forma);
            double y = getYCirculo(forma);

            return pontoDentroPoligono(p, x, y);
        }
        case LINHA: {
            double x1 = getX1Linha(forma);
            double y1 = getY1Linha(forma);
            double x2 = getX2Linha(forma);
            double y2 = getY2Linha(forma);
            return pontoDentroPoligono(poli, x1, y1) || pontoDentroPoligono(p, x2, y2);
        }
        case SEGMENTO: {
            double x1 = getX1Segmento(forma);
            double y1 = getY1Segmento(forma);
            double x2 = getX2Segmento(forma);
            double y2 = getY2Segmento(forma);

            return pontoDentroPoligono(poli, x1, y1) || pontoDentroPoligono(p, x2, y2);
        }
        case TEXTO: {
             double x = getXTexto(forma);
             double y = getYTexto(forma);
             return pontoDentroPoligono(poli, x, y);
        }
        case VERTICE: {
            double x = getXVertice(forma);
            double y = getYVertice(forma);
            return pontoDentroPoligono(poli, x, y);
        }
        case PONTO: {
            double x = getXPonto(forma);
            double y = getYPonto(forma);
            return pontoDentroPoligono(poli, x, y);
        }
    }
    return false;
}