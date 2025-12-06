//
// Created by natha on 01/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"
#include "lista.h"
#include "svg.h"
#include "txt.h"
#include "segmentador.h"
#include "vertices.h"
#include "arvore.h"
#include "sort.h"
#include "poligono.h"
#include "bombas.h"

#include "segmento.h"
#include "visibilidade.h"

#define DELTA_BORDA 5.0

void Anteparo(Arquivo txt,Lista formas,Lista anteparos,int inicial,int final,char direcao) {//

    if (formas == NULL) {
        printf( "ERRO no comando A: Lista de formas vazia sem formas para transformacao.\n");
        return;
    }

    for (int i = inicial; i <= final; i++) {
        Pacote p = getPorIdLista(formas,i);
        Forma f = getDadosForma(p);
        TipoForma tipo = getTipoForma(p);

        switch (tipo) {
            case CIRCULO:
                converteCirculoSegmento(txt,f,anteparos,direcao);
                //fprintf
                break;
            case RETANGULO:
                converteRetanguloSegmento(txt,f,anteparos);
                break;
            case LINHA:
                converteLinhaSegmento(txt,f,anteparos);
                break;
            case TEXTO:
                converteTextoSegmento(txt,f,anteparos);
                break;
            default:
                printf("Tipo inválido!\n");
                break;
        }
        removerPorIdLista(formas,i);
    }

    pont atual = getPrimeiroElementoLista(anteparos);
    Pacote p = getPacoteElementoLista(atual);
    Segmento seg = getDadosForma(p);
    double xMaximo = fmax(getX1Segmento(seg),getX2Segmento(seg));
    double xMinimo = fmin(getX1Segmento(seg),getX2Segmento(seg));
    double yMaximo = fmax(getY1Segmento(seg),getY2Segmento(seg));
    double yMinimo = fmin(getY1Segmento(seg),getY2Segmento(seg));
    atual = getProximoElementoLista(atual);

    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);
        Segmento s = getDadosForma(pacote);
        atual = getProximoElementoLista(atual);
        if (xMaximo < fmax(getX1Segmento(s),getX2Segmento(s))) {
            xMaximo = fmax(getX1Segmento(s),getX2Segmento(s));
        }
        if (xMinimo > fmin(getX1Segmento(s),getX2Segmento(s))) {
            xMinimo = fmin(getX1Segmento(s),getX2Segmento(s));
        }
        if (yMaximo < fmax(getY1Segmento(s),getY2Segmento(s))) {
            yMaximo = fmax(getY1Segmento(s),getY2Segmento(s));
        }
        if (yMinimo > fmin(getY1Segmento(s),getY2Segmento(s))) {
            yMinimo = fmin(getY1Segmento(s),getY2Segmento(s));
        }
    }
    ///Qual id??Qual Cor??
    inserirListaInicio(anteparos, CriarSegmento(1000, xMinimo + DELTA_BORDA, yMinimo + DELTA_BORDA, xMaximo + DELTA_BORDA, yMinimo + DELTA_BORDA, "black",AREA));
    inserirListaInicio(anteparos, CriarSegmento(1001, xMaximo + DELTA_BORDA, yMinimo + DELTA_BORDA, xMaximo + DELTA_BORDA, yMaximo + DELTA_BORDA, "black",AREA));
    inserirListaInicio(anteparos, CriarSegmento(1002, xMaximo + DELTA_BORDA, yMaximo + DELTA_BORDA, xMinimo + DELTA_BORDA, yMaximo + DELTA_BORDA, "black",AREA));
    inserirListaInicio(anteparos, CriarSegmento(1003, xMinimo + DELTA_BORDA, yMaximo + DELTA_BORDA, xMinimo + DELTA_BORDA, yMinimo + DELTA_BORDA, "black",AREA));

    fprintf(txt,"\nForma criada → ");
    reportarForma(txt,p);
}

