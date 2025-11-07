//
// Created by natha on 02/09/2025.
//

#ifndef RETANGULO_H
#define RETANGULO_H
/*
 Módulo encarregado de coordenar um retângulo com operações de criar, get, set, calcularArea e eliminar
*/

/*
 Ponteiro void Retangulo
*/
typedef void* Retangulo;

/// @brief Cria um retângulo com os atributos indicados.
/// @param id Identificador único que se refere ao retângulo.
/// @param x Coordenada x do ponto âncora (canto inferior esquerdo) do retângulo.
/// @param y Coordenada y do ponto âncora (canto inferior esquerdo) do retângulo.
/// @param w Largura do retângulo.
/// @param h Altura do retângulo.
/// @param corB Cor de borda do retângulo no padrão RGB (Ex: #FFFFFF).
/// @param corP Cor de preenchimento do retângulo no padrão RGB (Ex: #AA543B).
/// @return Ponteiro para o retângulo criado.
/// @warning
Retangulo CriarRetangulo(int id,double x,double y,double w,double h,char* corB,char* corP );

/// @brief Pega o ID do retângulo sem modifica-lo.
/// @param r Ponteiro para o retângulo analisado.
/// @return Um inteiro que representa o ID do retângulo.
/// @warning
int getIDRetangulo(Retangulo r);

/// @brief Define o ID do retângulo.
/// @param r Ponteiro para o retângulo onde o ID será definido.
/// @param id ID que será definido.
/// @warning
void setIDRetangulo(Retangulo r,int id);

/// @brief Pega a coordenada x do retângulo sem modifica-la.
/// @param r Ponteiro para o retângulo analisado.
/// @return Um double que representa a coordenada x do retângulo.
/// @warning
double getXRetangulo(Retangulo r);

/// @brief Define a nova coordenada x do retângulo.
/// @param r Ponteiro para o retângulo onde a coordenada x será definida.
/// @param x Nova coordenada x que será definida.
/// @warning
void setXRetangulo(Retangulo r,double x);

/// @brief Pega a coordenada y do retângulo sem modifica-la.
/// @param r Ponteiro para o retângulo analisado.
/// @return Um double que representa a coordenada y do retângulo.
/// @warning
double getYRetangulo(Retangulo r);

/// @brief Define a nova coordenada y do retângulo.
/// @param r Ponteiro para o retângulo onde a coordenada y será definida.
/// @param y Nova coordenada y que será definida.
/// @warning
void setYRetangulo(Retangulo r,double y);


/// @brief Pega a largura do retângulo sem modifica-lo.
/// @param r Ponteiro para o retângulo analisado.
/// @return Um double que representa a largura do retângulo.
/// @warning
double getWRetangulo(Retangulo r);

/// @brief Define a nova largura do retângulo.
/// @param r Ponteiro para o retângulo onde a largura será definida.
/// @param w Nova largura que será definido.
/// @warning
void setWRetangulo(Retangulo r,double w);

/// @brief Pega a altura do retângulo sem modifica-lo.
/// @param r Ponteiro para o retângulo analisado.
/// @return Um double que representa a altura do retângulo.
/// @warning
double getHRetangulo(Retangulo r);

/// @brief Define a nova altura do retângulo.
/// @param r Ponteiro para o retângulo onde a altura será definida.
/// @param h Nova altura que será definido.
/// @warning
void setHRetangulo(Retangulo r,double h);

/// @brief Pega a cor de borda do retângulo sem modifica-la.
/// @param r Ponteiro para o retângulo analisado.
/// @return Uma string com a cor de borda do retângulo.
/// @warning
char* getCorBRetangulo(Retangulo r);

/// @brief Define a nova cor de borda do retângulo.
/// @param r Ponteiro para o retângulo onde a cor de borda será definida.
/// @param corB Nova cor de borda que será definida.
/// @warning
void setCorBRetangulo(Retangulo r,char* corB);

/// @brief Pega a cor de preenchimento do retângulo sem modifica-la.
/// @param r Ponteiro para o retângulo analisado.
/// @return Uma string com a cor de preenchimento do retângulo.
/// @warning
char* getCorPRetangulo(Retangulo r);

/// @brief Define a nova cor de preenchimento do retângulo.
/// @param r Ponteiro para o retângulo onde a cor de preenchimento será definida.
/// @param corP Nova cor de preenchimento que será definida.
/// @warning
void setCorPRetangulo(Retangulo r,char* corP);

/// @brief Calcula a área do retângulo (w * h).
/// @param r Ponteiro para o retângulo analisado.
/// @return Um double que representa a área do retângulo.
/// @warning
double calcAreaRetangulo(Retangulo r);

/// @brief Libera a memória alocada para o retângulo, incluindo as strings de cor.
/// @param r Ponteiro para o retângulo que será eliminado.
/// @warning
void eliminarRetangulo(Retangulo r);

#endif//RETANGULO_H