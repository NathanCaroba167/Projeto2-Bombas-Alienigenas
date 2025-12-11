//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../linha.h"

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
    printf("\n--- Teste 1: Criacao e Getters ---\n");

    // Cria linha: ID 1, (10,10) -> (20,20), Cor "black"
    Linha l = CriarLinha(1, 10.0, 10.0, 20.0, 20.0, "black");

    verificar(l != NULL, "A linha foi alocada");

    verificar(getIDLinha(l) == 1, "ID deve ser 1");
    verificar(sao_iguais(getX1Linha(l), 10.0), "X1 deve ser 10.0");
    verificar(sao_iguais(getY1Linha(l), 10.0), "Y1 deve ser 10.0");
    verificar(sao_iguais(getX2Linha(l), 20.0), "X2 deve ser 20.0");
    verificar(sao_iguais(getY2Linha(l), 20.0), "Y2 deve ser 20.0");

    verificar(strcmp(getCorLinha(l), "black") == 0, "Cor deve ser black");

    eliminarLinha(l);
}

void teste_modificacao_numerica() {
    printf("\n--- Teste 2: Setters Numericos ---\n");

    Linha l = CriarLinha(0, 0, 0, 0, 0, "none");

    setIDLinha(l, 99);
    setX1Linha(l, 1.5);
    setY1Linha(l, 2.5);
    setX2Linha(l, 3.5);
    setY2Linha(l, 4.5);

    verificar(getIDLinha(l) == 99, "ID alterado para 99");
    verificar(sao_iguais(getX1Linha(l), 1.5), "X1 alterado corretamente");
    verificar(sao_iguais(getY1Linha(l), 2.5), "Y1 alterado corretamente");
    verificar(sao_iguais(getX2Linha(l), 3.5), "X2 alterado corretamente");
    verificar(sao_iguais(getY2Linha(l), 4.5), "Y2 alterado corretamente");

    eliminarLinha(l);
}

void teste_modificacao_cor_realloc() {
    printf("\n--- Teste 3: SetCor (Realloc) ---\n");

    Linha l = CriarLinha(1, 0, 0, 10, 10, "red");

    // Aumentar string
    char* corGrande = "#FF0000_vermelho_muito_intenso";
    setCorLinha(l, corGrande);
    verificar(strcmp(getCorLinha(l), corGrande) == 0, "Cor expandida corretamente");

    // Diminuir string
    setCorLinha(l, "#000");
    verificar(strcmp(getCorLinha(l), "#000") == 0, "Cor reduzida corretamente");

    eliminarLinha(l);
}

void teste_cor_complementar() {
    printf("\n--- Teste 4: Cor Complementar ---\n");

    // Caso 1: Branco (#FFFFFF) -> Preto (#000000)
    // 255,255,255 -> Inverso: 0,0,0
    Linha l1 = CriarLinha(1, 0,0,0,0, "#FFFFFF");
    char* comp1 = CorComplementarLinha(l1);

    printf("   Original: #FFFFFF -> Complementar: %s\n", comp1);
    verificar(strcmp(comp1, "#000000") == 0, "Complementar de Branco deve ser Preto");

    free(comp1); // IMPORTANTE: CorComplementar faz malloc, temos que dar free
    eliminarLinha(l1);

    // Caso 2: Preto (#000000) -> Branco (#FFFFFF)
    Linha l2 = CriarLinha(2, 0,0,0,0, "#000000");
    char* comp2 = CorComplementarLinha(l2);

    printf("   Original: #000000 -> Complementar: %s\n", comp2);
    verificar(strcmp(comp2, "#FFFFFF") == 0, "Complementar de Preto deve ser Branco");

    free(comp2);
    eliminarLinha(l2);

    // Caso 3: Sem o Hash (AAAAAA) -> (555555)
    // AA (Hex) = 170. 255 - 170 = 85. 85 (Hex) = 55.
    Linha l3 = CriarLinha(3, 0,0,0,0, "AAAAAA");
    char* comp3 = CorComplementarLinha(l3);

    printf("   Original: AAAAAA -> Complementar: %s\n", comp3);
    verificar(strcmp(comp3, "#555555") == 0, "Calculo correto mesmo sem # na entrada");

    free(comp3);
    eliminarLinha(l3);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO LINHA\n");
    printf("==========================================\n");

    teste_criacao_leitura();
    teste_modificacao_numerica();
    teste_modificacao_cor_realloc();
    teste_cor_complementar();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}