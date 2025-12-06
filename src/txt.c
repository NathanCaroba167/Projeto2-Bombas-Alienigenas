//
// Created by natha on 16/10/2025.
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

#include "lista.h"

#include "geo.h"
#include "txt.h"

Arquivo abrirTXT(Nome arquivo) {
    // Abrindo o arquivo para escrita ('w')
    Arquivo txt = fopen(arquivo,"w");
    if (txt == NULL) {
        printf("Erro ao abrir o arquivo txt!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return txt;
}

void reportarForma(Arquivo txt,Pacote p) {
    if (txt == NULL || p == NULL) return;

    TipoForma tipo = getTipoForma(p);

    switch (tipo) {
        case CIRCULO:
            Circulo c = getDadosForma(p);
            fprintf(txt, "Círculo - (ID: %d) | | "
                 "Centro: X = %lf "
                 "Y = %lf | | "
                 "Raio: %lf "
                 "Cor de Borda: %s | | "
                 "Cor de Preenchimento: %s ",
                 getIDCirculo(c),
                 getXCirculo(c),
                 getYCirculo(c),
                 getRCirculo(c),
                 getCorBCirculo(c),
                 getCorPCirculo(c));
            break;
        case RETANGULO:
            Retangulo r = getDadosForma(p);
            fprintf(txt, "Retângulo - (ID: %d) | | "
                 "Âncora (Ponto Inferior Esquerdo): X = %lf "
                 "Y = %lf | | "
                 "Largura: %lf | | "
                 "Altura: %lf | | "
                 "Cor de Borda: %s | | "
                 "Cor de Preenchimento: %s ",
                 getIDRetangulo(r),
                 getXRetangulo(r),
                 getYRetangulo(r),
                 getWRetangulo(r),
                 getHRetangulo(r),
                 getCorBRetangulo(r),
                 getCorPRetangulo(r));
            break;
        case LINHA:
            Linha l = getDadosForma(p);
            fprintf(txt, "Linha - (ID: %d) | | "
                 "Ponto de Ínicio: X = %lf "
                 "Y = %lf | | "
                 "Ponto de Fim: X2 = %lf "
                 "Y2 = %lf | | "
                 "Cor: %s ",
                 getIDLinha(l),
                 getX1Linha(l),
                 getY1Linha(l),
                 getX2Linha(l),
                 getY2Linha(l),
                 getCorLinha(l));
            break;
        case TEXTO:
            Texto t = getDadosForma(p);
            fprintf(txt, "Texto - (ID: %d) | | "
                 "Âncora: X = %lf "
                 "Y = %lf | | "
                 "Cor de Borda: %s | | "
                 "Cor de Preenchimento: %s | | "
                 "Local da Âncora: %c | | "
                 "Conteúdo: %s "
                 "\n",
                 getIDTexto(t),
                 getXTexto(t),
                 getYTexto(t),
                 getCorBTexto(t),
                 getCorPTexto(t),
                 getATexto(t),
                 getTxtoTexto(t));
            break;
        case SEGMENTO:
            Segmento s = getDadosForma(p);
            fprintf(txt, "Segmento - (ID: %d) | | "
                "Ponto de Ínicio: X = %lf "
                "Y = %lf | | "
                "Ponto de Fim: X2 = %lf "
                "Y2 = %lf | | "
                "Cor: %s ",
                getIDSegmento(s),
                getX1Segmento(s),
                getY1Segmento(s),
                getX2Segmento(s),
                getY2Segmento(s),
                getCorSegmento(s));
        default:
            printf("ERRO: tipo inválido!\n");
            break;
    }
}

