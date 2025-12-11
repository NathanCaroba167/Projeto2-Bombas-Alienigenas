//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../visibilidade.h"
#include "../segmento.h"
#include "../lista.h"
#include "../forma.h"
#include "../poligono.h"
#include "../vertices.h"
#include "../arvore.h"

int calcularIntersecaoRaio(Segmento s, double theta, double* xSaida, double* ySaida);

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
    return fabs(a - b) < 1e-4;
}

// Configura a bomba chamando a funcao principal com lista vazia
// Isso atualiza as variaveis static BOMBA_X e BOMBA_Y la dentro
void set_bomba(double x, double y) {
    Lista l = iniciarLista();
    // A funcao vai rodar, nao achar nada e retornar um poligono vazio.
    // O importante e que ela seta BOMBA_X=x e BOMBA_Y=y
    Poligono p = calcularRegiaoVisibilidade(l, x, y, 'q', 10);
    // Limpeza
    eliminarPoligono(p);
    liberarLista(l);
}

// --- TESTES ---

void teste_interseccao_raio() {
    printf("\n--- Teste 1: Interseccao Raio-Segmento ---\n");

    // Bomba em (0,0)
    set_bomba(0.0, 0.0);

    // Parede vertical em X=10, de Y=-10 a Y=10
    Segmento s = CriarSegmento(1, 10.0, -10.0, 10.0, 10.0, "black", ANTEPARO);

    double xOut, yOut;

    // 1. Raio Horizontal (0 graus/rad) -> Deve bater em (10,0)
    int acertou = calcularInterseccaoRaio(s, 0.0, &xOut, &yOut);
    verificar(acertou == 1, "Raio 0 graus acertou parede");
    verificar(sao_iguais(xOut, 10.0) && sao_iguais(yOut, 0.0), "Ponto (10,0) correto");

    // 2. Raio 45 graus (0.785 rad) -> Não deve bater (passa por cima)
    // Parede vai ate Y=10. Em X=10, Y seria 10.
    // Vamos testar um angulo mais inclinado que passa longe.
    // Angulo 1.0 rad (~57 graus). Em X=10, Y=15. Parede acaba em 10.
    acertou = calcularInterseccaoRaio(s, 1.0, &xOut, &yOut);
    verificar(acertou == 0, "Raio inclinado errou parede (passou por cima)");

    // 3. Raio para tras (PI rad) -> Nao deve bater
    acertou = calcularInterseccaoRaio(s, 3.14159, &xOut, &yOut);
    verificar(acertou == 0, "Raio para tras ignorou parede na frente");

    eliminarSegmento(s);
}

void teste_comparador_arvore() {
    printf("\n--- Teste 2: Comparador da Arvore (Quem esta na frente?) ---\n");

    set_bomba(0.0, 0.0);

    // Parede A (Perto): X=5
    Segmento A = CriarSegmento(1, 5.0, -10.0, 5.0, 10.0, "red", ANTEPARO);

    // Parede B (Longe): X=10
    Segmento B = CriarSegmento(2, 10.0, -10.0, 10.0, 10.0, "blue", ANTEPARO);

    // A bomba olha para a direita.
    // A está na frente de B. A deve ser "menor" (vem antes na arvore).
    int res = comparaSegmentosArvore(A, B);
    verificar(res == -1, "A < B (A bloqueia B)");

    res = comparaSegmentosArvore(B, A);
    verificar(res == 1, "B > A (B esta atras de A)");

    // Teste de Colinearidade (Compartilham inicio)
    // C começa onde A termina: (5, 10) ate (5, 20)

    eliminarSegmento(A);
    eliminarSegmento(B);
}

void teste_corte_inicio() {
    printf("\n--- Teste 3: Corte de Segmento no Inicio (Angulo 0) ---\n");

    set_bomba(0.0, 0.0);

    // Parede que cruza o eixo X positivo (onde o ângulo é 0)
    // Vai de (10, -5) até (10, 5).
    Lista anteparos = iniciarLista();
    Segmento s = CriarSegmento(1, 10.0, -5.0, 10.0, 5.0, "green", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s, SEGMENTO));

    tratarSegmentosQueCruzamInicio(anteparos, 0.0, 0.0);

    // O segmento original deve ter sido removido e substitudo por 2 novos.
    // Total esperado: 2 segmentos.
    int qtd = getTamanhoLista(anteparos);
    printf("   Quantidade apos corte: %d\n", qtd);
    verificar(qtd == 2, "Segmento foi dividido em 2");

    // Verifica os pedaços
    // Pedaco 1: (10, -5) ate (10, 0)
    // Pedaco 2: (10, 0) ate (10, 5)

    pont p = getPrimeiroElementoLista(anteparos);
    Segmento s1 = getDadosForma(getPacoteElementoLista(p));

    p = getProximoElementoLista(p);
    Segmento s2 = getDadosForma(getPacoteElementoLista(p));

    // Um deles deve terminar em Y=0 e o outro começar em Y=0
    int achouZero = 0;
    if (sao_iguais(getY2Segmento(s1), 0.0) || sao_iguais(getY1Segmento(s1), 0.0)) achouZero++;
    if (sao_iguais(getY2Segmento(s2), 0.0) || sao_iguais(getY1Segmento(s2), 0.0)) achouZero++;

    verificar(achouZero == 2, "Ambos os segmentos tocam Y=0 (Ponto de Corte)");

    liberarLista(anteparos); // Libera tudo
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO VISIBILIDADE\n");
    printf("==========================================\n");

    teste_interseccao_raio();
    teste_comparador_arvore();
    teste_corte_inicio();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}