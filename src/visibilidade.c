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

    return getMaisEsquerdaDado(ativos);
}

int calcularInterseccaoRaio(Segmento s, double theta, double* xSaida, double* ySaida) {
    double dx = cos(theta);
    double dy = sin(theta);

    double x1 = getX1Segmento(s);
    double y1 = getY1Segmento(s);
    double x2 = getX2Segmento(s);
    double y2 = getY2Segmento(s);

    double det = (x2 - x1)*dy - (y2 - y1)*dx;

    if (fabs(det) < 1e-6) return 0;

    double u = ((BOMBA_X - x1)*dy - (BOMBA_Y - y1)*dx) / det;

    if (u < -1e-6 || u > 1.0 + 1e-6) return 0;

    double px = x1 + u * (x2 - x1);
    double py = y1 + u * (y2 - y1);

    if ((px - BOMBA_X) * dx + (py - BOMBA_Y) * dy < 0) return 0;

    *xSaida = px;
    *ySaida = py;
    return 1;
}

int comparaVerticesSort(const void* a, const void* b) {
    Vertice v1 = *(Vertice*) a;
    Vertice v2 = *(Vertice*) b;

    double ang1 = getAnguloVertice(v1);
    double ang2 = getAnguloVertice(v2);

    if (fabs(ang1 - ang2) > 1e-9) {
        if (ang1 < ang2) {
            return -1;
        }
        return 1;
    }

    TipoVertice t1 = getTipoVertice(v1);
    TipoVertice t2 = getTipoVertice(v2);

    if (t1 == INICIO && t2 == FIM) return -1;
    if (t1 == FIM && t2 == INICIO) return 1;

    double d1 = getDistanciaVertice(v1);
    double d2 = getDistanciaVertice(v2);
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;

    return 0;
}

int comparaSegmentosArvore(Segmento a, Segmento b) {
    if (a == b) return 0;

    double x1a = getX1Segmento(a), y1a = getY1Segmento(a);
    double x2a = getX2Segmento(a), y2a = getY2Segmento(a);
    double x1b = getX1Segmento(b), y1b = getY1Segmento(b);
    double x2b = getX2Segmento(b), y2b = getY2Segmento(b);


    if (fabs(x1a - x1b) < 1e-5 && fabs(y1a - y1b) < 1e-5) {

        double val = orientacaoTresPontos(x1b, y1b, x2b, y2b, x2a, y2a);

        double val_bomba = orientacaoTresPontos(x1b, y1b, x2b, y2b, BOMBA_X, BOMBA_Y);

        if (val * val_bomba > 1e-9) return -1;
        if (val * val_bomba < -1e-9) return 1;

        if (hypot(x2a - x1a, y2a - y1a) < hypot(x2b - x1b, y2b - y1b)) return -1;
        return 1;
    }

    double val_a_em_b = orientacaoTresPontos(x1b, y1b, x2b, y2b, x1a, y1a);
    double val_bomba_em_b = orientacaoTresPontos(x1b, y1b, x2b, y2b, BOMBA_X, BOMBA_Y);

    if (val_a_em_b * val_bomba_em_b > 1e-9) return -1;
    if (val_a_em_b * val_bomba_em_b < -1e-9) return 1;

    if (getIDSegmento(a) < getIDSegmento(b)) return -1;
    return 1;
}

void tratarSegmentosQueCruzamInicio(Lista anteparos, double bx, double by) {
    Lista novosSegmentos = iniciarLista();
    Lista paraRemover = iniciarLista();

    pont atual = getPrimeiroElementoLista(anteparos);

    while (atual != NULL) {
        Pacote p = getPacoteElementoLista(atual);
        Segmento seg = getDadosForma(p);

        double y1 = getY1Segmento(seg) - by;
        double y2 = getY2Segmento(seg) - by;

        if ((y1 > 0 && y2 < 0) || (y1 < 0 && y2 > 0)) {
            double tx, ty;
            if (calcularInterseccaoRaio(seg, 0.0, &tx, &ty)) {
                if (tx > bx) {
                    ty = by;
                    char* cor = getCorSegmento(seg);
                    TipoSegmento tipoOriginal = getTipoSegmento(seg);
                    double sx1 = getX1Segmento(seg);
                    double sx2 = getX2Segmento(seg);
                    double sy1_abs = getY1Segmento(seg);
                    double sy2_abs = getY2Segmento(seg);

                    Segmento s1 = CriarSegmento(getMaiorId(), sx1, sy1_abs, tx, ty, cor, tipoOriginal);
                    adicionaMaiorID(1);

                    Segmento s2 = CriarSegmento(getMaiorId(), tx, ty, sx2, sy2_abs, cor, tipoOriginal);
                    adicionaMaiorID(1);

                    inserirListaInicio(novosSegmentos, CriarPacote(s1, SEGMENTO));
                    inserirListaInicio(novosSegmentos, CriarPacote(s2, SEGMENTO));
                    inserirListaInicio(paraRemover, p);
                }
            }
        }
        atual = getProximoElementoLista(atual);
    }

    if (!listavazia(paraRemover)) {
        atual = getPrimeiroElementoLista(paraRemover);
        while (atual != NULL) {
            Pacote pRemover = getPacoteElementoLista(atual);
            removerElementoLista(anteparos, pRemover);
            atual = getProximoElementoLista(atual);
        }
        concatenaListas(anteparos, novosSegmentos);
    }
    liberarLista(paraRemover);
    free(novosSegmentos);
}

Poligono calcularRegiaoVisibilidade(Lista anteparos, double bx, double by, char tipoOrd, int limIns) {
    printf("DEBUG VIS: --- Inicio do Calculo ---\n"); fflush(stdout);

    BOMBA_X = bx;
    BOMBA_Y = by;

    tratarSegmentosQueCruzamInicio(anteparos, bx, by);

    int qtdVertices;

    Vertice* vetorVertices = (Vertice*) CriarVetorVertices(anteparos, bx, by, &qtdVertices);

    ordenarVetor((void*)vetorVertices, qtdVertices, sizeof(Vertice), comparaVerticesSort, tipoOrd, limIns);

    Arvore ativos = CriarArvore(comparaSegmentosArvore);
    Poligono poli = CriarPoligono();

    Segmento segmentoAtual = NULL;

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
            Segmento removido = removerArvore(ativos, segV);

            if (removido == NULL) {
                printf("Erro Crítico: Falha ao remover segmento ID %d! \n", getIDSegmento(segV));
            }
        }

        Segmento novoMaisProximo = obterSegmentoMaisProximo(ativos);

        if (segmentoAtual != novoMaisProximo) {

            if (segmentoAtual != NULL) {
                double xCorte, yCorte;

                if (calcularInterseccaoRaio(segmentoAtual,angulo, &xCorte, &yCorte)) {
                    adicionaXY(poli,xCorte,yCorte);
                } else {
                    adicionaXY(poli, vx, vy);
                }
            }

            if (novoMaisProximo != NULL) {

                if (segmentoAtual != NULL) {

                    if (tipo == INICIO) {
                        adicionaXY(poli,vx,vy);
                    }else {
                        double xCorte, yCorte;
                        if (calcularInterseccaoRaio(novoMaisProximo,angulo,&xCorte,&yCorte)) {
                            adicionaXY(poli,xCorte,yCorte);
                        } else {
                            adicionaXY(poli, vx, vy);
                        }
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

    printf("DEBUG VIS: --- Fim do Calculo ---\n"); fflush(stdout);
    return poli;
}