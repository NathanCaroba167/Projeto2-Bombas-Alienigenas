//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../bombas.h"
#include "../lista.h"
#include "../forma.h"
#include "../segmento.h"
#include "../retangulo.h"
#include "../poligono.h"


// --- FUNÇÃO AUXILIAR ---
void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

// ============================================================================
// MOCKS (Simulações de funções externas para isolar o teste)
// ============================================================================

// Simula Visibilidade (Retorna ponteiro válido para não crashar)
Poligono calcularRegiaoVisibilidade(Lista a, double x, double y, char ord, int lim) {
    // Aloca 1 byte só para o ponteiro não ser NULL
    return (Poligono) malloc(1);
}

// Simula liberação do polígono (mock)
void eliminarPoligono(Poligono p) {
    free(p);
}

// Simula Sobreposição: Retorna SEMPRE 1 (Verdadeiro)
// Isso força o teste a entrar nos IFs de destruição/pintura/clone
bool verificarSobreposicao(Poligono poli, Pacote p) {
    return true;
}

// Mocks de SVG e TXT (Não fazem nada, só para compilar)
Arquivo abrirSVG(char* f) { return stdout; }
void inicializarSVG(Arquivo f) {}
void desenharPoligonoSVG(Arquivo f, Poligono p) {}
void desenharBombaSVG(Arquivo f, double x, double y) {}
void desenharFormasDaLista(Arquivo f, Lista l, void* estilo) {}
void fecharSVG(Arquivo f) {}
void reportarForma(Arquivo f, Pacote p) {}

// Mock do Segmentador (Retângulo)
// Adiciona um segmento fake na lista para simular que a conversão ocorreu
void converteRetanguloSegmento(Arquivo txt, void* r, Lista anteparos) {
    Segmento s = CriarSegmento(999, 0,0,10,10, "black", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s, SEGMENTO));
}

// Mocks vazios para outros tipos
void converteCirculoSegmento(Arquivo a, void* f, Lista l, char d) {}
void converteLinhaSegmento(Arquivo a, void* f, Lista l) {}
void converteTextoSegmento(Arquivo a, void* f, Lista l) {}

// ============================================================================
// CASOS DE TESTE
// ============================================================================

void teste_destruicao() {
    printf("\n--- Teste: Destruicao ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    // Cria forma e insere
    Retangulo r = CriarRetangulo(1, 10, 10, 20, 20, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    verificar(getTamanhoLista(formas) == 1, "Inicio: 1 forma na lista");

    // Executa destruição (Mock de sobreposição retorna true)
    Destruicao(stdout, stdout, formas, anteparos, 0, 0, "-", ".", 'q', 10);

    verificar(getTamanhoLista(formas) == 0, "Fim: Lista vazia (forma destruida)");

    liberarLista(formas);
    liberarLista(anteparos);
}

void teste_pintura() {
    printf("\n--- Teste: Pintura ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    Retangulo r = CriarRetangulo(1, 10, 10, 20, 20, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    // Pinta de AZUL
    Pintura(stdout, stdout, formas, anteparos, 0, 0, "blue", "-", ".", 'q', 10);

    char* novaCor = getCorBRetangulo(r);
    verificar(strcmp(novaCor, "blue") == 0, "Cor alterada para blue");

    liberarLista(formas);
    liberarLista(anteparos);
}

void teste_clone() {
    printf("\n--- Teste: Clone ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    // 1 Forma
    Retangulo r = CriarRetangulo(1, 10, 10, 20, 20, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    // 1 Anteparo
    Segmento s = CriarSegmento(2, 50, 50, 60, 60, "black", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s, SEGMENTO));

    // Clone com deslocamento
    Clone(stdout, stdout, formas, anteparos, 0, 0, 100, 100, "-", ".", 'q', 10);

    int qtdFormas = getTamanhoLista(formas);
    int qtdAnteparos = getTamanhoLista(anteparos);

    printf("   Formas: %d (Esp: 2). Anteparos: %d (Esp: 2).\n", qtdFormas, qtdAnteparos);

    // Como o mock retorna TRUE para tudo, deve clonar a forma E o anteparo
    verificar(qtdFormas == 2, "Lista formas dobrou (original + clone)");
    verificar(qtdAnteparos == 2, "Lista anteparos dobrou (original + clone)");

    liberarLista(formas);
    liberarLista(anteparos);
}

void teste_anteparo_universo() {
    printf("\n--- Teste: Anteparo (Universo) ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    // Forma longe para expandir o universo
    Retangulo r = CriarRetangulo(1, 1000, 1000, 10, 10, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    // Chama Anteparo (Mock converteRetangulo vai rodar)
    Anteparo(stdout, formas, anteparos, 1, 1, 'v');

    int qtd = getTamanhoLista(anteparos);
    printf("   Qtd Anteparos: %d\n", qtd);

    // Esperado: 1 segmento da conversão (mock) + 4 segmentos da borda do universo
    verificar(qtd >= 5, "Gerou conversao + bordas do universo");

    liberarLista(formas);
    liberarLista(anteparos);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO BOMBAS\n");
    printf("==========================================\n");

    teste_destruicao();
    teste_pintura();
    teste_clone();
    teste_anteparo_universo();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}