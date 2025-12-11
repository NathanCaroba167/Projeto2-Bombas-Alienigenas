//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../retangulo.h"
#include "../circulo.h"
#include "../linha.h"
#include "../texto.h"

#include "../segmentador.h"
#include "../lista.h"
#include "../segmento.h"
#include "../forma.h"

// --- MOCKS (SIMULADORES) ---

static int ID_GLOBAL = 1000;
int getMaiorId() { return ID_GLOBAL; }
void adicionaMaiorID(int n) { ID_GLOBAL += n; }
void reportarForma(FILE* f, Pacote p) {} // Mock vazio

// --- AUXILIARES ---

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

int sao_iguais(double a, double b) {
    return fabs(a - b) < 1e-4;
}

// --- TESTES ---

void teste_converte_retangulo() {
    printf("\n--- Teste 1: Retangulo -> 4 Segmentos ---\n");
    Lista anteparos = iniciarLista();
    Retangulo r = CriarRetangulo(1, 10, 10, 100, 50, "black", "white");

    converteRetanguloSegmento(stdout, r, anteparos);

    int qtd = getTamanhoLista(anteparos);
    printf("   Segmentos gerados: %d\n", qtd);
    verificar(qtd == 4, "Retangulo deve gerar 4 segmentos");

    pont node = getPrimeiroElementoLista(anteparos);
    Pacote p = getPacoteElementoLista(node);
    Segmento s = getDadosForma(p);

    verificar(sao_iguais(getX1Segmento(s), 10), "X1 do segmento esquerdo OK");
    verificar(sao_iguais(getY1Segmento(s), 60), "Y1 do segmento esquerdo OK");

    eliminarRetangulo(r);
}

void teste_converte_circulo() {
    printf("\n--- Teste 2: Circulo -> 1 Segmento ---\n");
    Lista anteparos = iniciarLista();
    Circulo c = CriarCirculo(2, 50, 50, 10, "red", "red");

    // Caso 'h'
    converteCirculoSegmento(stdout, c, anteparos, 'h');
    Segmento s = getDadosForma(getPacoteElementoLista(getPrimeiroElementoLista(anteparos)));
    verificar(sao_iguais(getX1Segmento(s), 40.0), "X1 horizontal = 40 (50-10)");
    verificar(sao_iguais(getX2Segmento(s), 60.0), "X2 horizontal = 60 (50+10)");

    // Caso 'v'
    converteCirculoSegmento(stdout, c, anteparos, 'v');
    s = getDadosForma(getPacoteElementoLista(getPrimeiroElementoLista(anteparos)));
    verificar(sao_iguais(getY1Segmento(s), 40.0), "Y1 vertical = 40 (50-10)");

    eliminarCirculo(c);
}

void teste_converte_texto() {
    printf("\n--- Teste 3: Texto (Ancoras i, f, m) ---\n");

    Lista anteparos = iniciarLista();

    Texto t = CriarTexto(3, 100, 100, "black", "black", 'i', "ABC");

    converteTextoSegmento(stdout, t, anteparos);
    Segmento s = getDadosForma(getPacoteElementoLista(getPrimeiroElementoLista(anteparos)));

    printf("   [i] Esperado: 100 a 130. Recebido: %.1f a %.1f\n", getX1Segmento(s), getX2Segmento(s));
    verificar(sao_iguais(getX1Segmento(s), 100.0), "Ancora 'i' X1 OK");
    verificar(sao_iguais(getX2Segmento(s), 130.0), "Ancora 'i' X2 OK");

    setATexto(t, 'f');
    anteparos = iniciarLista();
    converteTextoSegmento(stdout, t, anteparos);
    s = getDadosForma(getPacoteElementoLista(getPrimeiroElementoLista(anteparos)));

    printf("   [f] Esperado: 70 a 100. Recebido: %.1f a %.1f\n", getX1Segmento(s), getX2Segmento(s));
    verificar(sao_iguais(getX1Segmento(s), 70.0), "Ancora 'f' X1 OK");
    verificar(sao_iguais(getX2Segmento(s), 100.0), "Ancora 'f' X2 OK");

    setATexto(t, 'm');
    anteparos = iniciarLista();
    converteTextoSegmento(stdout, t, anteparos);
    s = getDadosForma(getPacoteElementoLista(getPrimeiroElementoLista(anteparos)));

    printf("   [m] Esperado: 85 a 115. Recebido: %.1f a %.1f\n", getX1Segmento(s), getX2Segmento(s));
    verificar(sao_iguais(getX1Segmento(s), 85.0), "Ancora 'm' X1 (85.0) OK");
    verificar(sao_iguais(getX2Segmento(s), 115.0), "Ancora 'm' X2 (115.0) OK");

    eliminarTexto(t);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO SEGMENTADOR\n");
    printf("==========================================\n");

    teste_converte_retangulo();
    teste_converte_circulo();
    teste_converte_texto();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}