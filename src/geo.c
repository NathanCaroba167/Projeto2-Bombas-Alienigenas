//
// Created by natha on 09/10/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "forma.h"
#include "lista.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "geo.h"

#define TAMANHO_MAX_BUFFER 256

Arquivo abrirGeo(Nome arquivo) {
    // Abrindo o arquivo para leitura ('r')
    Arquivo geo = fopen(arquivo,"r");
    if (geo == NULL) {
        printf("Erro ao abrir o arquivo geo!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return geo;
}

void criarFormasNaLista(Arquivo geo, Lista forma,Estilo* EstiloPonteiro) {
    if (geo == NULL || forma == NULL || EstiloPonteiro == NULL) {
        printf("ERRO: Argumentos NULL em criarFormasNoChao.\n");
        return;
    }

    int maiorID = 0;
    char buffer[TAMANHO_MAX_BUFFER];

    while(fgets(buffer,sizeof(buffer),geo) != NULL) {
        // Remove quebras de linha e trata linhas vazias
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            continue;
        }

        char* comando = strtok(buffer," ");
        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "c") == 0) {
            char* id_temp = strtok(NULL," ");
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* r_temp = strtok(NULL," ");
            char* corB = strtok(NULL," ");
            char* corP = strtok(NULL," ");

            if (id_temp && x_temp && y_temp && r_temp && corB && corP) {
                int id = atoi(id_temp);
                double x = atof(x_temp);
                double y = atof(y_temp);
                double r = atof(r_temp);

                if (maiorID < id) {
                    maiorID = id;
                }
                Circulo c = CriarCirculo(id, x, y, r, corB, corP);
                inserirListaFim(forma ,CriarPacote(c,CIRCULO));
            }
        }else if (strcmp(comando, "r") == 0) {
            char* id_temp = strtok(NULL," ");
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* w_temp = strtok(NULL," ");
            char* h_temp = strtok(NULL," ");
            char* corB = strtok(NULL," ");
            char* corP = strtok(NULL," ");

            if (id_temp && x_temp && y_temp && w_temp && h_temp && corB && corP) {
                int id = atoi(id_temp);
                double x = atof(x_temp);
                double y = atof(y_temp);
                double w = atof(w_temp);
                double h = atof(h_temp);
                if (maiorID < id) {
                    maiorID = id;
                }
                Retangulo r = CriarRetangulo(id, x, y, w, h, corB, corP);
                inserirListaFim(forma,CriarPacote(r,RETANGULO));
            }
        }else if (strcmp(comando, "l") == 0) {
            char* id_temp = strtok(NULL," ");
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* x2_temp = strtok(NULL," ");
            char* y2_temp = strtok(NULL," ");
            char* cor = strtok(NULL," ");

            if (id_temp && x_temp && y_temp && x2_temp && y2_temp && cor) {
                int id = atoi(id_temp);
                double x = atof(x_temp);
                double y = atof(y_temp);
                double x2 = atof(x2_temp);
                double y2 = atof(y2_temp);
                if (maiorID < id) {
                    maiorID = id;
                }
                Linha l = CriarLinha(id, x, y, x2, y2, cor);
                inserirListaFim(forma,CriarPacote(l,LINHA));
            }
        }else if (strcmp(comando, "t") == 0) {
            char* id_temp = strtok(NULL," ");
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* corB = strtok(NULL," ");
            char* corP = strtok(NULL," ");
            char* a_temp = strtok(NULL," ");
            char* txto = a_temp + strlen(a_temp) + 1;

            // Move o ponteiro para o início real do texto (ignorando espaços após 'a_temp')
            while (*txto == ' ') {
                txto++;
            }
            txto[strcspn(txto,"\n")] = 0;
            if (id_temp && x_temp && y_temp && corB && corP && a_temp && txto) {
                int id = atoi(id_temp);
                double x = atof(x_temp);
                double y = atof(y_temp);
                char a = a_temp[0];

                if (maiorID < id) {
                    maiorID = id;
                }
                Texto t = CriarTexto(id, x, y, corB, corP, a, txto);
                inserirListaFim(forma,CriarPacote(t,TEXTO));
            }
        }else if (strcmp(comando, "ts") == 0) {
            char* fFamily  = strtok(NULL," ");
            char* fWeight = strtok(NULL," ");
            char* fSize = strtok(NULL," ");

            if (fFamily && fWeight && fSize) {
                char* pesoCompleto = fWeight;

                if (strcmp(fWeight, "n") == 0) {
                    pesoCompleto = "normal";
                }
                else if (strcmp(fWeight, "b") == 0) {
                    pesoCompleto = "bold";
                }
                else if (strcmp(fWeight, "b+") == 0) {
                    pesoCompleto = "bolder";
                }
                else if (strcmp(fWeight, "l") == 0) {
                    pesoCompleto = "lighter";
                }

                // Se o EstiloPonteiro já contém um estilo alocado, ele deve ser liberado
                if (*EstiloPonteiro != NULL) {
                    eliminarEstilo(*EstiloPonteiro);
                }

                *EstiloPonteiro = CriarEstilo(fFamily,pesoCompleto,fSize);
            }
        }else {
            printf("Comando desconhecido: '%s'\n", comando);
        }
    }
    // Armazena o maior ID encontrado para ser usado na geração de novos IDs
    armazenaMaiorId(maiorID);
}