//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

int sao_iguais(double a, double b) {
    return fabs(a - b) < 1e-4;
}

// --- TESTES ---

void teste_pacote_basico() {
    printf("\n--- Teste 1: Criacao de Pacote e Tipo ---\n");

    // Cria um circulo real
    Circulo c = CriarCirculo(10, 0, 0, 5, "red", "blue");

    // Empacota
    Pacote p = CriarPacote(c, CIRCULO);

    verificar(p != NULL, "Pacote criado");
    verificar(getTipoForma(p) == CIRCULO, "Tipo do pacote e CIRCULO");
    verificar(getDadosForma(p) == c, "Ponteiro interno corresponde ao objeto original");

    liberarForma(p); // Libera pacote e circulo
}

void teste_polimorfismo_getters() {
    printf("\n--- Teste 2: Polimorfismo (Get ID/X/Y/Cor) ---\n");

    // Teste com Retângulo
    Retangulo r = CriarRetangulo(50, 10.0, 20.0, 100.0, 50.0, "black", "white");
    Pacote pR = CriarPacote(r, RETANGULO);

    verificar(getIDForma(pR) == 50, "getIDForma (Retangulo) OK");
    verificar(sao_iguais(getXForma(pR), 10.0), "getXForma (Retangulo) OK");
    verificar(sao_iguais(getYForma(pR), 20.0), "getYForma (Retangulo) OK");
    verificar(strcmp(getCorBForma(pR), "black") == 0, "getCorBForma (Retangulo) OK");

    // Teste com Texto
    Texto t = CriarTexto(60, 5.5, 6.6, "yellow", "green", 'i', "Ola");
    Pacote pT = CriarPacote(t, TEXTO);

    verificar(getIDForma(pT) == 60, "getIDForma (Texto) OK");
    verificar(sao_iguais(getXForma(pT), 5.5), "getXForma (Texto) OK");

    liberarForma(pR);
    liberarForma(pT);
}

void teste_gestao_ids() {
    printf("\n--- Teste 3: Gestao de IDs Globais ---\n");

    armazenaMaiorId(100);
    verificar(getMaiorId() == 101, "Armazena 100 -> Proximo ID deve ser 101");

    adicionaMaiorID(5);
    verificar(getMaiorId() == 106, "Adiciona 5 -> Proximo ID deve ser 106");
}

void teste_clonagem() {
    printf("\n--- Teste 4: Clonagem (Deep Copy + Deslocamento) ---\n");

    // Reseta ID para controle
    armazenaMaiorId(1000);

    // Original: Circulo ID 10, (10,10)
    Circulo c = CriarCirculo(10, 10.0, 10.0, 5.0, "red", "blue");
    Pacote pOriginal = CriarPacote(c, CIRCULO);

    // Clone com dx=50, dy=50
    // Novo ID esperado: 1001
    Pacote pClone = clonarForma(pOriginal, 50.0, 50.0);

    verificar(pClone != NULL, "Clone criado");
    verificar(pClone != pOriginal, "Clone e um novo objeto na memoria");

    // Verifica atributos do clone
    verificar(getTipoForma(pClone) == CIRCULO, "Tipo mantido");

    // ID deve ser novo
    int idClone = getIDForma(pClone);
    printf("   ID Original: 10. ID Clone: %d.\n", idClone);
    verificar(idClone != 10, "Clone tem ID diferente");

    // Coordenadas devem estar deslocadas
    double xClone = getXForma(pClone);
    double yClone = getYForma(pClone);
    printf("   Pos Original: (10,10). Pos Clone: (%.1f, %.1f).\n", xClone, yClone);

    verificar(sao_iguais(xClone, 60.0), "X deslocado (+50) corretamente");
    verificar(sao_iguais(yClone, 60.0), "Y deslocado (+50) corretamente");

    verificar(strcmp(getCorBForma(pClone), "red") == 0, "Cor borda copiada");

    liberarForma(pOriginal);
    liberarForma(pClone);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO FORMA\n");
    printf("==========================================\n");

    teste_pacote_basico();
    teste_polimorfismo_getters();
    teste_gestao_ids();
    teste_clonagem();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}