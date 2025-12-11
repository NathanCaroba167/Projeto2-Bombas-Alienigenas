//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// --- SUA FUNÇÃO (Copiada exatamente como você mandou) ---
char* getNomeBase(char* nomeArq) {
    // Busca a última barra ('/') para ignorar o caminho do diretório
    char* barra = strrchr(nomeArq, '/');
    char* Nome = (barra != NULL) ? barra + 1 : nomeArq;

    // Busca o último ponto ('.') para encontrar a extensão
    char* ponto = strrchr(Nome, '.');
    int tamanhoBase;

    if (ponto == NULL) {
        // Não há extensão, o nome base é o nome inteiro
        tamanhoBase = strlen(Nome);
    }else {
        // O tamanho base é a distância entre o ínicio do Nome e o ponto
        tamanhoBase = ponto - Nome;
    }

    // Aloca memória para a string resultante
    char* nomeBase = (char*) malloc(tamanhoBase + 1);
    if (nomeBase == NULL) {
        printf("Erro ao alocar memória de nomeBase!\n");
        perror("Motivo do erro");
        exit(1);
    }

    // Copia a substring e adiciona o terminador nulo
    strncpy(nomeBase, Nome, tamanhoBase);
    nomeBase[tamanhoBase] = '\0';

    return nomeBase;
}

// --- FUNÇÃO AUXILIAR DE TESTE ---
void testar_caso(const char* entrada, const char* esperado) {
    printf("Testando: [%s] ... ", entrada);

    // Convertemos const char* para char* para passar na sua função
    // (apenas para evitar warnings, já que sua função não altera a entrada)
    char* buffer = strdup(entrada);

    char* resultado = getNomeBase(buffer);

    if (strcmp(resultado, esperado) == 0) {
        printf("\033[0;32m[OK]\033[0m -> %s\n", resultado);
    } else {
        printf("\033[0;31m[FALHA]\033[0m\n");
        printf("   Esperado: '%s'\n", esperado);
        printf("   Recebido: '%s'\n", resultado);
        exit(1); // Para o teste se falhar
    }

    free(resultado); // Limpa o malloc feito dentro de getNomeBase
    free(buffer);    // Limpa o strdup
}

// --- MAIN DO TESTE ---
int main() {
    printf("=== INICIANDO TESTES UNITARIOS: getNomeBase ===\n\n");

    // CASO 1: Arquivo simples com extensão
    testar_caso("arquivo.geo", "arquivo");

    // CASO 2: Caminho relativo com diretórios
    testar_caso("entradas/casos/teste01.qry", "teste01");

    // CASO 3: Caminho absoluto (Linux)
    testar_caso("/usr/home/aluno/projeto/diagrama.svg", "diagrama");

    // CASO 4: Arquivo sem extensão
    testar_caso("makefile", "makefile");

    // CASO 5: Arquivo sem extensão dentro de diretório
    testar_caso("bin/executavel", "executavel");

    // CASO 6: Múltiplos pontos (deve remover apenas a última extensão)
    // Ex: arquivo.tar.gz -> arquivo.tar (comportamento padrão do strrchr)
    testar_caso("meu_backup.tar.gz", "meu_backup.tar");

    // CASO 7: Ponto no nome do diretório (pegadinha)
    // O código deve ignorar o ponto do diretório e pegar o nome do arquivo
    testar_caso("versao2.0/config.txt", "config");

    printf("\n\033[0;32mTODOS OS TESTES PASSARAM COM SUCESSO!\033[0m\n");
    return 0;
}