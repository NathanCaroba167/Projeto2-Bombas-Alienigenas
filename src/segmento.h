//
// Created by natha on 13/11/2025.
//

#ifndef SEGMENTO_H
#define SEGMENTO_H

/*
 Módulo encarregado de coordenar um segmento com operações de criar, get, set, 'calcTamanho' e eliminar
*/

typedef enum {
    ANTEPARO,
    AREA
}TipoSegmento;

/*
 Ponteiro void Segmento
 */
typedef void* Segmento;

/// @brief Cria um segmento com os atributos indicados.
/// @param id Identificador único que se refere ao segmento.
/// @param x1 Coordenada x do ponto de início do segmento.
/// @param y1 Coordenada y do ponto de início do segmento.
/// @param x2 Coordenada x do ponto de fim do segmento.
/// @param y2 Coordenada y do ponto de fim do segmento.
/// @param cor Cor do segmento no padrão RGB (Ex: #FFFFFF).
/// @param tipo Tipo de segmento (ANTEPARO ou AREA) que foi criada.
/// @return Ponteiro para o segmento criado.
/// @warning
Segmento CriarSegmento(int id, double x1, double y1, double x2, double y2, char* cor,TipoSegmento tipo);

/// @brief Pega o ID do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Um inteiro que representa o ID do segmento.
/// @warning
int getIDSegmento(Segmento s);

/// @brief Define o ID do segmento.
/// @param s Ponteiro para o segmento onde o ID será definido.
/// @param id ID que será definido.
/// @warning
void setIDSegmento(Segmento s, int id);///

/// @brief Pega a coordenada x do ponto do início do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Um double que representa a coordenada x do ponto do início do segmento.
/// @warning
double getX1Segmento(Segmento s);

/// @brief Pega a coordenada y do ponto do início do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Um double que representa a coordenada y do ponto do início do segmento.
/// @warning
double getY1Segmento(Segmento s);

/// @brief Pega a coordenada x do ponto do fim do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Um double que representa a coordenada x do ponto do fim do segmento.
/// @warning
double getX2Segmento(Segmento s);

/// @brief Pega a coordenada y do ponto do fim do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Um double que representa a coordenada y do ponto do fim do segmento.
/// @warning
double getY2Segmento(Segmento s);

/// @brief Define o ponto de início do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @param x1 Nova coordenada x do ponto de início do segmento que será definida.
/// @param y1 Nova coordenada y do ponto de início do segmento que será definida.
/// @warning
void setP1Segmento(Segmento s, double x1, double y1);

/// @brief Define o ponto de fim do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @param x2 Nova coordenada x do ponto de fim do segmento que será definida.
/// @param y2 Nova coordenada y do ponto de fim do segmento que será definida.
/// @warning
void setP2Segmento(Segmento s, double x2, double y2);

/// @brief Pega a cor do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Uma string com a cor da linha.
/// @warning
char* getCorSegmento(Segmento s);

/// @brief Define a nova cor do segmento.
/// @param s Ponteiro para o segmento onde a cor será definida.
/// @param cor Nova cor do segmento que será definida.
/// @warning
void setCorSegmento(Segmento s, char* cor);

/// @brief Pega o tipo de segmento que está dentro do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Ponteiro para o tipo do segmento que foi pego.
/// @warning
TipoSegmento getTipoSegmento(Segmento s);

/// @brief Calcula o tamanho/comprimento do segmento sem modifica-lo.
/// @param s Ponteiro para o segmento analisado.
/// @return Um double que representa o comprimento do segmento.
/// @warning
double calcTamanhoSegmento(Segmento s);

/// @brief Indica a orientação de um ponto em relação ao Segmento.
/// @param s Ponteiro para o segmento analisado.
/// @param px Coordenada x do ponto analisado.
/// @param py Coordenada y do ponto analisado.
/// @return Um double que se > 0: Ponto está a esquerda, se < 0: Ponto está a direita e se = 0 o Ponto está colinear ao segmento.
/// @warning
double orientacaoPontoSegmento(Segmento s, double px, double py);

/// @brief Libera a memória alocada para o segmento, incluindo a string de cor.
/// @param s Ponteiro para o segmento que será eliminado.
/// @warning
void eliminarSegmento(Segmento s);

#endif //SEGMENTO_H