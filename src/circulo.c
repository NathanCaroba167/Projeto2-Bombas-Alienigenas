//
// Created by natha on 19/09/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "circulo.h"

#define PI 3.14159265358979323846

typedef struct{
  int id;
  double x,y;
  double r;
  char* corB; // Cor de Borda (alocada dinamicamente)
  char* corP; // Cor de Preenchimento (alocada dinamicamente)
}circulo;

Circulo CriarCirculo(int id, double x, double y, double r, char* corB,char* corP){
  circulo* c  = (circulo*)malloc(sizeof(circulo));

  if(c==NULL){
    printf("Erro ao alocar memória ao CriarCirculo!\n");

    perror("Motivo do erro");
    exit(1);
  }

  c->id = id;
  c->x = x;
  c->y = y;
  c->r = r;
  // Alocação da Cor de Borda
  c->corB = (char*) malloc (strlen(corB) + 1);
  if (c->corB == NULL) {
    printf("Erro ao alocar memória ao criar cor de borda do círculo!\n");
    free(c); // Libera a struct antes de sair

    perror("Motivo do erro");
    exit(1);
  }
  strcpy(c->corB,corB);

  // Alocação da Cor de Preenchimento
  c->corP = (char*) malloc (strlen(corP) + 1);
  if (c->corP == NULL) {
    printf("Erro ao alocar memória ao criar cor de preenchimento do círculo!\n");
    free(c->corB); // Libera o que foi alocado anteriormente
    free(c);

    perror("Motivo do erro");
    exit(1);
  }
  strcpy(c->corP,corP);

  return c;
}

int getIDCirculo(Circulo c){
  return ((circulo*)c)->id;
}

void setIDCirculo(Circulo c, int id){
  ((circulo*)c)->id = id;
}

double getXCirculo(Circulo c){
  return ((circulo*)c)->x;
  }

void setXCirculo(Circulo c,double x) {
  ((circulo*)c)->x = x;
}

double getYCirculo(Circulo c){
  return ((circulo*)c)->y;
}

void setYCirculo(Circulo c,double y){
  ((circulo*)c)->y = y;
}

double getRCirculo(Circulo c) {
  return ((circulo*)c)->r;
}

void setRCirculo(Circulo c,double r) {
  ((circulo*)c)->r = r;
}

char* getCorBCirculo(Circulo c){
  return ((circulo*)c)->corB;
}

void setCorBCirculo(Circulo c,char* corB) {
  circulo* circ = (circulo*)c;
  // Realoque o ponteiro existente para o novo tamanho da string (strlen(corB) + 1)
  circ->corB = realloc (circ->corB,strlen(corB) + 1);
  if (circ->corB == NULL) {
    // Se realloc falhar, a memória original (circ->corB) permanece válida
    printf("Erro ao realocar memória da cor de borda do círculo!\n");

    perror("Motivo do erro");
    exit(1);
  }
  strcpy(circ->corB,corB);
}

char* getCorPCirculo(Circulo c){
  return ((circulo*)c)->corP;
}

void setCorPCirculo(Circulo c, char* corP) {
  circulo* circ = (circulo*)c;
  // Realoque o ponteiro existente para o novo tamanho da string (strlen(corP) + 1)
  circ->corP = realloc (circ->corP,strlen(corP) + 1);
  if (circ->corP == NULL) {
    // Se realloc falhar, a memória original (circ->corP) permanece válida
    printf("Erro ao realocar memória da cor de preenchimento do círculo!\n");

    perror("Motivo do erro");
    exit(1);
  }
  strcpy(circ->corP,corP);
}

double calcAreaCirculo(Circulo c) {
  // Usa a constante PI definida acima
  return PI*pow(getRCirculo(c) ,2);
}

void eliminarCirculo(Circulo c) {
  circulo* circ = (circulo*)c;
  // Libera as strings alocadas dinamicamente
  free(circ->corB);
  free(circ->corP);
  // Libera a struct principal
  free(circ);
}