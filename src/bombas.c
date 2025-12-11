//
// Created by natha on 01/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "forma.h"
#include "lista.h"

#include "segmento.h"
#include "poligono.h"
#include "vertices.h"
#include "svg.h"
#include "txt.h"
#include "segmentador.h"
#include "arvore.h"
#include "sort.h"
#include "visibilidade.h"
#include "bombas.h"

#define DELTA_BORDA 300.0

void Anteparo(Arquivo txt,Lista formas,Lista anteparos,int inicial,int final,char direcao) {

    if (formas == NULL) {
        printf( "ERRO no comando A: Lista de formas vazia sem formas para transformacao.\n");
        return;
    }

    for (int i = inicial; i <= final; i++) {
        printf("DEBUG: Buscando ID %d...\n", i); fflush(stdout);
        Pacote p = getPorIdLista(formas,i);
        if (p == NULL) {
            printf("DEBUG: ID %d nao achado. Pulo.\n", i); fflush(stdout);
            continue;
        }
        printf("DEBUG: Convertendo ID %d...\n", i); fflush(stdout);
        Forma f = getDadosForma(p);
        TipoForma tipo = getTipoForma(p);

        fprintf(txt,"\nForma original → ");
        reportarForma(txt,p);

        switch (tipo) {
            case CIRCULO:
                converteCirculoSegmento(txt,f,anteparos,direcao);
                break;
            case RETANGULO:
                printf("DEBUG: Entrando em converteRetangulo...\n"); fflush(stdout);
                converteRetanguloSegmento(txt,f,anteparos);
                printf("DEBUG: Saiu de converteRetangulo.\n"); fflush(stdout);
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
        printf("DEBUG: Removendo ID %d...\n", i); fflush(stdout);
        removerElementoLista(formas,p);
        liberarForma(p);
        printf("DEBUG: Removido ID %d com sucesso.\n", i); fflush(stdout);
    }

    printf("DEBUG: Iniciando Calculo da Borda (Universo)...\n"); fflush(stdout);

    double xMaximo = -1e30;
    double xMinimo = 1e30;
    double yMaximo = -1e30;
    double yMinimo = 1e30;
    int temElementos = 0;

    pont atual = getPrimeiroElementoLista(anteparos);

    int contador_debug = 0;
    while (atual != NULL) {
        printf("DEBUG: Processando anteparo %d...\n", contador_debug++); fflush(stdout);
        Pacote pacote = getPacoteElementoLista(atual);
        Segmento s = getDadosForma(pacote);

        if (getTipoSegmento(s) == ANTEPARO) {
            double x1 = getX1Segmento(s);
            double x2 = getX2Segmento(s);
            double y1 = getY1Segmento(s);
            double y2 = getY2Segmento(s);

            if (x1 > xMaximo) xMaximo = x1;
            if (x1 < xMinimo) xMinimo = x1;

            if (x2 > xMaximo) xMaximo = x2;
            if (x2 < xMinimo) xMinimo = x2;

            if (y1 > yMaximo) yMaximo = y1;
            if (y1 < yMinimo) yMinimo = y1;

            if (y2 > yMaximo) yMaximo = y2;
            if (y2 < yMinimo) yMinimo = y2;

            temElementos = 1;
        }
        atual = getProximoElementoLista(atual);
    }

    atual = getPrimeiroElementoLista(formas);

    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);
        TipoForma tipo = getTipoForma(pacote);
        Forma f = getDadosForma(pacote);

        double minX_f, maxX_f, minY_f, maxY_f;

        switch (tipo) {
            case CIRCULO: {
                double r = getRCirculo(f);
                minX_f = getXCirculo(f) - r; maxX_f = getXCirculo(f) + r;
                minY_f = getYCirculo(f) - r; maxY_f = getYCirculo(f) + r;
                break;
            }
            case RETANGULO: {
                double w = getWRetangulo(f); double h = getHRetangulo(f);
                minX_f = getXRetangulo(f); maxX_f = getXRetangulo(f) + w;
                minY_f = getYRetangulo(f); maxY_f = getYRetangulo(f) + h;
                break;
            }
            case LINHA: {
                minX_f = fmin(getX1Linha(f), getX2Linha(f));
                maxX_f = fmax(getX1Linha(f), getX2Linha(f));
                minY_f = fmin(getY1Linha(f), getY2Linha(f));
                maxY_f = fmax(getY1Linha(f), getY2Linha(f));
                break;
            }
            case TEXTO: {
                double x = getXTexto(f); double y = getYTexto(f);
                double largura = 10.0 * quantidadeCaracteresTexto(f);
                minX_f = x; maxX_f = x + largura;
                minY_f = y; maxY_f = y + 10.0;
                break;
            }
            default:
                atual = getProximoElementoLista(atual);
                continue;
        }


        if (maxX_f > xMaximo) xMaximo = maxX_f;
        if (minX_f < xMinimo) xMinimo = minX_f;
        if (maxY_f > yMaximo) yMaximo = maxY_f;
        if (minY_f < yMinimo) yMinimo = minY_f;

        temElementos = 1;
        atual = getProximoElementoLista(atual);
    }

    printf("DEBUG: Calculo Borda finalizado. Criando 4 segmentos...\n"); fflush(stdout);

    if (temElementos) {
        int idMax = getMaiorId();

        Pacote p = CriarPacote(CriarSegmento(idMax, xMinimo - DELTA_BORDA, yMinimo - DELTA_BORDA, xMaximo + DELTA_BORDA, yMinimo - DELTA_BORDA, "black",AREA),SEGMENTO);
        inserirListaInicio(anteparos, p);

        Pacote p1 = CriarPacote(CriarSegmento(idMax + 1, xMaximo + DELTA_BORDA, yMinimo - DELTA_BORDA, xMaximo + DELTA_BORDA, yMaximo + DELTA_BORDA, "black",AREA),SEGMENTO);
        inserirListaInicio(anteparos, p1);

        Pacote p2 = CriarPacote(CriarSegmento(idMax + 2, xMaximo + DELTA_BORDA, yMaximo + DELTA_BORDA, xMinimo - DELTA_BORDA, yMaximo + DELTA_BORDA, "black",AREA),SEGMENTO);
        inserirListaInicio(anteparos, p2);

        Pacote p3 = CriarPacote(CriarSegmento(idMax + 3, xMinimo - DELTA_BORDA, yMaximo + DELTA_BORDA, xMinimo - DELTA_BORDA, yMinimo - DELTA_BORDA, "black",AREA),SEGMENTO);
        inserirListaInicio(anteparos, p3);

        adicionaMaiorID(4);
    }
    printf("DEBUG: Bordas criadas. Fim do Anteparo.\n"); fflush(stdout);

}

