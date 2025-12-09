//
// Created by natha on 04/10/2025.
//

#ifndef SVG_H
#define SVG_H

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "segmento.h"
#include "poligono.h"
#include "lista.h"

/*
 Módulo encarregado de gerar um arquivo SVG a partir das formas presentes e executar os comandos com as operações de abrir,
 inicializar, desenhar, gerar e fechar
 */

/*
 Ponteiro do tipo FILE Arquivo
 Ponteiro char Nome
 */
typedef FILE* Arquivo;
typedef char* Nome;

/// @brief Cria e abre o arquivo SVG para escrita (sobrescrevendo o conteúdo existentes).
/// @param arquivo Ponteiro para o nome do arquivo que será criado e aberto.
/// @return Ponteiro para o arquivo (FILE*).
/// @warning
Arquivo abrirSVG(Nome arquivo);

/// @brief Adiciona a tag iniciais do arquivo SVG.
/// @param svg Ponteiro para o arquivo que será inicializado.
/// @warning
void inicializarSVG(Arquivo svg);

/// @brief Desenha um círculo no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param c Círculo que será desenhado.
/// @warning
void desenharCirculoSVG(Arquivo svg, Circulo c);

/// @brief Desenha um retângulo no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param r Retângulo que será desenhado.
/// @warning
void desenharRetanguloSVG(Arquivo svg, Retangulo r);

/// @brief Desenha uma linha no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param l Linha que será desenhada.
/// @warning
void desenharLinhaSVG(Arquivo svg, Linha l);

/// @brief Desenha um texto no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param t Texto que será desenhado.
/// @param e Estilo do texto que será desenhado.
/// @warning
void desenharTextoSVG(Arquivo svg, Texto t, Estilo e);

/// @brief Desenha um segmento no arquivo SVG.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param s Segmento que será desenhado.
/// @warning
void desenharSegmentoSVG(Arquivo svg, Segmento s);

/// @brief Desenha um asterisco vermelho no local da bomba lançada.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param x Coordenada x da bomba.
/// @param y Coordenada y da bomba.
/// @warning
void desenharBombaSVG(Arquivo svg, double x, double y);///

/// @brief Desenha um poligono que representa a região de visibilidade da bomba lançada.
/// @param svg Ponteiro para o arquivo que receberá o desenho.
/// @param p Ponteiro para o poligono analisado.
/// @warning
void desenharPoligonoSVG(Arquivo svg, Poligono p);

/// @brief Desenha todas as formas presentes na lista da área no arquivo SVG.
/// @param svg Ponteiro para o arquivo SVG que receberá o desenho.
/// @param forma Lista que contém as formas.
/// @param EstiloGlobalTexto Estilo global do texto.
/// @warning
void desenharFormasDaLista(Arquivo svg, Lista forma,Estilo EstiloGlobalTexto);

/// @brief Fecha o arquivo SVG, adicionando as tags de fechamento.
/// @param svg Ponteiro para o arquivo que será fechado.
/// @warning
void fecharSVG(Arquivo svg);

/// @brief Gera arquivo SVG após a leitura da lista e fecha o arquivo.
/// @param forma Lista que mandará as formas.
/// @param arqSvg Ponteiro para o arquivo SVG.
/// @param EstiloGlobalTexto Estilo global do texto.
/// @warning
void gerarSVG(Lista forma, Arquivo arqSvg, Estilo EstiloGlobalTexto);

#endif //SVG_H