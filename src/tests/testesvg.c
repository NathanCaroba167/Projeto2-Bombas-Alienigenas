//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../svg.h"
#include "../lista.h"
#include "../forma.h"
#include "../circulo.h"
#include "../retangulo.h"
#include "../linha.h"
#include "../texto.h"
#include "../segmento.h"
#include "../poligono.h"

// --- AUXILIARES ---

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

// Lê arquivo
char* ler_arquivo(const char* nome) {
    FILE* f = fopen(nome, "r");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buf = malloc(tam + 1);
    if(buf) {
        fread(buf, 1, tam, f);
        buf[tam] = '\0';
    }
    fclose(f);
    return buf;
}

// --- TESTES ---

void teste_geracao_svg_basico() {
    printf("\n--- Teste 1: Tags Basicas e Estrutura ---\n");

    const char* NOME_ARQ = "teste_saida.svg";
    Arquivo svg = abrirSVG((char*)NOME_ARQ);
    inicializarSVG(svg);

    // Testa: Círculo e Retângulo
    Circulo c = CriarCirculo(1, 10.5, 20.5, 5.0, "red", "blue");
    desenharCirculoSVG(svg, c);

    Retangulo r = CriarRetangulo(2, 100, 100, 50, 30, "black", "white");
    desenharRetanguloSVG(svg, r);

    fecharSVG(svg);
    fclose(svg);

    // Verificação
    char* conteudo = ler_arquivo(NOME_ARQ);
    verificar(conteudo != NULL, "Arquivo criado e lido");

    // Cabeçalho
    verificar(strstr(conteudo, "<svg") != NULL, "Tag <svg> presente");
    verificar(strstr(conteudo, "<g>") != NULL, "Tag <g> presente");

    // Circulo
    verificar(strstr(conteudo, "<circle") != NULL, "Tag <circle> presente");
    verificar(strstr(conteudo, "cx=\"10.500000\"") != NULL, "CX do circulo correto");
    verificar(strstr(conteudo, "fill=\"blue\"") != NULL, "Cor fill do circulo correta");

    // Retangulo
    verificar(strstr(conteudo, "<rect") != NULL, "Tag <rect> presente");
    verificar(strstr(conteudo, "width=\"50.000000\"") != NULL, "Width do retangulo correto");

    // Rodapé
    verificar(strstr(conteudo, "</svg>") != NULL, "Fechamento </svg> presente");

    free(conteudo);
    eliminarCirculo(c);
    eliminarRetangulo(r);
    remove(NOME_ARQ);
}

void teste_texto_ancora() {
    printf("\n--- Teste 2: Texto e Ancoras ---\n");

    const char* NOME_ARQ = "teste_texto.svg";
    Arquivo svg = abrirSVG((char*)NOME_ARQ);
    inicializarSVG(svg);

    Estilo e = CriarEstilo("Arial", "bold", "12px");

    // Texto ancora Inicio ('i')
    Texto t1 = CriarTexto(1, 0, 0, "black", "black", 'i', "Inicio");
    desenharTextoSVG(svg, t1, e);

    // Texto ancora Meio ('m')
    Texto t2 = CriarTexto(2, 0, 0, "black", "black", 'm', "Meio");
    desenharTextoSVG(svg, t2, e);

    fecharSVG(svg);
    fclose(svg);

    char* conteudo = ler_arquivo(NOME_ARQ);

    verificar(strstr(conteudo, "text-anchor=\"start\"") != NULL, "Ancora 'i' gerou start");
    verificar(strstr(conteudo, "text-anchor=\"middle\"") != NULL, "Ancora 'm' gerou middle");
    verificar(strstr(conteudo, "font-family=\"Arial\"") != NULL, "Fonte Arial presente");

    free(conteudo);
    eliminarTexto(t1); eliminarTexto(t2); eliminarEstilo(e);
    remove(NOME_ARQ);
}

void teste_poligono() {
    printf("\n--- Teste 3: Poligono (Points) ---\n");

    const char* NOME_ARQ = "teste_poli.svg";
    Arquivo svg = abrirSVG((char*)NOME_ARQ);
    inicializarSVG(svg);

    Poligono p = CriarPoligono();
    adicionarPontoAoPoligono(p, CriarPonto(10, 10));
    adicionarPontoAoPoligono(p, CriarPonto(20, 20));

    desenharPoligonoSVG(svg, p);

    fecharSVG(svg);
    fclose(svg);

    char* conteudo = ler_arquivo(NOME_ARQ);

    verificar(strstr(conteudo, "<polygon") != NULL, "Tag <polygon> presente");
    // Verifica se os pontos foram escritos no formato "x,y "
    verificar(strstr(conteudo, "10.000000,10.000000") != NULL, "Ponto 1 correto");
    verificar(strstr(conteudo, "20.000000,20.000000") != NULL, "Ponto 2 correto");

    free(conteudo);
    eliminarPoligono(p);
    remove(NOME_ARQ);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO SVG\n");
    printf("==========================================\n");

    teste_geracao_svg_basico();
    teste_texto_ancora();
    teste_poligono();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}