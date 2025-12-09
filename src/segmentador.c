//
// Created by natha on 19/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "lista.h"
#include "segmento.h"
#include "txt.h"
#include "segmentador.h"

static int MAIOR_ID = 0;

void converteCirculoSegmento(Arquivo txt,Circulo c,Lista anteparo,char direcao) {
    int novo_id = getMaiorId();

    double x = getXCirculo(c);
    double y = getYCirculo(c);
    double r = getRCirculo(c);
    char* corB = getCorBCirculo(c);

    double xBase = x - r;
    double yBase = y - r;
    double tamanho = 2 * r;

    if (direcao == 'h') {
        Pacote p = CriarPacote(CriarSegmento(novo_id, xBase, y, xBase + tamanho, y, corB,ANTEPARO),SEGMENTO);
        fprintf(txt,"\nSegmento criado → ");
        reportarForma(txt,p);
        inserirListaInicio(anteparo,p);
        MAIOR_ID++;
    }else if (direcao == 'v') {
        Pacote p = CriarPacote(CriarSegmento(novo_id, x, yBase, x, yBase + tamanho, corB,ANTEPARO),SEGMENTO);
        fprintf(txt,"\nSegmento criado → ");
        reportarForma(txt,p);
        inserirListaInicio(anteparo, p);
        MAIOR_ID++;
    }
}

void converteRetanguloSegmento(Arquivo txt,Retangulo r,Lista anteparo) {
    int novo_id = getMaiorId();

    double x = getXRetangulo(r);
    double y = getYRetangulo(r);
    double w = getWRetangulo(r);
    double h = getHRetangulo(r);
    char* corB = getCorBRetangulo(r);

    if (corB == NULL) {
        corB = "black";
    }

    fprintf(txt,"\nSegmentos criados → ");

    Pacote p = CriarPacote(CriarSegmento(novo_id, x, y, x + w, y, corB,ANTEPARO),SEGMENTO);
    reportarForma(txt,p);
    fflush(txt);
    inserirListaInicio(anteparo, p);
    fprintf(txt,"\n");

    Pacote p1 = CriarPacote(CriarSegmento(novo_id + 1, x + w, y, x + w, y + h, corB,ANTEPARO),SEGMENTO);
    reportarForma(txt,p1);
    fflush(txt);
    inserirListaInicio(anteparo, p1);
    fprintf(txt,"\n");

    Pacote p2 = CriarPacote(CriarSegmento(novo_id + 2, x + w, y + h, x, y + h, corB,ANTEPARO),SEGMENTO);
    reportarForma(txt,p2);
    fflush(txt);
    inserirListaInicio(anteparo, p2);
    fprintf(txt,"\n");

    Pacote p3 = CriarPacote(CriarSegmento(novo_id + 3, x, y + h, x, y, corB,ANTEPARO),SEGMENTO);
    reportarForma(txt,p3);
    fflush(txt);
    inserirListaInicio(anteparo, p3);
    fprintf(txt,"\n");

    MAIOR_ID = MAIOR_ID + 4;
}

void converteLinhaSegmento(Arquivo txt,Linha l,Lista anteparo) {
    int novo_id = getMaiorId();

    double x1 = getX1Linha(l);
    double y1 = getY1Linha(l);
    double x2 = getX2Linha(l);
    double y2 = getY2Linha(l);
    char* cor = getCorLinha(l);

    Pacote p = CriarPacote(CriarSegmento(novo_id, x1, y1, x2, y2, cor,ANTEPARO),SEGMENTO);
    fprintf(txt,"\nSegmento criado → ");
    reportarForma(txt,p);
    inserirListaInicio(anteparo, p);
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

    Pacote p = CriarPacote(CriarSegmento(novo_id, x1, getYTexto(t), x2, getYTexto(t), corB,ANTEPARO),SEGMENTO);
    fprintf(txt,"\nSegmento criado → ");
    reportarForma(txt,p);
    inserirListaInicio(anteparo, p);
}
