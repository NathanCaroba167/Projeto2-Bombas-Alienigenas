//
// Created by natha on 03/12/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../lista.h"

typedef struct {
    int id_falso;
} MockForma;

MockForma* CriarMock(int id) {
    MockForma* m = (MockForma*) malloc(sizeof(MockForma));
    m->id_falso = id;
    return m;
}

int getIDForma(Pacote p) {
    MockForma* m = (MockForma*)p;
    return m->id_falso;
}

void liberarForma(Pacote p) {
    free(p);
}


void verificar(int condicao, const char* mensagem) {
    if (condicao) {
        printf("\033[0;32m[OK]\033[0m %s\n", mensagem);
    } else {
        printf("\033[0;31m[ERRO]\033[0m %s\n", mensagem);
        exit(1);
    }
}


void teste_insercao_basica() {
    printf("\n--- Teste 1: Insercao Inicio e Fim ---\n");

    Lista l = iniciarLista();
    verificar(listavazia(l) == true, "Lista recem criada deve ser vazia");
    verificar(getTamanhoLista(l) == 0, "Tamanho inicial zero");

    Pacote p1 = CriarMock(10);
    Pacote p2 = CriarMock(20);
    Pacote p3 = CriarMock(30);

    inserirListaInicio(l, p1);
    verificar(getTamanhoLista(l) == 1, "Tamanho deve ser 1");

    inserirListaFim(l, p2);
    verificar(getTamanhoLista(l) == 2, "Tamanho deve ser 2");

    inserirListaInicio(l, p3);

    pont node = getPrimeiroElementoLista(l);
    verificar(getIDForma(getPacoteElementoLista(node)) == 30, "Primeiro elemento deve ser 30");

    node = getProximoElementoLista(node);
    verificar(getIDForma(getPacoteElementoLista(node)) == 10, "Segundo elemento deve ser 10");

    node = getProximoElementoLista(node);
    verificar(getIDForma(getPacoteElementoLista(node)) == 20, "Terceiro elemento deve ser 20");

    pont ultimo = getUltimoElementoLista(l);
    verificar(getIDForma(getPacoteElementoLista(ultimo)) == 20, "Ponteiro Fim deve apontar para 20");

    liberarLista(l);
}

void teste_busca_remocao_por_id() {
    printf("\n--- Teste 2: Busca e Remocao por ID ---\n");

    Lista l = iniciarLista();
    inserirListaFim(l, CriarMock(1));
    inserirListaFim(l, CriarMock(2));
    inserirListaFim(l, CriarMock(3));

    Pacote p = getPorIdLista(l, 2);
    verificar(p != NULL, "Busca por ID 2 encontrou algo");
    if (p) verificar(getIDForma(p) == 2, "ID encontrado realmente e 2");

    Pacote pNull = getPorIdLista(l, 99);
    verificar(pNull == NULL, "Busca por ID 99 retornou NULL");

    removerPorIdLista(l, 2);

    verificar(getTamanhoLista(l) == 2, "Tamanho reduziu para 2");
    verificar(getPorIdLista(l, 2) == NULL, "ID 2 nao existe mais");

    removerPorIdLista(l, 1);
    pont primeiro = getPrimeiroElementoLista(l);
    verificar(getIDForma(getPacoteElementoLista(primeiro)) == 3, "Novo primeiro e 3");

    liberarLista(l);

    free(p);

}

void teste_concatenacao() {
    printf("\n--- Teste 3: Concatenacao ---\n");

    Lista l1 = iniciarLista();
    inserirListaFim(l1, CriarMock(1));
    inserirListaFim(l1, CriarMock(2));

    Lista l2 = iniciarLista();
    inserirListaFim(l2, CriarMock(3));
    inserirListaFim(l2, CriarMock(4));

    concatenaListas(l1, l2);

    verificar(getTamanhoLista(l1) == 4, "Tamanho de L1 deve ser 4");
    verificar(getTamanhoLista(l2) == 0, "Tamanho de L2 deve ser 0");
    verificar(listavazia(l2) == true, "L2 deve estar vazia (ponteiros resetados)");

    pont no = getPrimeiroElementoLista(l1);
    verificar(getIDForma(getPacoteElementoLista(no)) == 1, "Pos 1 OK");
    no = no->prox;
    verificar(getIDForma(getPacoteElementoLista(no)) == 2, "Pos 2 OK");
    no = no->prox;
    verificar(getIDForma(getPacoteElementoLista(no)) == 3, "Pos 3 OK");
    no = no->prox;
    verificar(getIDForma(getPacoteElementoLista(no)) == 4, "Pos 4 OK");

    pont ultimo = getUltimoElementoLista(l1);
    verificar(getIDForma(getPacoteElementoLista(ultimo)) == 4, "Fim de L1 atualizado corretamente");

    liberarLista(l1);
    liberarLista(l2);
}

int main() {
    printf("==========================================\n");
    printf("   TESTE UNITARIO: MODULO LISTA\n");
    printf("==========================================\n");

    teste_insercao_basica();
    teste_concatenacao();

    printf("\n==========================================\n");
    printf("   SUCESSO: TODOS OS TESTES PASSARAM!\n");
    printf("==========================================\n");

    return 0;
}