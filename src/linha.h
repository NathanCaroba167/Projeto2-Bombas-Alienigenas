//
// Created by natha on 19/09/2025.
//

#ifndef LINHA_H
#define LINHA_H

/*
 Módulo encarregado de coordenar uma linha com operações de criar, get, set, calcularArea e eliminar
*/

/*
 Ponteiro void Linha
 */
typedef void* Linha;

/// @brief Cria uma linha com os atributos indicados.
/// @param id Identificador único que se refere a linha.
/// @param x1 Coordenada x do ponto do início da linha.
/// @param y1 Coordenada y do ponto do início da linha.
/// @param x2 Coordenada x do ponto do final da linha.
/// @param y2 Coordenada y do ponto do final da linha.
/// @param cor Cor da linha no padrão RGB (Ex: #FFFFFF).
/// @return Ponteiro para a linha criada.
/// @warning
Linha CriarLinha(int id, double x1, double y1, double x2, double y2 ,char* cor);

/// @brief Pega o ID da linha sem modifica-lo.
/// @param l Ponteiro para a linha analisada.
/// @return Um inteiro que representa o ID da linha.
/// @warning
int getIDLinha(Linha l);

/// @brief Define o ID da linha.
/// @param l Ponteiro para a linha onde o ID será definido.
/// @param id ID que será definido.
/// @warning
void setIDLinha(Linha l, int id);

/// @brief Pega a coordenada x do ponto do início da linha sem modifica-la.
/// @param l Ponteiro para a linha analisada.
/// @return Um double que representa a coordenada x do ponto do início da linha.
/// @warning
double getX1Linha(Linha l);

/// @brief Define a nova coordenada x do ponto do início da linha.
/// @param l Ponteiro para a linha onde a coordenada x será definida.
/// @param x1 Nova coordenada x do ponto de início da linha que será definida.
/// @warning
void setX1Linha(Linha l, double x1);

/// @brief Pega a coordenada y do ponto do início da linha sem modifica-la.
/// @param l Ponteiro para a linha analisada.
/// @return Um double que representa a coordenada y do ponto do início da linha.
/// @warning
double getY1Linha(Linha l);

/// @brief Define a nova coordenada y do ponto do início da linha.
/// @param l Ponteiro para a linha onde a coordenada y será definida.
/// @param y1 Nova coordenada y do ponto de início da linha que será definida.
/// @warning
void setY1Linha(Linha l, double y1);

/// @brief Pega a coordenada x do ponto do início da linha sem modifica-la.
/// @param l Ponteiro para a linha analisada.
/// @return Um double que representa a coordenada x do ponto do início da linha.
/// @warning
double getX2Linha(Linha l);

/// @brief Define a nova coordenada x do ponto do início da linha.
/// @param l Ponteiro para a linha onde a coordenada x será definida.
/// @param x2 Nova coordenada x do ponto de início da linha que será definida.
/// @warning
void setX2Linha(Linha l, double x2);

/// @brief Pega a coordenada y do ponto do início da linha sem modifica-la.
/// @param l Ponteiro para a linha analisada.
/// @return Um double que representa a coordenada y do ponto do início da linha.
/// @warning
double getY2Linha(Linha l);

/// @brief Define a nova coordenada y do ponto do início da linha.
/// @param l Ponteiro para a linha onde a coordenada y será definida.
/// @param y2 Nova coordenada y do ponto de início da linha que será definida.
/// @warning
void setY2Linha(Linha l, double y2);

/// @brief Pega a cor da linha sem modifica-la.
/// @param l Ponteiro para a linha analisada.
/// @return Uma string com a cor da linha.
/// @warning
char* getCorLinha(Linha l);

/// @brief Define a nova cor da linha.
/// @param l Ponteiro para a linha onde a cor será definida.
/// @param cor Nova cor da linha que será definida.
/// @warning
void setCorLinha(Linha l, char* cor);

/// @brief Acha a cor complementar da cor da linha.
/// @param l Ponteiro para linha analisada.
/// @return String com a cor complementar (alocada dinamicamente) no formato RGB (Ex: #RRGGBB).
char* CorComplementarLinha(Linha l);

/// @brief Calcula a área da linha (2 * comprimento da linha).
/// @param l Ponteiro para a linha analisada.
/// @return Um double que representa a área da linha.
/// @warning
double calcAreaLinha(Linha l);

/// @brief Libera a memória alocada para a linha, incluindo a string de cor.
/// @param l Ponteiro para a linha que será eliminada.
/// @warning
void eliminarLinha(Linha l);

#endif //LINHA_H
