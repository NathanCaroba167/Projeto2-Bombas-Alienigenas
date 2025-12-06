//
// Created by natha on 09/10/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>

#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"
#include "forma.h"

#include "lista.h"
#include "txt.h"
#include "svg.h"
#include "bombas.h"
#include "qry.h"

#define TAMANHO_MAX_BUFFER 256

Arquivo abrirQry(Nome arquivo) {
    Arquivo qry = fopen(arquivo,"r");
    if (qry == NULL) {
        printf("Erro ao abrir o arquivo qry!\n");

        perror("Motivo do erro");
        exit(1);
    }
    return qry;
}

void LerComandosExecutar(Arquivo svg,Arquivo txt,Arquivo qry,Lista formas,Lista anteparos,char tipoOrd,int limIns) {
    char buffer[TAMANHO_MAX_BUFFER];

    while(fgets(buffer,sizeof(buffer),qry) != NULL) {

        buffer[strcspn(buffer,"\n")] = 0;

        if (buffer[0] == '\n' || buffer[0] == '\0') {
            continue;
        }

        fprintf(txt,"\n[*] %s\n", buffer);//

        char* comando = strtok(buffer," ");
        if (comando == NULL) {
            continue;
        }

        if (strcmp(comando, "a") == 0) {
            char* i_temp = strtok(NULL," ");
            char* j_temp = strtok(NULL," ");
            char* dir_temp = strtok(NULL," ");

            if (i_temp && j_temp) {
                int i = atoi(i_temp);
                int j = atoi(j_temp);

                char dir_modo;
                if (dir_temp != NULL) {
                    dir_modo = dir_temp[0];
                }else {
                    printf("Erro: sem parâmetro para direção do circulo!!");
                    exit(1);
                }

                Anteparo(txt,formas,anteparos,i,j,dir_modo);
            }
        }else if (strcmp(comando, "d") == 0) {
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* sfx_temp = strtok(NULL," ");

            if (x_temp && y_temp) {
                double x = atof(x_temp);
                double y = atof(y_temp);

                char* sfx_modo;
                if (sfx_temp != NULL) {
                    sfx_modo = sfx_temp;
                }else {
                    printf("Erro: sem parâmetro para direção do circulo!!");
                    exit(1);
                }

                Destruicao(svg,txt,formas,anteparos,x,y,sfx_modo, tipoOrd, limIns);
            }
        }else if (strcmp(comando, "p") == 0) {
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* cor_temp = strtok(NULL," ");
            char* sfx_temp = strtok(NULL," ");


            if (x_temp && y_temp && cor_temp ) {
                double x = atof(x_temp);
                double y = atof(y_temp);

                char* cor_modo = cor_temp;
                char* sfx_modo;
                if (sfx_temp != NULL) {
                    sfx_modo = sfx_temp;
                }else {
                    printf("Erro: sem parâmetro para direção do circulo!!");
                    exit(1);
                }


                Pintura(svg,txt,formas,anteparos,x,y,cor_modo,sfx_modo, tipoOrd, limIns);
            }
        }else if (strcmp(comando, "cln") == 0) {
            char* x_temp = strtok(NULL," ");
            char* y_temp = strtok(NULL," ");
            char* dx_temp = strtok(NULL," ");
            char* dy_temp = strtok(NULL," ");
            char* sfx_temp = strtok(NULL," ");

            if (x_temp && y_temp && dx_temp && dy_temp) {
                double x = atof(x_temp);
                double y = atof(y_temp);
                double dx = atof(dx_temp);
                double dy = atof(dy_temp);

                char* sfx_modo;
                if (sfx_temp != NULL) {
                    sfx_modo = sfx_temp;
                }else {
                    printf("Erro: sem parâmetro para direção do circulo!!");
                    exit(1);
                }

                Clone(svg,txt,formas,anteparos,x,y,dx,dy,sfx_modo, tipoOrd, limIns);
            }
        }else{
            printf("Comando desconhecido: '%s' \n", comando);
        }
    }
}