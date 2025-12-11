//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../texto.h"

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

void teste_estilo_ciclo_vida() {
    printf("\n--- Teste 1: Estilo (Criacao e Modificacao) ---\n");

    // 1. Criação
    Estilo e = CriarEstilo("sans-serif", "normal", "12px");
    verificar(e != NULL, "Estilo alocado");

    // 2. Leitura
    verificar(strcmp(getFontFamilyTexto(e), "sans-serif") == 0, "Family inicial correta");
    verificar(strcmp(getFontWeightTexto(e), "normal") == 0, "Weight inicial correto");
    verificar(strcmp(getFontSizeTexto(e), "12px") == 0, "Size inicial correto");

    // 3. Modificação (Setters com Realloc)

    // Aumentando string (Family)
    char* novaFamily = "Times New Roman Extra Bold";
    setFontFamilyTexto(e, novaFamily);
    verificar(strcmp(getFontFamilyTexto(e), novaFamily) == 0, "Family alterada (expandida)");

    // Mudando outros atributos
    setFontWeightTexto(e, "bold");
    setFontSizeTexto(e, "16pt");

    verificar(strcmp(getFontWeightTexto(e), "bold") == 0, "Weight alterado");
    verificar(strcmp(getFontSizeTexto(e), "16pt") == 0, "Size alterado");

    // 4. Eliminação
    eliminarEstilo(e);
}

void teste_texto_dados_basicos() {
    printf("\n--- Teste 2: Texto (Dados Numericos) ---\n");

    // ID 1, x=10, y=20, ancora='i' (inicio)
    Texto t = CriarTexto(1, 10.5, 20.5, "black", "white", 'i', "Ola");

    verificar(t != NULL, "Texto alocado");

    // Getters
    verificar(getIDTexto(t) == 1, "ID correto");
    verificar(sao_iguais(getXTexto(t), 10.5), "X correto");
    verificar(sao_iguais(getYTexto(t), 20.5), "Y correto");
    verificar(getATexto(t) == 'i', "Ancora correta");

    // Setters
    setIDTexto(t, 50);
    setXTexto(t, 0.0);
    setYTexto(t, -5.5);
    setATexto(t, 'm'); // meio

    verificar(getIDTexto(t) == 50, "ID alterado");
    verificar(sao_iguais(getXTexto(t), 0.0), "X alterado");
    verificar(sao_iguais(getYTexto(t), -5.5), "Y alterado");
    verificar(getATexto(t) == 'm', "Ancora alterada");

    eliminarTexto(t);
}

void teste_texto_strings_dinamicas() {
    printf("\n--- Teste 3: Texto (Strings e Realloc) ---\n");

    Texto t = CriarTexto(1, 0, 0, "red", "blue", 'i', "Texto Curto");

    // Verifica inicial
    verificar(strcmp(getTxtoTexto(t), "Texto Curto") == 0, "Conteudo inicial correto");
    verificar(quantidadeCaracteresTexto(t) == 11, "Quantidade de caracteres correta (11)");

    // 1. Modificar Conteúdo para algo maior (Realloc expande)
    char* textoLongo = "Este e um texto muito maior para testar o realloc de memoria";
    setTxtoTexto(t, textoLongo);

    verificar(strcmp(getTxtoTexto(t), textoLongo) == 0, "Conteudo expandido com sucesso");
    verificar(quantidadeCaracteresTexto(t) == strlen(textoLongo), "Nova quantidade de caracteres correta");

    // 2. Modificar Cores
    setCorBTexto(t, "#FFAA00"); // Hexadecimal maior que "red"
    setCorPTexto(t, "cyan");

    verificar(strcmp(getCorBTexto(t), "#FFAA00") == 0, "Cor borda alterada");
    verificar(strcmp(getCorPTexto(t), "cyan") == 0, "Cor preenchimento alterada");

    eliminarTexto(t);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO TEXTO\n");
    printf("==========================================\n");

    teste_estilo_ciclo_vida();
    teste_texto_dados_basicos();
    teste_texto_strings_dinamicas();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}