void Destruicao(Arquivo svg,Arquivo txt,Lista formas,Lista anteparos, double xBomba, double yBomba, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd,int limIns) {
    Poligono poli = calcularRegiaoVisibilidade(anteparos,xBomba,yBomba, tipoOrd,limIns);

    printf("DEBUG BOMBA: Iniciando desenho no SVG (Modo: %s)...\n", sfx_modo); fflush(stdout);
    if (strcmp(sfx_modo, "-") == 0) {
        printf("DEBUG SVG: Chamando desenharPoligonoSVG no principal...\n"); fflush(stdout);
        desenharPoligonoSVG(svg,poli);
        desenharBombaSVG(svg,xBomba,yBomba);
        printf("DEBUG SVG: Retornou de desenharPoligonoSVG.\n"); fflush(stdout);
    } else {
        char nomeArquivoSfx[512];
        sprintf(nomeArquivoSfx,"%s-%s.svg",caminhoBaseSaida, sfx_modo);

        Arquivo svgSFX = abrirSVG(nomeArquivoSfx);
        inicializarSVG(svgSFX);

        desenharPoligonoSVG(svgSFX,poli);
        desenharBombaSVG(svgSFX,xBomba,yBomba);
        //desenharFormasDaLista(svgSFX, formas, NULL);
        desenharFormasDaLista(svgSFX, anteparos, NULL);
        fecharSVG(svgSFX);
        fclose(svgSFX);
    }
    printf("DEBUG BOMBA: Desenho SVG concluido.\n"); fflush(stdout);

    pont atual = getPrimeiroElementoLista(formas);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        pont proximo = getProximoElementoLista(atual);
        if (verificarSobreposicao(poli,pacote)) {
            fprintf(txt,"\nForma destruida → ");
            reportarForma(txt,pacote);

            removerElementoLista(formas,pacote);
            liberarForma(pacote);
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
                fprintf(txt,"\nAnteparo destruido → ");
                reportarForma(txt,pacote);
                fprintf(txt,"\n");
                removerElementoLista(anteparos,pacote);
                liberarForma(pacote);
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
            setCorPForma(pacote,cor);
            fprintf(txt,"\nForma pintada → ");
            reportarForma(txt,pacote);
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
                setCorPForma(pacote,cor);
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

    Lista clonesDeFormas = iniciarLista();
    Lista clonesDeAnteparos = iniciarLista();

    pont atual = getPrimeiroElementoLista(formas);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        if (verificarSobreposicao(poli,pacote)) {

            Pacote clone = clonarForma(pacote, dx, dy);
            inserirListaFim(clonesDeFormas,clone);
            fprintf(txt,"\nForma clonada → ");
            reportarForma(txt,pacote);
        }

        atual = getProximoElementoLista(atual);
    }

    atual = getPrimeiroElementoLista(anteparos);
    while (atual != NULL) {
        Pacote pacote = getPacoteElementoLista(atual);

        if (verificarSobreposicao(poli,pacote)) {
            Segmento seg = getDadosForma(pacote);

            if (getTipoSegmento(seg) != AREA) {
                Pacote clone = clonarForma(pacote, dx, dy);
                inserirListaFim(clonesDeAnteparos,clone);
                fprintf(txt, "\nAnteparo clonado → ");
                reportarForma(txt, pacote);
            }
        }
        atual = getProximoElementoLista(atual);
    }
    concatenaListas(formas, clonesDeFormas);
    concatenaListas(anteparos, clonesDeAnteparos);
    free(clonesDeFormas);
    free(clonesDeAnteparos);
    eliminarPoligono(poli);
}
