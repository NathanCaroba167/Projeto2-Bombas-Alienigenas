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

double produtoVetorial(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x2 -x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

bool naSegmento(double px, double py, double qx, double qy, double rx, double ry) {
    return qx <= fmax(px, rx) && qx >= fmin(px, rx) &&
           qy <= fmax(py, ry) && qy >= fmin(py, ry);
}

bool segmentosSeInterceptam(double p1x, double p1y, double p2x, double p2y,double p3x, double p3y, double p4x, double p4y) {

    double o1 = produtoVetorial(p1x, p1y, p2x, p2y, p3x, p3y);
    double o2 = produtoVetorial(p1x, p1y, p2x, p2y, p4x, p4y);
    double o3 = produtoVetorial(p3x, p3y, p4x, p4y, p1x, p1y);
    double o4 = produtoVetorial(p3x, p3y, p4x, p4y, p2x, p2y);

    if (((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
        ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0))) {
        return true;
        }

    if (o1 == 0 && naSegmento(p1x, p1y, p3x, p3y, p2x, p2y)) return true;
    if (o2 == 0 && naSegmento(p1x, p1y, p4x, p4y, p2x, p2y)) return true;
    if (o3 == 0 && naSegmento(p3x, p3y, p1x, p1y, p4x, p4y)) return true;
    if (o4 == 0 && naSegmento(p3x, p3y, p2x, p2y, p4x, p4y)) return true;

    return false;
}

bool linhaCruzaArestasDoPoligono(Poligono p, double x1, double y1, double x2, double y2) {
    poligono* poli = (poligono*)p;

    if (getTamanhoLista(poli->pontos) < 2) return false;

    pont atual = getPrimeiroElementoLista(poli->pontos);

    Pacote packPrimeiro = getPacoteElementoLista(atual);
    Ponto ptPrimeiro = getDadosForma(packPrimeiro);
    double xPrim = getXPonto(ptPrimeiro);
    double yPrim = getYPonto(ptPrimeiro);

    double xA = xPrim;
    double yA = yPrim;

    while (atual != NULL) {
        pont proxNode = getProximoElementoLista(atual);
        double xB, yB;

        if (proxNode != NULL) {
            Pacote pack = getPacoteElementoLista(proxNode);
            Ponto pt = getDadosForma(pack);
            xB = getXPonto(pt);
            yB = getYPonto(pt);
        } else {
            xB = xPrim;
            yB = yPrim;
        }

        if (segmentosSeInterceptam(x1, y1, x2, y2, xA, yA, xB, yB)) {
            return true;
        }

        xA = xB;
        yA = yB;
        atual = proxNode;
    }
    return false;
}

bool pontoEhVerticeDoPoligono(Poligono p, double x, double y) {
    poligono* poli = (poligono*)p;
    pont atual = getPrimeiroElementoLista(poli->pontos);

    double epsilon = 1e-4;

    while (atual != NULL) {
        Pacote pack = getPacoteElementoLista(atual);
        Ponto pt = getDadosForma(pack);

        if (hypot(getXPonto(pt) - x, getYPonto(pt) - y) < epsilon) {
            return true;
        }
        atual = getProximoElementoLista(atual);
    }
    return false;
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

            if (linhaCruzaArestasDoPoligono(poli, x, y, x + w, y)) return true;
            if (linhaCruzaArestasDoPoligono(poli, x, y + h, x + w, y + h)) return true;
            if (linhaCruzaArestasDoPoligono(poli, x, y, x, y + h)) return true;
            if (linhaCruzaArestasDoPoligono(poli, x + w, y, x + w, y + h)) return true;

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

            if (pontoDentroPoligono(poli, x1, y1)) return true;
            if (pontoDentroPoligono(poli, x2, y2)) return true;

            double xm = (x1 + x2) / 2.0;
            double ym = (y1 + y2) / 2.0;
            if (pontoDentroPoligono(poli, xm, ym)) return true;

            if (linhaCruzaArestasDoPoligono(poli, x1, y1, x2, y2)) return true;

            return false;

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

            if (pontoEhVerticeDoPoligono(poli, x1, y1)) return true;
            if (pontoEhVerticeDoPoligono(poli, x2, y2)) return true;

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