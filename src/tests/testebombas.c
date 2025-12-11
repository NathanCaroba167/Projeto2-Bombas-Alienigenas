//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../poligono.h"
#include "../bombas.h"
#include "../lista.h"
#include "../forma.h"
#include "../segmento.h"
#include "../retangulo.h"

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

Poligono calcularRegiaoVisibilidade(Lista a, double x, double y, char ord, int lim) {
    return (Poligono) malloc(1);
}

void eliminarPoligono(Poligono p) {
    free(p);
}

int verificarSobreposicao(Poligono poli, Pacote p) {
    return 1;
}

Arquivo abrirSVG(char* f) { return stdout; }
void inicializarSVG(Arquivo f) {}
void desenharPoligonoSVG(Arquivo f, Poligono p) {}
void desenharBombaSVG(Arquivo f, double x, double y) {}
void desenharFormasDaLista(Arquivo f, Lista l, void* estilo) {}
void fecharSVG(Arquivo f) {}
void reportarForma(Arquivo f, Pacote p) {}

void converteRetanguloSegmento(Arquivo txt, void* r, Lista anteparos) {

    Segmento s = CriarSegmento(999, 0,0,10,10, "black", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s, SEGMENTO));
}

void converteCirculoSegmento(Arquivo a, void* f, Lista l, char d) {}
void converteLinhaSegmento(Arquivo a, void* f, Lista l) {}
void converteTextoSegmento(Arquivo a, void* f, Lista l) {}

void teste_destruicao() {
    printf("\n--- Teste: Destruicao ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    Retangulo r = CriarRetangulo(1, 10, 10, 20, 20, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    verificar(getTamanhoLista(formas) == 1, "Lista de formas comeca com 1 item");

    Destruicao(stdout, stdout, formas, anteparos, 0, 0, "-", ".", 'q', 10);

    verificar(getTamanhoLista(formas) == 0, "Lista de formas deve estar vazia apos destruicao");

    liberarLista(formas);
    liberarLista(anteparos);
}

void teste_pintura() {
    printf("\n--- Teste: Pintura ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    Retangulo r = CriarRetangulo(1, 10, 10, 20, 20, "red", "red");
    Pacote p = CriarPacote(r, RETANGULO);
    inserirListaFim(formas, p);

    Pintura(stdout, stdout, formas, anteparos, 0, 0, "blue", "-", ".", 'q', 10);

    char* novaCor = getCorBRetangulo(r);
    verificar(strcmp(novaCor, "blue") == 0, "A cor do retangulo mudou para blue");

    liberarLista(formas);
    liberarLista(anteparos);
}

void teste_clone() {
    printf("\n--- Teste: Clone ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    Retangulo r = CriarRetangulo(1, 10, 10, 20, 20, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    Segmento s = CriarSegmento(2, 50, 50, 60, 60, "black", ANTEPARO);
    inserirListaFim(anteparos, CriarPacote(s, SEGMENTO));

    Clone(stdout, stdout, formas, anteparos, 0, 0, 100, 100, "-", ".", 'q', 10);

    int qtdFormas = getTamanhoLista(formas);
    int qtdAnteparos = getTamanhoLista(anteparos);

    printf("   Formas: %d (Esperado 2). Anteparos: %d (Esperado 2).\n", qtdFormas, qtdAnteparos);

    verificar(qtdFormas == 2, "A lista de formas dobrou de tamanho");
    verificar(qtdAnteparos == 2, "A lista de anteparos dobrou de tamanho");

    liberarLista(formas);
    liberarLista(anteparos);
}

void teste_anteparo_universo() {
    printf("\n--- Teste: Anteparo (Universo) ---\n");

    Lista formas = iniciarLista();
    Lista anteparos = iniciarLista();

    Retangulo r = CriarRetangulo(1, 1000, 1000, 10, 10, "red", "red");
    inserirListaFim(formas, CriarPacote(r, RETANGULO));

    Anteparo(stdout, formas, anteparos, 1, 1, 'v');

    int qtd = getTamanhoLista(anteparos);
    printf("   Qtd Anteparos: %d\n", qtd);
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