//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../qry.h"
#include "../lista.h"
#include "../txt.h"

// --- VARIAVEIS GLOBAIS DE VERIFICACAO (OS ESPIÕES) ---

int MOCK_ANTEPARO_CHAMADO = 0;
int MOCK_A_INI = 0, MOCK_A_FIM = 0;
char MOCK_A_DIR = ' ';

int MOCK_DESTRUICAO_CHAMADO = 0;
double MOCK_D_X = 0, MOCK_D_Y = 0;
char MOCK_D_SFX[100];

int MOCK_PINTURA_CHAMADO = 0;
char MOCK_P_COR[100];

int MOCK_CLONE_CHAMADO = 0;
double MOCK_C_DX = 0, MOCK_C_DY = 0;

// --- FUNÇÃO AUXILIAR ---
void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

void resetar_mocks() {
    MOCK_ANTEPARO_CHAMADO = 0;
    MOCK_DESTRUICAO_CHAMADO = 0;
    MOCK_PINTURA_CHAMADO = 0;
    MOCK_CLONE_CHAMADO = 0;
    memset(MOCK_D_SFX, 0, 100);
    memset(MOCK_P_COR, 0, 100);
}

// ============================================================================
// 1. MOCKS (SUBSTITUEM O BOMBAS.C)
// ============================================================================

void Anteparo(Arquivo txt, Lista formas, Lista anteparos, int inicial, int final, char direcao) {
    MOCK_ANTEPARO_CHAMADO = 1;
    MOCK_A_INI = inicial;
    MOCK_A_FIM = final;
    MOCK_A_DIR = direcao;
}

void Destruicao(Arquivo svg, Arquivo txt, Lista formas, Lista anteparos, double xBomba, double yBomba, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd, int limIns) {
    MOCK_DESTRUICAO_CHAMADO = 1;
    MOCK_D_X = xBomba;
    MOCK_D_Y = yBomba;
    if(sfx_modo) strcpy(MOCK_D_SFX, sfx_modo);
}

void Pintura(Arquivo svg, Arquivo txt, Lista formas, Lista anteparos, double xBomba, double yBomba, char* cor, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd, int limIns) {
    MOCK_PINTURA_CHAMADO = 1;
    if(cor) strcpy(MOCK_P_COR, cor);
}

void Clone(Arquivo svg, Arquivo txt, Lista formas, Lista anteparos, double xBomba, double yBomba, double dx, double dy, char* sfx_modo, char* caminhoBaseSaida, char tipoOrd, int limIns) {
    MOCK_CLONE_CHAMADO = 1;
    MOCK_C_DX = dx;
    MOCK_C_DY = dy;
}

// ============================================================================
// 2. TESTES
// ============================================================================

void criar_arquivo_teste(const char* nome, const char* conteudo) {
    FILE* f = fopen(nome, "w");
    if (!f) { printf("Erro criar arquivo teste\n"); exit(1); }
    fprintf(f, "%s", conteudo);
    fclose(f);
}

void teste_comando_anteparo() {
    printf("\n--- Teste 1: Comando 'a' (Anteparo) ---\n");
    resetar_mocks();

    const char* NOME = "temp_qry_1.qry";
    // Comando: a [id_ini] [id_fim] [dir]
    criar_arquivo_teste(NOME, "a 10 20 v\n");

    Arquivo qry = abrirQry((char*)NOME);

    LerComandosExecutar(NULL, stdout, qry, NULL, NULL, 'q', 10, "out");
    fclose(qry);

    verificar(MOCK_ANTEPARO_CHAMADO == 1, "Funcao Anteparo foi chamada");
    verificar(MOCK_A_INI == 10, "ID Inicial correto (10)");
    verificar(MOCK_A_FIM == 20, "ID Final correto (20)");
    verificar(MOCK_A_DIR == 'v', "Direcao correta ('v')");

    remove(NOME);
}

