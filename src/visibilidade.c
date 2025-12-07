//
// Created by natha on 26/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "forma.h"
#include "lista.h"
#include "arvore.h"
#include "segmento.h"
#include "poligono.h"
#include "vertices.h"
#include "sort.h"
#include "visibilidade.h"

static double BOMBA_X;
static double BOMBA_Y;

void adicionaXY(Poligono p, double x, double y) {
    Ponto pt = CriarPonto(x,y);
    adicionarPontoAoPoligono(p, pt);
}

Segmento obterSegmentoMaisProximo(Arvore ativos) {
    if (arvorevazia(ativos)) return NULL;

    return (Segmento) pontMaisEsquerda(ativos);
}

void calcularInterseccaoRaio(Segmento s, double theta, double* xSaida, double* ySaida) {
    double dx = cos(theta);
    double dy = sin(theta);

    double x1 = getX1Segmento(s);
    double y1 = getY1Segmento(s);
    double x2 = getX2Segmento(s);
    double y2 = getY2Segmento(s);

    double det = (x2 - x1)*dy - (y2 - y1)*dx;
    if (det == 0) return;

    double u = ((BOMBA_X - x1)*dy - (BOMBA_Y - y1)*dx) / det;

    *xSaida = x1 + u * (x2 - x1);
    *ySaida = y1 + u * (y2 - y1);
}

int comparaVerticesSort(Vertice v1, Vertice v2) {
    //Vertice v1 = *(Vertice*) a;
    //Vertice v2 = *(Vertice*) b;

    double ang1 = getAnguloVertice(v1);
    double ang2 = getAnguloVertice(v2);

    if (ang1 < ang2) return -1;
    if (ang1 > ang2) return 1;
    return 0;

}

int comparaSegmentosArvore(Segmento a, Segmento b) {
    if (a == b) return 0;

    double o = orientacaoPontoSegmento(b, getX1Segmento(a), getY1Segmento(a));

    if (o < 0) return -1;
    if (o > 0) return 1;
    return 0;

}

Segmento inicializarSweepLine(Lista anteparos, Arvore ativos,double *pontoInterseccao) {

    Segmento biombo = NULL;
    double distBiombo = INFINITY;

    pont atual = getPrimeiroElementoLista(anteparos);

    while (atual != NULL) {
        Pacote p = getPacoteElementoLista(atual);
        Segmento seg = getDadosForma(p);

        double sy1 = getY1Segmento(seg) - BOMBA_Y;
        double sy2 = getY2Segmento(seg) - BOMBA_Y;

        if ((sy1 > 0 && sy2 < 0) || (sy1 < 0 && sy2 > 0)) {
            double tx, ty;
            calcularInterseccaoRaio(seg,0.0,&tx, &ty);

            if (tx > BOMBA_X) {
                inserirArvore(ativos, seg);

                double dist = tx - BOMBA_X;
                if (dist < distBiombo) {
                    distBiombo = dist;
                    biombo = seg;
                    *pontoInterseccao = tx;
                }
            }
        }

        atual = getProximoElementoLista(atual);
    }

    return biombo;
}

Poligono calcularRegiaoVisibilidade(Lista anteparos, double bx, double by, char tipoOrd, int limIns) {

    BOMBA_X = bx;
    BOMBA_Y = by;

    int qtdVertices;

    Vertice* vetorVertices = (Vertice*) CriarVetorVertices(anteparos, bx, by, &qtdVertices);

    ordenarVetor(vetorVertices, qtdVertices, sizeof(Vertice), comparaVerticesSort, tipoOrd, limIns);

    Arvore ativos = CriarArvore(comparaSegmentosArvore);
    Poligono poli = CriarPoligono();

    double xBiombo;
    Segmento segmentoAtual = inicializarSweepLine(anteparos, ativos, &xBiombo);

    if (segmentoAtual != NULL) {
        adicionaXY(poli, xBiombo, by);
    }

    for (int i = 0; i < qtdVertices; i++) {
        Vertice v = vetorVertices[i];
        Segmento segV = getSegmentoVertice(v);
        TipoVertice tipo = getTipoVertice(v);
        double angulo = getAnguloVertice(v);
        double vx = getXVertice(v);
        double vy = getYVertice(v);

        if (tipo == INICIO) {
            inserirArvore(ativos, segV);
        } else {
            removerArvore(ativos, segV);
        }

        Segmento novoMaisProximo = obterSegmentoMaisProximo(ativos);

        if (segmentoAtual != novoMaisProximo) {

            if (segmentoAtual != NULL) {
                double xCorte, yCorte;
                calcularInterseccaoRaio(segmentoAtual,angulo, &xCorte, &yCorte);
                adicionaXY(poli, xCorte, yCorte);
            }

            if (novoMaisProximo != NULL) {
                if (segmentoAtual != NULL) {
                    if (tipo == INICIO) {
                        adicionaXY(poli,vx,vy);
                    }else {
                        double xCorte, yCorte;
                        calcularInterseccaoRaio(novoMaisProximo,angulo,&xCorte,&yCorte);
                        adicionaXY(poli,xCorte,yCorte);
                    }
                }else {
                    adicionaXY(poli,vx,vy);
                }
            } else {
                adicionaXY(poli,vx,vy);
            }
            segmentoAtual = novoMaisProximo;
        }
        else {
            if (segmentoAtual == segV) {
                adicionaXY(poli,vx,vy);
            }
        }
    }
    liberarArvore(ativos);
    for (int i = 0; i < qtdVertices; i++) {
        eliminarVertice(vetorVertices[i]);
    }
    free(vetorVertices);

    return poli;
}