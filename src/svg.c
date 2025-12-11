//
// Created by natha on 04/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "segmento.h"
#include "forma.h"

#include "poligono.h"
#include "lista.h"
#include "txt.h"
#include "svg.h"

Arquivo abrirSVG(Nome arquivo) {
    Arquivo svg = fopen(arquivo,"w");
    if (svg == NULL) {
        printf("Erro ao abrir o arquivo svg!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return svg;
}

void inicializarSVG(Arquivo svg) {
    if (svg == NULL) return;
    fprintf(svg,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg,"<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" width=\"1000\" height=\"1000\">\n");
    fprintf(svg,"\t<g>\n");
}

void desenharCirculoSVG(Arquivo svg, Circulo c) {
    if (svg == NULL || c == NULL) return;
    fprintf(svg, "<circle id=\"%d\" "
                 "cx=\"%lf\" "
                 "cy=\"%lf\" "
                 "r=\"%lf\" "
                 "stroke=\"%s\" "
                 "fill=\"%s\" "
                 "opacity=\"%lf\" "
                 "stroke-width=\"%lf\" "
                 "/>\n",
                 getIDCirculo(c),
                 getXCirculo(c),
                 getYCirculo(c),
                 getRCirculo(c),
                 getCorBCirculo(c),
                 getCorPCirculo(c),
                 0.5,
                 1.5);
}

void desenharRetanguloSVG(Arquivo svg, Retangulo r) {
    if (svg == NULL || r == NULL) return;
    fprintf(svg, "\t<rect id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "width=\"%lf\" "
                 "height=\"%lf\" "
                 "stroke=\"%s\" "
                 "fill=\"%s\" "
                 "opacity=\"%lf\" "
                 "stroke-width=\"%lf\" "
                 "/>\n",
                 getIDRetangulo(r),
                 getXRetangulo(r),
                 getYRetangulo(r),
                 getWRetangulo(r),
                 getHRetangulo(r),
                 getCorBRetangulo(r),
                 getCorPRetangulo(r),
                 0.5,
                 1.5);

}

void desenharLinhaSVG(Arquivo svg, Linha l) {
    if (svg == NULL || l == NULL) return;
    fprintf(svg, "\t<line id=\"%d\" "
                 "x1=\"%lf\" "
                 "y1=\"%lf\" "
                 "x2=\"%lf\" "
                 "y2=\"%lf\" "
                 "stroke=\"%s\" "
                 "stroke-width=\"%lf\" "
                 "/>\n",
                 getIDLinha(l),
                 getX1Linha(l),
                 getY1Linha(l),
                 getX2Linha(l),
                 getY2Linha(l),
                 getCorLinha(l),
                 1.5);

}

void desenharTextoSVG(Arquivo svg, Texto t, Estilo e) {
    if (svg == NULL || t == NULL || e == NULL) return;
    fprintf(svg, "\t<text id=\"%d\" "
                 "x=\"%lf\" "
                 "y=\"%lf\" "
                 "stroke=\"%s\" "
                 "fill=\"%s\" "
                 "font-family=\"%s\" "
                 "font-weight=\"%s\" "
                 "font-size=\"%spt\" ",
                 getIDTexto(t),
                 getXTexto(t),
                 getYTexto(t),
                 getCorBTexto(t),
                 getCorPTexto(t),
                 getFontFamilyTexto(e),
                 getFontWeightTexto(e),
                 getFontSizeTexto(e));

    switch (getATexto(t)) {
        case 'i':
            fprintf(svg, "text-anchor=\"start\" ");
            break;
        case 'm':
            fprintf(svg, "text-anchor=\"middle\" ");
            break;
        case 'f':
            fprintf(svg, "text-anchor=\"end\" ");
            break;
        default:
            printf("Indice de ancora '%c' incorreto!\n",getATexto(t));
            break;
    }
    fprintf(svg, ">%s</text>\n", getTxtoTexto(t));

}

void desenharSegmentoSVG(Arquivo svg, Segmento s) {
    if (svg == NULL || s == NULL) return;
    TipoSegmento tipo = getTipoSegmento(s);
    if (tipo == AREA) {
        fprintf(svg, "\t<line id=\"%d\" "
                 "x1=\"%lf\" "
                 "y1=\"%lf\" "
                 "x2=\"%lf\" "
                 "y2=\"%lf\" "
                 "stroke=\"%s\" "
                 "stroke-dasharray=\"5,5\" "
                 "stroke-width=\"%lf\" "
                 "/>\n",
                 getIDSegmento(s),
                 getX1Segmento(s),
                 getY1Segmento(s),
                 getX2Segmento(s),
                 getY2Segmento(s),
                 getCorSegmento(s),
                 1.2);
    }else {
        fprintf(svg, "\t<line id=\"%d\" "
                 "x1=\"%lf\" "
                 "y1=\"%lf\" "
                 "x2=\"%lf\" "
                 "y2=\"%lf\" "
                 "stroke=\"%s\" "
                 "stroke-width=\"%lf\" "
                 "/>\n",
                 getIDSegmento(s),
                 getX1Segmento(s),
                 getY1Segmento(s),
                 getX2Segmento(s),
                 getY2Segmento(s),
                 getCorSegmento(s),
                 1.5);
    }
}

void desenharBombaSVG(Arquivo svg, double x, double y) {
    if (svg == NULL) return;
    fprintf(svg, "\t<text x=\"%lf\" "
                 "y=\"%lf\" "
                 "fill=\"red\" "
                 "font-size=\"%d\" "
                 ">*</text>\n",
                 x,
                 y,
                 10);
}

void desenharPoligonoSVG(Arquivo svg, Poligono p) {
    if (svg == NULL || p == NULL) return;

    fprintf(svg, "\t<polygon points=\"");
    Lista pontos = getListaPontosPoligono(p);

    pont atual = getPrimeiroElementoLista(pontos);
    while (atual != NULL) {
        Pacote pac = getPacoteElementoLista(atual);
        Ponto pt = getDadosForma(pac);
        fprintf(svg, "%lf,%lf ", getXPonto(pt), getYPonto(pt));
        atual = getProximoElementoLista(atual);
    }

    fprintf(svg, "\" fill=\"yellow\" opacity=\"0.5\" stroke=\"black\" />\n");
}

void desenharFormasDaLista(Arquivo svg, Lista formas, Estilo EstiloGlobalTexto) {

    if (svg == NULL || formas == NULL) {
        printf("Erro ao CriarFormas/Anteparos no svg!\n");

        perror("Motivo do erro");
        return;
    }

    if (listavazia(formas)) {
        printf("Erro de listavazia ao CriarFormas/Anteparos no svg!\n");

        perror("Motivo do erro");
        return;
    }

    pont atual = getPrimeiroElementoLista(formas);

    while (atual != NULL) {
        Pacote p = getPacoteElementoLista(atual);

        TipoForma tipo = getTipoForma(p);
        Forma forma = getDadosForma(p);

        switch (tipo) {
            case CIRCULO:
                desenharCirculoSVG(svg, forma);
                break;
            case RETANGULO:
                desenharRetanguloSVG(svg, forma);
                break;
            case LINHA:
                desenharLinhaSVG(svg, forma);
                break;
            case TEXTO:
                desenharTextoSVG(svg, forma, EstiloGlobalTexto);
                break;
            case SEGMENTO:
                desenharSegmentoSVG(svg, forma);
                break;
            default:
                printf("ERRO: tipo inválido!\n");
                break;
        }

        atual = getProximoElementoLista(atual);
    }
}

void fecharSVG(Arquivo svg) {
    if (svg == NULL) return;
    fprintf(svg, "</g>\n");
    fprintf(svg,"</svg>\n");

    printf("Arquivo SVG gerado com sucesso!\n");

}

void gerarSVG(Lista formas, Arquivo arqSvg,Estilo EstiloGlobalTexto) {
    desenharFormasDaLista(arqSvg, formas,EstiloGlobalTexto);
}