void teste_comando_destruicao() {
    printf("\n--- Teste 2: Comando 'd' (Destruicao) ---\n");
    resetar_mocks();

    const char* NOME = "temp_qry_2.qry";
    // Comando: d [x] [y] [sufixo]
    criar_arquivo_teste(NOME, "d 55.5 66.6 sulfixo-teste\n");

    Arquivo qry = abrirQry((char*)NOME);
    LerComandosExecutar(NULL, stdout, qry, NULL, NULL, 'q', 10, "out");
    fclose(qry);

    verificar(MOCK_DESTRUICAO_CHAMADO == 1, "Funcao Destruicao foi chamada");

    printf("   X Lido: %.2f | Y Lido: %.2f\n", MOCK_D_X, MOCK_D_Y);
    verificar((MOCK_D_X > 55.4 && MOCK_D_X < 55.6), "X correto");
    verificar((MOCK_D_Y > 66.5 && MOCK_D_Y < 66.7), "Y correto");
    verificar(strcmp(MOCK_D_SFX, "sulfixo-teste") == 0, "Sufixo correto");

    remove(NOME);
}

void teste_comando_pintura() {
    printf("\n--- Teste 3: Comando 'p' (Pintura) ---\n");
    resetar_mocks();

    const char* NOME = "temp_qry_3.qry";
    // Comando: p [x] [y] [cor] [sufixo]
    criar_arquivo_teste(NOME, "p 10 10 #FF00FF -\n");

    Arquivo qry = abrirQry((char*)NOME);
    LerComandosExecutar(NULL, stdout, qry, NULL, NULL, 'q', 10, "out");
    fclose(qry);

    verificar(MOCK_PINTURA_CHAMADO == 1, "Funcao Pintura foi chamada");
    verificar(strcmp(MOCK_P_COR, "#FF00FF") == 0, "Cor lida corretamente");

    remove(NOME);
}

void teste_comando_clone() {
    printf("\n--- Teste 4: Comando 'cln' (Clone) ---\n");
    resetar_mocks();

    const char* NOME = "temp_qry_4.qry";
    // Comando: cln [x] [y] [dx] [dy] [sufixo]
    criar_arquivo_teste(NOME, "cln 0 0 100.5 200.5 -\n");

    Arquivo qry = abrirQry((char*)NOME);
    LerComandosExecutar(NULL, stdout, qry, NULL, NULL, 'q', 10, "out");
    fclose(qry);

    verificar(MOCK_CLONE_CHAMADO == 1, "Funcao Clone foi chamada");
    printf("   DX: %.2f | DY: %.2f\n", MOCK_C_DX, MOCK_C_DY);
    verificar(MOCK_C_DX > 100.4, "DX correto");
    verificar(MOCK_C_DY > 200.4, "DY correto");

    remove(NOME);
}

void teste_arquivo_multilinhas() {
    printf("\n--- Teste 5: Multiplas Linhas e Vazios ---\n");
    resetar_mocks();

    const char* NOME = "temp_qry_5.qry";
    // Testa parser com linhas vazias e múltiplos comandos
    criar_arquivo_teste(NOME,
        "\n"
        "a 1 2 h\n"
        "\n"
        "d 5 5 -\n"
    );

    Arquivo qry = abrirQry((char*)NOME);
    LerComandosExecutar(NULL, stdout, qry, NULL, NULL, 'q', 10, "out");
    fclose(qry);

    verificar(MOCK_ANTEPARO_CHAMADO == 1, "Leu o primeiro comando (a)");
    verificar(MOCK_DESTRUICAO_CHAMADO == 1, "Leu o segundo comando (d)");

    remove(NOME);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO QRY (PARSER)\n");
    printf("==========================================\n");

    teste_comando_anteparo();
    teste_comando_destruicao();
    teste_comando_pintura();
    teste_comando_clone();
    teste_arquivo_multilinhas();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}