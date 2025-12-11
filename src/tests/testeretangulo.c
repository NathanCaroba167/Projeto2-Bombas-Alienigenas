//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../retangulo.h"

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

    // Cria retângulo: ID 5, X=10, Y=20, W=100, H=50, Borda="black", Preenchimento="white"
    Retangulo r = CriarRetangulo(5, 10.0, 20.0, 100.0, 50.0, "black", "white");

    verificar(r != NULL, "O retangulo foi alocado");

    // Verificações numéricas
    verificar(getIDRetangulo(r) == 5, "ID deve ser 5");
    verificar(sao_iguais(getXRetangulo(r), 10.0), "X deve ser 10.0");
    verificar(sao_iguais(getYRetangulo(r), 20.0), "Y deve ser 20.0");
    verificar(sao_iguais(getWRetangulo(r), 100.0), "W deve ser 100.0");
    verificar(sao_iguais(getHRetangulo(r), 50.0), "H deve ser 50.0");

    // Verificações de String
    verificar(strcmp(getCorBRetangulo(r), "black") == 0, "Cor borda deve ser black");
    verificar(strcmp(getCorPRetangulo(r), "white") == 0, "Cor preenchimento deve ser white");

    eliminarRetangulo(r);
}

void teste_modificacao_numerica() {
    printf("\n--- Teste 2: Setters Numericos ---\n");

    Retangulo r = CriarRetangulo(0, 0, 0, 0, 0, "none", "none");

    setIDRetangulo(r, 999);
    setXRetangulo(r, 15.5);
    setYRetangulo(r, 25.5);
    setWRetangulo(r, 200.0);
    setHRetangulo(r, 150.0);

    verificar(getIDRetangulo(r) == 999, "ID alterado para 999");
    verificar(sao_iguais(getXRetangulo(r), 15.5), "X alterado corretamente");
    verificar(sao_iguais(getYRetangulo(r), 25.5), "Y alterado corretamente");
    verificar(sao_iguais(getWRetangulo(r), 200.0), "W alterado corretamente");
    verificar(sao_iguais(getHRetangulo(r), 150.0), "H alterado corretamente");

    eliminarRetangulo(r);
}

void teste_modificacao_cor_realloc() {
    printf("\n--- Teste 3: SetCor (Realloc) ---\n");

    // Começa com string média
    Retangulo r = CriarRetangulo(1, 0, 0, 10, 10, "green", "yellow");

    // 1. Aumentar string da borda
    char* corGrande = "dark_slate_blue_muito_longo";
    setCorBRetangulo(r, corGrande);
    verificar(strcmp(getCorBRetangulo(r), corGrande) == 0, "Cor borda expandida corretamente");

    // 2. Diminuir string do preenchimento
    setCorPRetangulo(r, "red");
    verificar(strcmp(getCorPRetangulo(r), "red") == 0, "Cor preenchimento reduzida corretamente");

    // 3. Teste cruzado (Trocar as duas)
    setCorBRetangulo(r, "#000");
    setCorPRetangulo(r, "#FFF");

    verificar(strcmp(getCorBRetangulo(r), "#000") == 0, "Cor borda alterada para hex");
    verificar(strcmp(getCorPRetangulo(r), "#FFF") == 0, "Cor preenchimento alterada para hex");

    eliminarRetangulo(r);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO RETANGULO\n");
    printf("==========================================\n");

    teste_criacao_leitura();
    teste_modificacao_numerica();
    teste_modificacao_cor_realloc();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}