//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../txt.h"
#include "../forma.h"
#include "../circulo.h"
#include "../retangulo.h"
#include "../linha.h"
#include "../texto.h"
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

char* ler_arquivo_inteiro(const char* nome) {
    FILE* f = fopen(nome, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*) malloc(tamanho + 1);
    if (buffer) {
        fread(buffer, 1, tamanho, f);
        buffer[tamanho] = '\0';
    }
    fclose(f);
    return buffer;
}

// --- TESTES ---

void teste_escrita_relatorio() {
    printf("\n--- Teste 1: Escrita de Relatorio de Formas ---\n");

    const char* NOME_ARQ = "teste_relatorio.txt";

    // 1. Abrir Arquivo
    Arquivo arq = abrirTXT((char*)NOME_ARQ);
    verificar(arq != NULL, "Arquivo aberto com sucesso");

    // 2. Criar Formas e Reportar

    // Circulo
    Circulo c = CriarCirculo(10, 5.0, 5.0, 2.0, "red", "blue");
    Pacote p1 = CriarPacote(c, CIRCULO);
    reportarForma(arq, p1);

    // Retangulo
    Retangulo r = CriarRetangulo(20, 10.0, 10.0, 50.0, 30.0, "black", "white");
    Pacote p2 = CriarPacote(r, RETANGULO);
    reportarForma(arq, p2);

    // Linha
    Linha l = CriarLinha(30, 0.0, 0.0, 100.0, 100.0, "green");
    Pacote p3 = CriarPacote(l, LINHA);
    reportarForma(arq, p3);

    // Texto
    Texto t = CriarTexto(40, 200.0, 200.0, "yellow", "purple", 'i', "OlaMundo");
    Pacote p4 = CriarPacote(t, TEXTO);
    reportarForma(arq, p4);

    // Segmento
    Segmento s = CriarSegmento(50, 1.0, 1.0, 2.0, 2.0, "orange", ANTEPARO);
    Pacote p5 = CriarPacote(s, SEGMENTO);
    reportarForma(arq, p5);

    fclose(arq);

    char* conteudo = ler_arquivo_inteiro(NOME_ARQ);
    verificar(conteudo != NULL, "Conteudo lido de volta");

    // Verifica se as strings chaves estão presentes

    // Verifica Círculo
    verificar(strstr(conteudo, "Círculo - (ID: 10)") != NULL, "Encontrou ID do Circulo");
    verificar(strstr(conteudo, "Raio: 2.000000") != NULL, "Encontrou Raio do Circulo");

    // Verifica Retângulo
    verificar(strstr(conteudo, "Retângulo - (ID: 20)") != NULL, "Encontrou ID do Retangulo");
    verificar(strstr(conteudo, "Largura: 50.000000") != NULL, "Encontrou Largura do Retangulo");

    // Verifica Linha
    verificar(strstr(conteudo, "Linha - (ID: 30)") != NULL, "Encontrou ID da Linha");
    verificar(strstr(conteudo, "Cor: green") != NULL, "Encontrou Cor da Linha");

    // Verifica Texto
    verificar(strstr(conteudo, "Texto - (ID: 40)") != NULL, "Encontrou ID do Texto");
    verificar(strstr(conteudo, "Conteúdo: OlaMundo") != NULL, "Encontrou Conteudo do Texto");

    // Verifica Segmento
    verificar(strstr(conteudo, "Segmento - (ID: 50)") != NULL, "Encontrou ID do Segmento");

    // Limpeza
    free(conteudo);

    eliminarCirculo(c); free(p1);
    eliminarRetangulo(r); free(p2);
    eliminarLinha(l); free(p3);
    eliminarTexto(t); free(p4);
    eliminarSegmento(s); free(p5);

    // Remove o arquivo temporário
    remove(NOME_ARQ);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO TXT (RELATORIO)\n");
    printf("==========================================\n");

    teste_escrita_relatorio();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}