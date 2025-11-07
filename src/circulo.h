//
// Created by natha on 19/09/2025.
//

#ifndef CIRCULO_H
#define CIRCULO_H
/*
 Módulo encarregado de coordenar um círculo com operações de criar, get, set, calcularArea e eliminar
 */

/*
 Ponteiro void Circulo
 */
typedef void* Circulo;

/// @brief Cria um círculo com os atributos indicados.
/// @param id Identificador único que se refere ao círculo.
/// @param x Coordenada x do centro do círculo.
/// @param y Coordenada y do centro do círculo.
/// @param r Raio do círculo.
/// @param corB Cor de borda do círculo no padrão RGB (Ex: #FFFFFF).
/// @param corP Cor de preenchimento do círculo no padrão RGB (Ex: #AA543B).
/// @return Ponteiro para o círculo criado.
/// @warning
Circulo CriarCirculo(int id, double x, double y, double r, char* corB,char* corP);

/// @brief Pega o ID do círculo sem modifica-lo.
/// @param c Ponteiro para o círculo analisado.
/// @return Um inteiro que representa o ID do círculo.
/// @warning
int getIDCirculo(Circulo c);

/// @brief Define o ID do círculo.
/// @param c Ponteiro para o círculo onde o ID será definido.
/// @param id ID que será definido.
/// @warning
void setIDCirculo(Circulo c, int id);

/// @brief Pega a coordenada x do círculo sem modifica-la.
/// @param c Ponteiro para o círculo analisado.
/// @return Um double que representa a coordenada x do círculo.
/// @warning
double getXCirculo(Circulo c);

/// @brief Define a nova coordenada x do círculo.
/// @param c Ponteiro para o círculo onde a coordenada x será definida.
/// @param x Nova coordenada x que será definida.
/// @warning
void setXCirculo(Circulo c, double x);

/// @brief Pega a coordenada y do círculo sem modifica-la.
/// @param c Ponteiro para o círculo analisado.
/// @return Um double que representa a coordenada y do círculo.
/// @warning
double getYCirculo(Circulo c);

/// @brief Define a nova coordenada y do círculo.
/// @param c Ponteiro para o círculo onde a coordenada y será definida.
/// @param y Nova coordenada y que será definida.
/// @warning
void setYCirculo(Circulo c, double y);

/// @brief Pega o raio do círculo sem modifica-lo.
/// @param c Ponteiro para o círculo analisado.
/// @return Um double que representa o raio do círculo.
/// @warning
double getRCirculo(Circulo c);

/// @brief Define o novo raio do círculo.
/// @param c Ponteiro para o círculo onde o raio será definida.
/// @param raio Novo raio que será definido.
/// @warning
void setRCirculo(Circulo c, double raio);

/// @brief Pega a cor de borda do círculo sem modifica-la.
/// @param c Ponteiro para o círculo analisado.
/// @return Uma string com a cor de borda do círculo.
/// @warning
char* getCorBCirculo(Circulo c);

/// @brief Define a nova cor de borda do círculo.
/// @param c Ponteiro para o círculo onde a cor de borda será definida.
/// @param corB Nova cor de borda que será definida.
/// @warning
void setCorBCirculo(Circulo c, char* corB);

/// @brief Pega a cor de preenchimento do círculo sem modifica-la.
/// @param c Ponteiro para o círculo analisado.
/// @return Uma string com a cor de preenchimento do círculo.
/// @warning
char* getCorPCirculo(Circulo c);

/// @brief Define a nova cor de preenchimento do círculo.
/// @param c Ponteiro para o círculo onde a cor de preenchimento será definida.
/// @param corP Nova cor de preenchimento que será definida.
/// @warning
void setCorPCirculo(Circulo c, char* corP);

/// @brief Calcula a área do círculo.
/// @param c Ponteiro para o círculo analisado.
/// @return Um double que representa a área do círculo.
/// @warning
double calcAreaCirculo(Circulo c);

/// @brief Libera a memória alocada para o círculo, incluindo as strings de cor.
/// @param c Ponteiro para o círculo que será eliminado.
/// @warning
void eliminarCirculo(Circulo c);

#endif //CIRCULO_H