void Destruicao(Arquivo svg,Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns) {
    Poligono poli = calcularRegiaoVisibilidade(anteparos,xBomba,yBomba, tipoOrd,limIns);

    if (strcmp(sfx_modo, "-") == 0) {
        desenharPoligonoSVG(svg,poli);
    } else {
        char nomeArquivoSfx[512];
        sprintf(nomeArquivoSfx,"%s-%s.svg",caminhoBaseSaida, sfx_modo);
        Arquivo svgSFX = abrirSVG(nomeArquivoSfx);
        inicializarSVG(svgSFX);
        desenharFormasDaLista(svgSFX, anteparos, NULL);
        desenharPoligonoSVG(svgSFX,poli);
        fecharSVG(svgSFX);
        fclose(svgSFX);
    }

    pont atual = getPrimeiroElementoLista(formas);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        pont proximo = getProximoElementoLista(atual);
        if (verificarSobreposicao(poli,pacote)) {
            ///fprintf

            removerElementoLista(formas,pacote);
        }

        atual = proximo;
    }

    atual = getPrimeiroElementoLista(anteparos);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        pont proximo = getProximoElementoLista(atual);
        if (verificarSobreposicao(poli,pacote)) {
            Segmento seg = getDadosForma(pacote);
            if (getTipoSegmento(seg) == AREA) {

            } else {
                removerElementoLista(anteparos,pacote);
            }
        }
        atual = proximo;
    }
    eliminarPoligono(poli);
}

void Pintura(Arquivo svg,Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba,char* cor, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns) {
    Poligono poli = calcularRegiaoVisibilidade(anteparos,xBomba,yBomba, tipoOrd,limIns);

    if (strcmp(sfx_modo, "-") == 0) {
        desenharPoligonoSVG(svg,poli);
    } else {
        char nomeArquivoSfx[512];
        sprintf(nomeArquivoSfx,"%s-%s.svg",caminhoBaseSaida, sfx_modo);
        Arquivo svgSFX = abrirSVG(nomeArquivoSfx);
        inicializarSVG(svgSFX);
        desenharFormasDaLista(svgSFX, anteparos, NULL);
        desenharPoligonoSVG(svgSFX,poli);
        fecharSVG(svgSFX);
        fclose(svgSFX);
    }

    pont atual = getPrimeiroElementoLista(formas);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        if (verificarSobreposicao(poli,pacote)) {

            setCorBForma(pacote,cor);
            ///fprintf
        }

        atual = getProximoElementoLista(atual);
    }

    atual = getPrimeiroElementoLista(anteparos);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        if (verificarSobreposicao(poli,pacote)) {
            Segmento seg = getDadosForma(pacote);
            if (getTipoSegmento(seg) == AREA) {

            } else {
                setCorBForma(pacote,cor);
            }
        }
        atual = getProximoElementoLista(atual);
    }
    eliminarPoligono(poli);
}

void Clone(Arquivo svg,Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba, double dx, double dy, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns) {
    Poligono poli = calcularRegiaoVisibilidade(anteparos,xBomba,yBomba, tipoOrd,limIns);

    if (strcmp(sfx_modo, "-") == 0) {
        desenharPoligonoSVG(svg,poli);
    } else {
        char nomeArquivoSfx[512];
        sprintf(nomeArquivoSfx,"%s-%s.svg",caminhoBaseSaida, sfx_modo);
        Arquivo svgSFX = abrirSVG(nomeArquivoSfx);
        inicializarSVG(svgSFX);
        desenharFormasDaLista(svgSFX, anteparos, NULL);
        desenharPoligonoSVG(svgSFX,poli);
        fecharSVG(svgSFX);
        fclose(svgSFX);
    }

    Lista novosClones = iniciarLista();

    pont atual = getPrimeiroElementoLista(formas);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        if (verificarSobreposicao(poli,pacote)) {

            Pacote clone = clonarForma(pacote, dx, dy);
            inserirListaFim(novosClones,clone);
            ///fprintf

        }

        atual = getProximoElementoLista(atual);
    }

    atual = getPrimeiroElementoLista(anteparos);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        if (verificarSobreposicao(poli,pacote)) {
            Segmento seg = getDadosForma(pacote);
            if (getTipoSegmento(seg) == AREA) {

            } else {
                Pacote clone = clonarForma(pacote, dx, dy);
                inserirListaFim(novosClones,clone);
            }
        }
        atual = getProximoElementoLista(atual);
    }
    concatenaListas(formas, novosClones); //anteparo??
    free(novosClones);
    eliminarPoligono(poli);
}
