//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../poligono.h"
#include "../lista.h"
#include "../forma.h"
#include "../circulo.h"
#include "../retangulo.h"
#include "../linha.h"
#include "../texto.h"
#include "../segmento.h"

// --- AUXILIARES ---

void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}

// Cria um polígono quadrado (0,0) -> (100,0) -> (100,100) -> (0,100)
Poligono criar_poligono_quadrado() {
    Poligono p = CriarPoligono();
    adicionarPontoAoPoligono(p, CriarPonto(0, 0));
    adicionarPontoAoPoligono(p, CriarPonto(100, 0));
    adicionarPontoAoPoligono(p, CriarPonto(100, 100));
    adicionarPontoAoPoligono(p, CriarPonto(0, 100));
    return p;
}

// --- TESTES ---

void teste_ray_casting_basico() {
    printf("\n--- Teste 1: Ponto Dentro Poligono (Ray Casting) ---\n");

    Poligono p = criar_poligono_quadrado();

    // 1. Ponto DENTRO (50, 50)
    verificar(pontoDentroPoligono(p, 50, 50) == true, "Ponto (50,50) esta dentro");

    // 2. Ponto FORA (150, 50)
    verificar(pontoDentroPoligono(p, 150, 50) == false, "Ponto (150,50) esta fora");

    // 3. Ponto FORA Negativo (-10, 50)
    verificar(pontoDentroPoligono(p, -10, 50) == false, "Ponto (-10,50) esta fora");

    eliminarPoligono(p);
}

void teste_sobreposicao_retangulo() {
    printf("\n--- Teste 2: Colisao com Retangulo ---\n");

    Poligono p = criar_poligono_quadrado(); // 0 a 100

    // Retângulo Totalmente DENTRO (10,10 tam 10x10)
    Retangulo rIn = CriarRetangulo(1, 10, 10, 10, 10, "r", "r");
    Pacote pIn = CriarPacote(rIn, RETANGULO);

    verificar(verificarSobreposicao(p, pIn) == true, "Retangulo dentro colidiu");

    // Retângulo Totalmente FORA (200,200 tam 10x10)
    Retangulo rOut = CriarRetangulo(2, 200, 200, 10, 10, "r", "r");
    Pacote pOut = CriarPacote(rOut, RETANGULO);

    verificar(verificarSobreposicao(p, pOut) == false, "Retangulo fora nao colidiu");

    // Retângulo PARCIALMENTE Dentro (Borda: 95,10 tam 20x10)
    // O algoritmo testa os cantos. (95,10) tá dentro. (115,10) tá fora.
    Retangulo rParcial = CriarRetangulo(3, 95, 10, 20, 10, "r", "r");
    Pacote pParcial = CriarPacote(rParcial, RETANGULO);

    verificar(verificarSobreposicao(p, pParcial) == true, "Retangulo na borda colidiu");

    eliminarPoligono(p);
    liberarForma(pIn); liberarForma(pOut); liberarForma(pParcial);
}

void teste_sobreposicao_circulo() {
    printf("\n--- Teste 3: Colisao com Circulo ---\n");

    Poligono p = criar_poligono_quadrado();

    // Círculo DENTRO (50,50 r=10)
    Circulo cIn = CriarCirculo(1, 50, 50, 10, "c", "c");
    Pacote pIn = CriarPacote(cIn, CIRCULO);
    verificar(verificarSobreposicao(p, pIn) == true, "Circulo dentro colidiu");

    // Círculo FORA (200,200 r=10)
    Circulo cOut = CriarCirculo(2, 200, 200, 10, "c", "c");
    Pacote pOut = CriarPacote(cOut, CIRCULO);
    verificar(verificarSobreposicao(p, pOut) == false, "Circulo fora nao colidiu");

    // Círculo com CENTRO FORA mas BORDA DENTRO
    // Centro (105, 50), Raio 10. O ponto (95, 50) deve entrar.
    // Função testa x-r. 105 - 10 = 95. 95 < 100.
    Circulo cBorda = CriarCirculo(3, 105, 50, 10, "c", "c");
    Pacote pBorda = CriarPacote(cBorda, CIRCULO);
    verificar(verificarSobreposicao(p, pBorda) == true, "Circulo raspando colidiu (teste x-r)");

    eliminarPoligono(p);
    liberarForma(pIn); liberarForma(pOut); liberarForma(pBorda);
}

void teste_sobreposicao_texto() {
    printf("\n--- Teste 4: Colisao com Texto (Ancoras) ---\n");

    Poligono p = criar_poligono_quadrado(); // 0 a 100

    // Texto "ABC" (largura 30), em (50,50). Âncora 'i'.
    // Vai de x=50 a x=80. DENTRO.
    Texto tIn = CriarTexto(1, 50, 50, "c", "c", 'i', "ABC");
    Pacote pIn = CriarPacote(tIn, TEXTO);
    verificar(verificarSobreposicao(p, pIn) == true, "Texto dentro colidiu");

    // Texto Âncora 'f' (Fim) em (110, 50).
    // Vai de x=80 (110-30) até x=110.
    // Parte dele (80 a 100) está DENTRO. O ponto (110,50) tá fora.
    // Função testa xMin. xMin=80. 80 < 100. Deve colidir.
    Texto tFim = CriarTexto(2, 110, 50, "c", "c", 'f', "ABC");
    Pacote pFim = CriarPacote(tFim, TEXTO);
    verificar(verificarSobreposicao(p, pFim) == true, "Texto ancora 'f' entrando colidiu");

    eliminarPoligono(p);
    liberarForma(pIn); liberarForma(pFim);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO POLIGONO\n");
    printf("==========================================\n");

    teste_ray_casting_basico();
    teste_sobreposicao_retangulo();
    teste_sobreposicao_circulo();
    teste_sobreposicao_texto();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}