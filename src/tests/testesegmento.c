//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../segmento.h"

// --- FUNÇÕES AUXILIARES ---

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

int sao_iguais(double a, double b) {
    return fabs(a - b) < 1e-6;
}

// --- TESTES ---

void teste_criacao_leitura() {
    printf("\n--- Teste 1: Criacao e Getters Basicos ---\n");

    // Segmento: ID 10, (0,0) -> (10,10), Cor "black", Tipo ANTEPARO
    Segmento s = CriarSegmento(10, 0.0, 0.0, 10.0, 10.0, "black", ANTEPARO);

    verificar(s != NULL, "O segmento foi alocado");

    verificar(getIDSegmento(s) == 10, "ID correto");
    verificar(sao_iguais(getX1Segmento(s), 0.0), "X1 correto");
    verificar(sao_iguais(getY1Segmento(s), 0.0), "Y1 correto");
    verificar(sao_iguais(getX2Segmento(s), 10.0), "X2 correto");
    verificar(sao_iguais(getY2Segmento(s), 10.0), "Y2 correto");

    verificar(strcmp(getCorSegmento(s), "black") == 0, "Cor correta");
    verificar(getTipoSegmento(s) == ANTEPARO, "Tipo correto");

    eliminarSegmento(s);
}

void teste_modificacao_pontos_cor() {
    printf("\n--- Teste 2: Modificacao (Setters e Realloc) ---\n");

    Segmento s = CriarSegmento(1, 0, 0, 1, 1, "red", ANTEPARO);

    // Mudar ID
    setIDSegmento(s, 50);
    verificar(getIDSegmento(s) == 50, "ID alterado");

    // Mudar Pontos (P1 e P2)
    setP1Segmento(s, 5.5, 6.6);
    setP2Segmento(s, 10.5, 20.5);

    verificar(sao_iguais(getX1Segmento(s), 5.5), "X1 alterado via setP1");
    verificar(sao_iguais(getY1Segmento(s), 6.6), "Y1 alterado via setP1");
    verificar(sao_iguais(getX2Segmento(s), 10.5), "X2 alterado via setP2");
    verificar(sao_iguais(getY2Segmento(s), 20.5), "Y2 alterado via setP2");

    // Mudar Cor (Testar Realloc)
    // 1. Expandir
    char* corLonga = "purple_dark_neon_glowing";
    setCorSegmento(s, corLonga);
    verificar(strcmp(getCorSegmento(s), corLonga) == 0, "Cor expandida com sucesso");

    // 2. Reduzir
    setCorSegmento(s, "#FFF");
    verificar(strcmp(getCorSegmento(s), "#FFF") == 0, "Cor reduzida com sucesso");

    eliminarSegmento(s);
}

void teste_calculo_tamanho() {
    printf("\n--- Teste 3: Calculo de Tamanho (Pitagoras) ---\n");

    // Triângulo 3-4-5
    // P1(0,0) -> P2(3,4). Hipotenusa deve ser 5.
    Segmento s = CriarSegmento(1, 0.0, 0.0, 3.0, 4.0, "none", ANTEPARO);

    double tam = calcTamanhoSegmento(s);
    printf("   Tamanho calculado: %.2f\n", tam);

    verificar(sao_iguais(tam, 5.0), "Tamanho do segmento deve ser 5.0");

    eliminarSegmento(s);
}

void teste_orientacao_geometrica() {
    printf("\n--- Teste 4: Orientacao (Produto Vetorial) ---\n");

    // Vamos criar um segmento horizontal no eixo X
    // (0,0) ----> (10,0)
    Segmento s = CriarSegmento(1, 0.0, 0.0, 10.0, 0.0, "black", ANTEPARO);

    double val1 = orientacaoPontoSegmento(s, 5.0, 5.0);
    printf("   (5,5) Orientacao: %.2f (Esperado > 0)\n", val1);
    verificar(val1 > 0, "Ponto (5,5) esta a esquerda/acima");

    double val2 = orientacaoPontoSegmento(s, 5.0, -5.0);
    printf("   (5,-5) Orientacao: %.2f (Esperado < 0)\n", val2);
    verificar(val2 < 0, "Ponto (5,-5) esta a direita/abaixo");

    double val3 = orientacaoPontoSegmento(s, 5.0, 0.0);
    printf("   (5,0) Orientacao: %.2f (Esperado == 0)\n", val3);
    verificar(sao_iguais(val3, 0.0), "Ponto (5,0) e colinear");

    eliminarSegmento(s);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO SEGMENTO\n");
    printf("==========================================\n");

    teste_criacao_leitura();
    teste_modificacao_pontos_cor();
    teste_calculo_tamanho();
    teste_orientacao_geometrica();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}