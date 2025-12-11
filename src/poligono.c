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
    if (p == NULL) {
        printf("Erro ao alocar memória ao CriarPonto!\n");

        perror("Motivo do erro");
        exit(1);
    }
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
    poligono* poli = malloc(sizeof(poligono));
    if (poli == NULL) {
        printf("Erro ao alocar memória ao CriarPoligono!\n");

        perror("Motivo do erro");
        exit(1);
    }
    poli->pontos = iniciarLista();
    return poli;
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
    if (vet == NULL) {
        printf("Erro ao alocar memória ao pontoDentroPoligono!\n");

        perror("Motivo do erro");
        exit(1);
    }
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
            double x = getXCirculo(form);
            double y = getYCirculo(form);
            double r = getRCirculo(form);

            if (pontoDentroPoligono(poli, x, y)) return true;
            if (pontoDentroPoligono(poli, x - r,y))return true;
            if (pontoDentroPoligono(poli, x, y + r)) return true;
            if (pontoDentroPoligono(poli, x + r, y)) return true;
            if (pontoDentroPoligono(poli, x, y - r)) return true;

            return false;
        }
        case LINHA: {
            double x1 = getX1Linha(form);
            double y1 = getY1Linha(form);
            double x2 = getX2Linha(form);
            double y2 = getY2Linha(form);
            return pontoDentroPoligono(poli, x1, y1) || pontoDentroPoligono(poli, x2, y2);
        }
        case SEGMENTO: {
            double x1 = getX1Segmento(form);
            double y1 = getY1Segmento(form);
            double x2 = getX2Segmento(form);
            double y2 = getY2Segmento(form);

            if (pontoDentroPoligono(poli, x1, y1)) return true;
            if (pontoDentroPoligono(poli, x2, y2)) return true;

            double xm = (x1 + x2) / 2.0;
            double ym = (y1 + y2) / 2.0;
            if (pontoDentroPoligono(poli,xm,ym)) return true;

            return false;
        }
        case TEXTO: {
            double x = getXTexto(form);
            double y = getYTexto(form);
            char ancora = getATexto(form);

            double largura = 10.0 * quantidadeCaracteresTexto(form);
            double altura = 10.0;

            double xMin, xMax;

            switch (ancora) {
                case 'i':
                    xMin = x;
                    xMax = x + largura;
                    break;
                case 'm':
                    xMin = x - (largura / 2.0);
                    xMax = x + (largura / 2.0);
                    break;
                case 'f':
                    xMin = x - largura;
                    xMax = x;
                    break;
                default:
                    xMin = x;
                    xMax = x + largura;
            }

            double yBase = y;
            double yTopo = y - altura;

            if (pontoDentroPoligono(poli, xMin, yBase)) return true;
            if (pontoDentroPoligono(poli, xMax, yBase)) return true;
            if (pontoDentroPoligono(poli, xMin, yTopo)) return true;
            if (pontoDentroPoligono(poli, xMax, yTopo)) return true;

            double xCentro = (xMin + xMax) / 2.0;
            double yCentro = (yBase + yTopo) / 2.0;
            if (pontoDentroPoligono(poli,xCentro, yCentro)) return true;

            return false;
        }
        case VERTICE: {
            double x = getXVertice(form);
            double y = getYVertice(form);
            return pontoDentroPoligono(poli, x, y);
        }
        case PONTO: {
            double x = getXPonto(form);
            double y = getYPonto(form);
            return pontoDentroPoligono(poli, x, y);
        }
    }
    return false;
}