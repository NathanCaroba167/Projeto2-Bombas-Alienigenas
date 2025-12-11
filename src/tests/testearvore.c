//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../arvore.h"
#include "../segmento.h"

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

int comparador_por_id(Segmento a, Segmento b) {
    int idA = getIDSegmento(a);
    int idB = getIDSegmento(b);
    return idA - idB;
}


void teste_criacao() {
    printf("\n--- Teste 1: Criacao e Estado Inicial ---\n");

    Arvore arv = CriarArvore(comparador_por_id);

    verificar(arv != NULL, "A arvore foi alocada na memoria");
    verificar(arvorevazia(arv) == true, "A arvore recem-criada esta vazia");

    liberarArvore(arv);
}

void teste_insercao_e_busca() {
    printf("\n--- Teste 2: Insercao e Busca ---\n");

    Arvore arv = CriarArvore(comparador_por_id);

    Segmento s10 = CriarSegmento(10, 0,0,0,0, "red", ANTEPARO);
    Segmento s5  = CriarSegmento(5,  0,0,0,0, "red", ANTEPARO);
    Segmento s15 = CriarSegmento(15, 0,0,0,0, "red", ANTEPARO);

    inserirArvore(arv, s10);
    verificar(arvorevazia(arv) == false, "Arvore nao esta mais vazia apos insercao");

    inserirArvore(arv, s5);
    inserirArvore(arv, s15);

    Segmento busca1 = buscarArvore(arv, s5);
    verificar(busca1 != NULL, "Busca pelo ID 5 retornou algo");
    if (busca1 != NULL) {
        verificar(getIDSegmento(busca1) == 5, "O elemento retornado tem ID 5");
    }

    Segmento busca2 = buscarArvore(arv, s15);
    verificar(busca2 != NULL, "Busca pelo ID 15 retornou algo");

    Segmento s99 = CriarSegmento(99, 0,0,0,0, "red", ANTEPARO);
    Segmento busca3 = buscarArvore(arv, s99);
    verificar(busca3 == NULL, "Busca pelo ID 99 retornou NULL (correto)");

    liberarArvore(arv);
    eliminarSegmento(s10); eliminarSegmento(s5); eliminarSegmento(s15); eliminarSegmento(s99);
}

void teste_mais_esquerda() {
    printf("\n--- Teste 3: Get Mais Esquerda (Minimo) ---\n");

    Arvore arv = CriarArvore(comparador_por_id);

    Segmento s20 = CriarSegmento(20, 0,0,0,0, "b", ANTEPARO);
    Segmento s10 = CriarSegmento(10, 0,0,0,0, "b", ANTEPARO);
    Segmento s5  = CriarSegmento(5,  0,0,0,0, "b", ANTEPARO);
    Segmento s30 = CriarSegmento(30, 0,0,0,0, "b", ANTEPARO);

    inserirArvore(arv, s20);
    inserirArvore(arv, s30);
    inserirArvore(arv, s10);
    inserirArvore(arv, s5);

    Segmento menor = getMaisEsquerdaDado(arv);

    verificar(menor != NULL, "Retornou um segmento");
    if (menor != NULL) {
        printf("   Valor esperado: 5. Valor recebido: %d.\n", getIDSegmento(menor));
        verificar(getIDSegmento(menor) == 5, "O segmento mais a esquerda e o 5");
    }

    liberarArvore(arv);
    eliminarSegmento(s20); eliminarSegmento(s10); eliminarSegmento(s5); eliminarSegmento(s30);
}

void teste_remocao() {
    printf("\n--- Teste 4: Remocao ---\n");

    Arvore arv = CriarArvore(comparador_por_id);

    Segmento s20 = CriarSegmento(20, 0,0,0,0, "b", ANTEPARO);
    Segmento s10 = CriarSegmento(10, 0,0,0,0, "b", ANTEPARO);

    inserirArvore(arv, s20);
    inserirArvore(arv, s10);

    Segmento removido = removerArvore(arv, s10);
    verificar(removido != NULL, "Removeu o segmento 10");
    verificar(buscarArvore(arv, s10) == NULL, "O segmento 10 nao esta mais na arvore");

    removido = removerArvore(arv, s20);
    verificar(removido != NULL, "Removeu o segmento 20");
    verificar(arvorevazia(arv) == true, "Arvore ficou vazia apos remover tudo");

    liberarArvore(arv);
    eliminarSegmento(s20); eliminarSegmento(s10);
}

int main() {
    printf("==========================================\n");
    printf("   INICIANDO TESTES DO MODULO ARVORE\n");
    printf("==========================================\n");

    teste_criacao();
    teste_insercao_e_busca();
    teste_mais_esquerda();
    teste_remocao();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}