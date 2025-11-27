//
// Created by natha on 15/10/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "forma.h"

static int MAIOR_ID = 0;

typedef struct {
    Forma form;
    TipoForma tipo;
}pacote;

Pacote CriarPacote(Forma g,TipoForma tipo) {
    pacote* p = (Pacote)malloc(sizeof(pacote));
    if (p == NULL) {
        printf("Erro ao alocar memória ao criarPacote!\n");

        perror("Motivo do erro");
        exit(1);
    }
    p->form = g;
    p->tipo = tipo;

    return p;
}

Forma getDadosForma(Pacote p) {
    return ((pacote*)p)->form;

}

TipoForma getTipoForma(Pacote p) {
    return ((pacote*)p)->tipo;

}

double getAreaForma(Pacote p) {
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);
    switch (tipo) {
        case CIRCULO:
            return calcAreaCirculo(g);
        case RETANGULO:
            return calcAreaRetangulo(g);
        case LINHA:
            return calcAreaLinha(g);
        case TEXTO:
            return calcAreaTexto(g);
        default:
            printf("ERRO: tipo inválido!\n");
            return 0.0;
    }
}

int getIDForma(Pacote p) {
    if (p == NULL) {
        return 0;
    }
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);

    switch (tipo) {
        case CIRCULO:
            return getIDCirculo(g);
        case RETANGULO:
            return getIDRetangulo(g);
        case LINHA:
            return getIDLinha(g);
        case TEXTO:
            return getIDTexto(g);
        default:
            printf("ERRO: tipo inválido!\n");
            return 0;
    }
}

double getXForma(Pacote p) {
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);
    switch (tipo) {
        case CIRCULO:
            return getXCirculo(g);
        case RETANGULO:
            return getXRetangulo(g);
        case LINHA:
            // Retorna o X mínimo da box da linha
            return fmin(getX1Linha(g),getX2Linha(g));
        case TEXTO:
            return getXTexto(g);
        default:
            printf("ERRO: tipo inválido!\n");
            return 0.0;
    }
}

double getYForma(Pacote p) {
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);
    switch (tipo) {
        case CIRCULO:
            return getYCirculo(g);
        case RETANGULO:
            return getYRetangulo(g);
        case LINHA:
            double menorX = fmin(getX1Linha(g),getX2Linha(g));

            if (getX1Linha(g) == getX2Linha(g)) {
                return fmin(getY1Linha(g),getY2Linha(g));
            }

            if (menorX == getX1Linha(g)) {
                return getY1Linha(g);
            }

            return getY2Linha(g);
        case TEXTO:
            return getYTexto(g);
        default:
            printf("ERRO: tipo inválido!\n");
            return 0.0;
    }
}

char* getCorBForma(Pacote p) {
    if (p == NULL) {
        return NULL;
    }
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);

    switch (tipo) {
        case CIRCULO:
            return getCorBCirculo(g);
        case RETANGULO:
            return getCorBRetangulo(g);
        case LINHA:
            return getCorLinha(g);
        case TEXTO:
            return getCorBTexto(g);
        default:
            printf("ERRO: tipo inválido!\n");
            return NULL;
    }
}

char* getCorPForma(Pacote p) {
    if (p == NULL) {
        return NULL;
    }
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);

    switch (tipo) {
        case CIRCULO:
            return getCorPCirculo(g);
        case RETANGULO:
            return getCorPRetangulo(g);
        case LINHA:
            // Cor de preenchimento da linha é a cor complementar da cor de borda
            return CorComplementarLinha(g);
        case TEXTO:
            return getCorPTexto(g);
        default:
            printf("ERRO: tipo inválido!\n");
            return NULL;
    }
}

void setCorBForma(Pacote p, char* corB) {
    if (p == NULL) {
        return;
    }
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);

    switch (tipo) {
        case CIRCULO:
            setCorBCirculo(g,corB);
            break;
        case RETANGULO:
            setCorBRetangulo(g,corB);
            break;
        case LINHA:
            setCorLinha(g,corB);
            break;
        case TEXTO:
            setCorBTexto(g,corB);
            break;
        default:
            printf("ERRO: tipo inválido!\n");
            return;
    }
}

void setCorPForma(Pacote p, char* corP) {
    if (p == NULL) {
        return;
    }
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);

    switch (tipo) {
        case CIRCULO:
            setCorPCirculo(g,corP);
            break;
        case RETANGULO:
            setCorPRetangulo(g,corP);
            break;
        case LINHA:
            break;
        case TEXTO:
            setCorPTexto(g,corP);
            break;
        default:
            printf("ERRO: tipo inválido!\n");
            return;
    }
}

void armazenaMaiorId(int maior_id) {
    MAIOR_ID = maior_id + 1;
}

int getMaiorId() {
    return MAIOR_ID;
}

Pacote clonarForma(Pacote p) {
    TipoForma tipo = getTipoForma(p);

    int novo_id = getMaiorId();

    switch (tipo) {
        case CIRCULO: {
            Circulo c = getDadosForma(p);
            Circulo clone = CriarCirculo(novo_id,
                getXCirculo(c),
                getYCirculo(c),
                getRCirculo(c),
                getCorBCirculo(c),
                getCorPCirculo(c));
            MAIOR_ID++;
            return CriarPacote(clone,CIRCULO);
        }
        case RETANGULO: {
            Retangulo r = getDadosForma(p);
            Retangulo clone = CriarRetangulo(novo_id,
                getXRetangulo(r),
                getYRetangulo(r),
                getWRetangulo(r),
                getHRetangulo(r),
                getCorBRetangulo(r),
                getCorPRetangulo(r));
            MAIOR_ID++;
            return CriarPacote(clone,RETANGULO);
        }
        case LINHA: {
            Linha l = getDadosForma(p);
            Linha clone = CriarLinha(novo_id,
                getX1Linha(l),
                getY1Linha(l),
                getX2Linha(l),
                getY2Linha(l),
                getCorLinha(l));
            MAIOR_ID++;
            return CriarPacote(clone,LINHA);
        }
        case TEXTO: {
            Texto t = getDadosForma(p);
            Texto clone = CriarTexto(novo_id,
                getXTexto(t),
                getYTexto(t),
                getCorBTexto(t),
                getCorPTexto(t),
                getATexto(t),
                getTxtoTexto(t));
            MAIOR_ID++;
            return CriarPacote(clone,TEXTO);
        }
        default:
            printf("ERRO: tipo inválido!\n");
            return NULL;
    }
}

void liberarForma(Pacote p) {
    if (p == NULL) {
        return;
    }
    TipoForma tipo = getTipoForma(p);
    Forma g = getDadosForma(p);

    switch (tipo) {
        case CIRCULO:
            eliminarCirculo(g);
            break;
        case RETANGULO:
            eliminarRetangulo(g);
            break;
        case LINHA:
            eliminarLinha(g);
            break;
        case TEXTO:
            eliminarTexto(g);
            break;
        default:
            printf("ERRO: tipo inválido encontrado em liberarForma!\n");
            return;
    }
    free(p); // Libera a struct Pacote
}