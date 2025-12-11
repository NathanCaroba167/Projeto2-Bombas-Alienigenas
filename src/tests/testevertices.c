//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../vertices.h"
#include "../segmento.h"
#include "../lista.h"
#include "../forma.h"

#define M_PI 3.14159265358979323846

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

// --- TESTES ---

void teste_criacao_simples() {
    printf("\n--- Teste 1: Criacao e Getters de 1 Vertice ---\n");

    // Cria um segmento fictício para associar
    Segmento seg = CriarSegmento(1, 0,0,10,10, "black", ANTEPARO);

    // Cria vertice manualmente
    Vertice v = CriarVertice(10.5, 20.5, 1.57, 50.0, INICIO, seg);

    verificar(v != NULL, "Vertice alocado");
    verificar(sao_iguais(getXVertice(v), 10.5), "X correto");
    verificar(sao_iguais(getYVertice(v), 20.5), "Y correto");
    verificar(sao_iguais(getAnguloVertice(v), 1.57), "Angulo correto");
    verificar(sao_iguais(getDistanciaVertice(v), 50.0), "Distancia correta");
    verificar(getTipoVertice(v) == INICIO, "Tipo INICIO correto");
    verificar(getSegmentoVertice(v) == seg, "Ponteiro para segmento original mantido");

    eliminarVertice(v);
    eliminarSegmento(seg);
}

void teste_vetor_vertices_logica() {
    printf("\n--- Teste 2: Criacao do Vetor (Logica Angular) ---\n");

    // Cenário:
    // Bomba em (0,0).
    // Segmento 1: (10, 0) até (10, 10).
    //    (10,0) ângulo é 0.
    //    (10,10) ângulo é 45 graus (0.78 rad).
    //    Esperado: (10,0) é INICIO, (10,10) é FIM.

    Lista anteparos = iniciarLista();
    Segmento s1 = CriarSegmento(10, 10.0, 0.0, 10.0, 10.0, "red", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s1, SEGMENTO));

    int qtdVertices = 0;
    double bombaX = 0.0;
    double bombaY = 0.0;

    // A função retorna um Vetor (que é void* ou array de Vertice*)
    // Convertemos para (Vertice*) para acessar como array
    Vertice* vetor = (Vertice*) CriarVetorVertices(anteparos, bombaX, bombaY, &qtdVertices);

    verificar(qtdVertices == 2, "Gerou 2 vertices para 1 segmento");
    verificar(vetor != NULL, "Vetor alocado");

    // Analisando Vertice 0 (O código insere [i] e [i+1])
    Vertice v0 = vetor[0];
    Vertice v1 = vetor[1];

    double ang0 = getAnguloVertice(v0);
    double ang1 = getAnguloVertice(v1);

    printf("   V0: Angulo %.2f rad (Tipo %d)\n", ang0, getTipoVertice(v0));
    printf("   V1: Angulo %.2f rad (Tipo %d)\n", ang1, getTipoVertice(v1));

    // Verifica logica de ordenação (Menor ângulo vira INICIO)
    // 0.0 < 0.78

    // V0 deve ser o ponto (10, 0) -> Angulo 0 -> INICIO
    verificar(sao_iguais(ang0, 0.0), "V0 tem angulo 0");
    verificar(getTipoVertice(v0) == INICIO, "V0 e INICIO");

    // V1 deve ser o ponto (10, 10) -> Angulo ~0.78 -> FIM
    verificar(ang1 > 0.1, "V1 tem angulo > 0");
    verificar(getTipoVertice(v1) == FIM, "V1 e FIM");

    // Limpeza
    for(int i=0; i<qtdVertices; i++) {
        eliminarVertice(vetor[i]);
    }
    free(vetor);

    liberarLista(anteparos); // Libera o pacote e o segmento
}

void teste_vetor_vertices_angulo_negativo() {
    printf("\n--- Teste 3: Normalizacao de Angulos (Q4) ---\n");

    // Cenário: Segmento no 4º quadrante.
    // P1 (10, -10) -> atan2 = -0.78 rad (-45 graus).
    // P2 (20, -10).
    // O sistema deve converter -0.78 para 2PI - 0.78 (~5.5 rad).

    Lista anteparos = iniciarLista();
    Segmento s1 = CriarSegmento(20, 10.0, -10.0, 20.0, -10.0, "blue", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s1, SEGMENTO));

    int qtd = 0;
    Vertice* vetor = (Vertice*) CriarVetorVertices(anteparos, 0.0, 0.0, &qtd);

    Vertice vA = vetor[0];
    double angA = getAnguloVertice(vA);

    printf("   Angulo calculado: %.2f rad\n", angA);

    verificar(angA > 0, "Angulo negativo foi normalizado para positivo");
    verificar(angA > 5.0, "Angulo esta no final do ciclo (perto de 6.28)");

    // Limpeza
    for(int i=0; i<qtd; i++) eliminarVertice(vetor[i]);
    free(vetor);
    liberarLista(anteparos);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO VERTICES\n");
    printf("==========================================\n");

    teste_criacao_simples();
    teste_vetor_vertices_logica();
    teste_vetor_vertices_angulo_negativo();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}