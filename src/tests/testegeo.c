//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../geo.h"
#include "../lista.h"
#include "../forma.h"
#include "../circulo.h"
#include "../retangulo.h"
#include "../linha.h"
#include "../texto.h"

// --- MOCK (SIMULAÇÃO) ---
int ID_MAX_CAPTURADO = 0;

void armazenaMaiorId(int id) {
    if (id > ID_MAX_CAPTURADO) {
        ID_MAX_CAPTURADO = id;
    }
}

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
    return (a - b < 0.0001) && (b - a < 0.0001);
}

void criar_arquivo_teste(const char* nome, const char* conteudo) {
    FILE* f = fopen(nome, "w");
    if (!f) {
        printf("Erro ao criar arquivo de teste temporario.\n");
        exit(1);
    }
    fprintf(f, "%s", conteudo);
    fclose(f);
}

// --- TESTES ---

void teste_leitura_formas_basicas() {
    printf("\n--- Teste 1: Leitura de Formas (c, r, l) ---\n");

    const char* NOME_ARQ = "temp_teste_1.geo";
    const char* CONTEUDO =
        "c 1 10.5 20.5 5.0 red blue\n"
        "r 2 100 100 50 20 black white\n"
        "l 3 0 0 10 10 green\n";

    criar_arquivo_teste(NOME_ARQ, CONTEUDO);

    Lista lista = iniciarLista();
    Estilo estiloAtual = NULL;

    FILE* f = fopen(NOME_ARQ, "r");
    criarFormasNaLista(f, lista, &estiloAtual);
    fclose(f);

    // Verificações

    // 1. Quantidade
    verificar(getTamanhoLista(lista) == 3, "Leu 3 formas");

    // 2. Verificar Ordem e Tipos (Inserção no Fim)
    pont no = getPrimeiroElementoLista(lista);

    // Círculo (ID 1)
    Pacote p1 = getPacoteElementoLista(no);
    verificar(getTipoForma(p1) == CIRCULO, "Primeiro item e Circulo");
    Circulo c = getDadosForma(p1);
    verificar(getIDCirculo(c) == 1, "ID do circulo e 1");
    verificar(sao_iguais(getRCirculo(c), 5.0), "Raio do circulo e 5.0");
    verificar(strcmp(getCorBCirculo(c), "red") == 0, "Cor borda red");

    // Retângulo (ID 2)
    no = getProximoElementoLista(no);
    Pacote p2 = getPacoteElementoLista(no);
    verificar(getTipoForma(p2) == RETANGULO, "Segundo item e Retangulo");
    Retangulo r = getDadosForma(p2);
    verificar(getIDRetangulo(r) == 2, "ID do retangulo e 2");
    verificar(sao_iguais(getWRetangulo(r), 50.0), "Largura 50");

    // Linha (ID 3)
    no = getProximoElementoLista(no);
    Pacote p3 = getPacoteElementoLista(no);
    verificar(getTipoForma(p3) == LINHA, "Terceiro item e Linha");
    Linha l = getDadosForma(p3);
    verificar(getIDLinha(l) == 3, "ID da linha e 3");

    // Verifica Maior ID Global
    verificar(ID_MAX_CAPTURADO == 3, "Maior ID capturado corretamente (3)");

    // Limpeza
    liberarLista(lista);
    if (estiloAtual) eliminarEstilo(estiloAtual);
    remove(NOME_ARQ);
}

void teste_texto_e_estilo() {
    printf("\n--- Teste 2: Texto e Estilo (ts abreviado) ---\n");

    // Testes:
    // 1. Tradução de 'b' para 'bold'
    // 2. Leitura de texto com espaços "Ola Mundo"

    const char* NOME_ARQ = "temp_teste_2.geo";
    const char* CONTEUDO =
        "ts sans b 12pt\n"
        "t 10 50 50 yellow purple m Ola Mundo Cruel\n";

    criar_arquivo_teste(NOME_ARQ, CONTEUDO);

    Lista lista = iniciarLista();
    Estilo estiloAtual = NULL;

    FILE* f = fopen(NOME_ARQ, "r");
    criarFormasNaLista(f, lista, &estiloAtual);
    fclose(f);

    // Verifica Estilo (efeito colateral do ts)
    verificar(estiloAtual != NULL, "Estilo foi criado");
    printf("   Weight lido: %s\n", getFontWeightTexto(estiloAtual));
    verificar(strcmp(getFontWeightTexto(estiloAtual), "bold") == 0, "Traduziu 'b' para 'bold'");
    verificar(strcmp(getFontFamilyTexto(estiloAtual), "sans") == 0, "Leu familia 'sans'");

    // Verifica Texto
    verificar(getTamanhoLista(lista) == 1, "Leu 1 texto");
    Pacote p = getPacoteElementoLista(getPrimeiroElementoLista(lista));
    Texto t = getDadosForma(p);

    printf("   Conteudo lido: '%s'\n", getTxtoTexto(t));
    verificar(strcmp(getTxtoTexto(t), "Ola Mundo Cruel") == 0, "Leu texto com espacos corretamente");
    verificar(getATexto(t) == 'm', "Leu ancora 'm'");

    liberarLista(lista);
    eliminarEstilo(estiloAtual);
    remove(NOME_ARQ);
}

void teste_arquivo_vazio_ou_comentarios() {
    printf("\n--- Teste 3: Linhas Vazias e Resiliencia ---\n");

    const char* NOME_ARQ = "temp_teste_3.geo";
    // Arquivo cheio de enters e espaços
    const char* CONTEUDO =
        "\n"
        "\n"
        "c 99 0 0 1 r r\n"
        "\n";

    criar_arquivo_teste(NOME_ARQ, CONTEUDO);

    Lista lista = iniciarLista();
    Estilo estiloAtual = NULL;

    FILE* f = fopen(NOME_ARQ, "r");
    criarFormasNaLista(f, lista, &estiloAtual);
    fclose(f);

    verificar(getTamanhoLista(lista) == 1, "Ignorou linhas vazias e leu o circulo");

    liberarLista(lista);
    if(estiloAtual) eliminarEstilo(estiloAtual);
    remove(NOME_ARQ);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO GEO (PARSER)\n");
    printf("==========================================\n");

    teste_leitura_formas_basicas();
    teste_texto_e_estilo();
    teste_arquivo_vazio_ou_comentarios();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}