//
// Created by natha on 19/11/2025.
//

#include <stdio.h>
#include <stdlib.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "lista.h"
#include "segmento.h"
#include "txt.h"
#include "segmentador.h"

#include <math.h>

static int MAIOR_ID = 0;

void converteCirculoSegmento(Arquivo txt,Circulo c,Lista anteparo,char direcao) {
    int novo_id = getMaiorId();

    int id = getIDCirculo(c);
    double x = getXCirculo(c);
    double y = getYCirculo(c);
    double r = getRCirculo(c);
    char* corB = getCorBCirculo(c);

    double xBase = x - r;
    double yBase = y - r;
    double tamanho = 2 * r;

    if (direcao == 'h') {
        inserirListaInicio(anteparo, CriarSegmento(novo_id, xBase, y, xBase + tamanho, y, corB,SEGMENTO));
        MAIOR_ID++;
    }else if (direcao == 'v') {
        inserirListaInicio(anteparo, CriarSegmento(novo_id, x, yBase, xBase, yBase + tamanho, corB,SEGMENTO));
        MAIOR_ID++;
    }
}

void converteRetanguloSegmento(Arquivo txt,Retangulo r,Lista anteparo) {
    int novo_id = getMaiorId();

    int id = getIDRetangulo(r);
    double x = getXRetangulo(r);
    double y = getYRetangulo(r);
    double w = getWRetangulo(r);
    double h = getHRetangulo(r);
    char* corB = getCorBRetangulo(r);

    inserirListaInicio(anteparo, CriarSegmento(novo_id, x, y, x + w, y, corB,SEGMENTO));

    inserirListaInicio(anteparo, CriarSegmento(novo_id + 1, x + w, y, x + w, y + h, corB,SEGMENTO));

    inserirListaInicio(anteparo, CriarSegmento(novo_id + 2, x + w, y + h, x, y + h, corB,SEGMENTO));

    inserirListaInicio(anteparo, CriarSegmento(novo_id + 3, x, y + h, x, y, corB,SEGMENTO));

    MAIOR_ID = MAIOR_ID + 4;
}

void converteLinhaSegmento(Arquivo txt,Linha l,Lista anteparo) {
    int novo_id = getMaiorId();

    int id = getIDLinha(l);
    double x1 = getX1Linha(l);
    double y1 = getY2Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);
    char* cor = getCorLinha(l);

    inserirListaInicio(anteparo, CriarSegmento(novo_id, x1, y1, x2, y2, cor,SEGMENTO));
    MAIOR_ID++;
}

void converteTextoSegmento(Arquivo txt,Texto t,Lista anteparo) {
    int novo_id = getMaiorId();
    char* corB = getCorBTexto(t);

    double x1,x2;
    switch (getATexto(t)) {
        case 'i':
            x1 = getXTexto(t);
            x2 = getXTexto(t) + 10.0 * quantidadeCaracteresTexto(t);
            break;
        case 'm':
            x1 = (getXTexto(t) - 10.0 * quantidadeCaracteresTexto(t))/2;
            x2 = (getXTexto(t) + 10.0 * quantidadeCaracteresTexto(t))/2;
            break;
        case 'f':
            x1 = getXTexto(t) - 10.0 * quantidadeCaracteresTexto(t);
            x2 = getXTexto(t);
            break;
        default:
            printf("Indice de ancora '%c' incorreto!\n",getATexto(t));
            exit(1);
    }
    inserirListaInicio(anteparo, CriarSegmento(novo_id, x1, getYTexto(t), x2, getYTexto(t), corB,SEGMENTO));
}
