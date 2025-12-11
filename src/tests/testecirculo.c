//
// Created by natha on 02/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../circulo.h"

// --- FUNÇÃO AUXILIAR DE VERIFICAÇÃO ---
void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1); // Para o teste imediatamente se falhar
    }
}

// --- FUNÇÃO AUXILIAR PARA DOUBLE (EVITAR ERROS DE ARREDONDAMENTO) ---
int sao_iguais(double a, double b) {
    return fabs(a - b) < 1e-6;
}

// --- TESTES ---

void teste_criacao_leitura() {
    printf("\n--- Teste 1: Criacao e Leitura (Getters) ---\n");

    // Cria um círculo: ID 10, X=5.5, Y=6.6, Raio=3.0, Borda="red", Preenchimento="blue"
    Circulo c = CriarCirculo(10, 5.5, 6.6, 3.0, "red", "blue");

    verificar(c != NULL, "O circulo foi alocado na memoria");

    // Testa IDs e Numeros
    verificar(getIDCirculo(c) == 10, "ID deve ser 10");
    verificar(sao_iguais(getXCirculo(c), 5.5), "X deve ser 5.5");
    verificar(sao_iguais(getYCirculo(c), 6.6), "Y deve ser 6.6");
    verificar(sao_iguais(getRCirculo(c), 3.0), "Raio deve ser 3.0");

    // Testa Strings
    verificar(strcmp(getCorBCirculo(c), "red") == 0, "Cor de borda inicial deve ser red");
    verificar(strcmp(getCorPCirculo(c), "blue") == 0, "Cor de preenchimento inicial deve ser blue");

    eliminarCirculo(c);
}

void teste_modificacao_numerica() {
    printf("\n--- Teste 2: Modificacao de Numeros (Setters) ---\n");

    Circulo c = CriarCirculo(1, 0, 0, 1, "none", "none");

    setIDCirculo(c, 999);
    setXCirculo(c, 123.45);
    setYCirculo(c, -50.0);
    setRCirculo(c, 100.0);

    verificar(getIDCirculo(c) == 999, "ID alterado para 999");
    verificar(sao_iguais(getXCirculo(c), 123.45), "X alterado para 123.45");
    verificar(sao_iguais(getYCirculo(c), -50.0), "Y alterado para -50.0");
    verificar(sao_iguais(getRCirculo(c), 100.0), "Raio alterado para 100.0");

    eliminarCirculo(c);
}

void teste_modificacao_cores_realloc() {
    printf("\n--- Teste 3: Modificacao de Cores (Realloc) ---\n");

    // Começa com string pequena
    Circulo c = CriarCirculo(5, 10, 10, 5, "red", "blue");

    // 1. Aumentar o tamanho da string (Testa se o realloc expande)
    char* corGrande = "dark_olive_green_with_transparency";
    setCorBCirculo(c, corGrande);

    printf("   Nova cor borda: %s\n", getCorBCirculo(c));
    verificar(strcmp(getCorBCirculo(c), corGrande) == 0, "Cor da borda expandida corretamente");

    // 2. Diminuir o tamanho da string
    setCorPCirculo(c, "w");

    printf("   Nova cor preenchimento: %s\n", getCorPCirculo(c));
    verificar(strcmp(getCorPCirculo(c), "w") == 0, "Cor de preenchimento reduzida corretamente");

    eliminarCirculo(c);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO CIRCULO\n");
    printf("==========================================\n");

    teste_criacao_leitura();
    teste_modificacao_numerica();
    teste_modificacao_cores_realloc();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}