//
// Created by natha on 19/09/2025.
//

#ifndef TEXTO_H
#define TEXTO_H
/*
 Módulo encarregado de coordenar um texto e o estilo de texto com operações de criar, get, set, calcularArea, quantidade e eliminar
*/

/*
 Ponteiro void Texto
 Ponteiro void Estilo
 */
typedef void* Estilo;
typedef void* Texto;

/// @brief Cria um Estilo com os atributos da fonte.
/// @param fFamily Família da fonte do texto.
/// @param fWeight Peso da fonte do texto.
/// @param fSize Tamanho da fonte do texto.
/// @return Ponteiro para o estilo criado.
Estilo CriarEstilo(char* fFamily ,char* fWeight, char* fSize);

/// @brief Cria um texto com os atributos indicados.
/// @param id Identificador único que se refere ao texto.
/// @param x Coordenada x do ponto âncora do texto.
/// @param y Coordenada y do ponto âncora do texto.
/// @param corB Cor de borda do texto no padrão RGB (Ex: #FFFFFF).
/// @param corP Cor de preenchimento do texto no padrão RGB (Ex: #AA543B).
/// @param a Ponto âncora do texto ('i' - Inìcio // 'm' - Meio // 'f' - Fim).
/// @param txto O conteúdo do texto (o texto em si).
/// @return Ponteiro para o texto criado.
/// @warning
Texto CriarTexto(int id, double x, double y, char* corB, char* corP, char a, char* txto);

/// @brief Pega o ID do texto sem modifica-lo.
/// @param t Ponteiro para o texto analisada.
/// @return Um inteiro que representa o ID do texto.
/// @warning
int getIDTexto(Texto t);

/// @brief Define o ID do texto.
/// @param t Ponteiro para o texto onde o ID será definido.
/// @param id ID que será definido.
/// @warning
void setIDTexto(Texto t, int id);

/// @brief Pega a coordenada x do ponto âncora do texto sem modifica-la.
/// @param t Ponteiro para o texto analisada.
/// @return Um double que representa a coordenada x do ponto âncora do texto.
/// @warning
double getXTexto(Texto t);

/// @brief Define a nova coordenada x do ponto âncora do texto.
/// @param t Ponteiro para o texto onde a coordenada x do ponto âncora será definida.
/// @param x Nova coordenada x do ponto âncora do texto que será definida.
/// @warning
void setXTexto(Texto t, double x);

/// @brief Pega a coordenada y do ponto âncora do texto sem modifica-la.
/// @param t Ponteiro para o texto analisado.
/// @return Um double que representa a coordenada y do ponto âncora do texto.
/// @warning
double getYTexto(Texto t);

/// @brief Define a nova coordenada y do ponto âncora do texto.
/// @param t Ponteiro para o texto onde a coordenada y do ponto âncora será definida.
/// @param y Nova coordenada y do ponto âncora do texto que será definida.
/// @warning
void setYTexto(Texto t, double y);

/// @brief Pega a cor de borda do texto sem modifica-la.
/// @param t Ponteiro para o texto analisado.
/// @return Uma string com a cor de borda do texto.
/// @warning
char* getCorBTexto(Texto t);

/// @brief Define a nova cor de borda do texto.
/// @param t Ponteiro para o texto onde a cor de borda será definida.
/// @param corB Nova cor de borda que será definida.
/// @warning
void setCorBTexto(Texto t,char* corB);

/// @brief Pega a cor de preenchimento do texto sem modifica-la.
/// @param t Ponteiro para o texto analisado.
/// @return Uma string com a cor de preenchimento do texto.
/// @warning
char* getCorPTexto(Texto t);

/// @brief Define a nova cor de preenchimento do texto.
/// @param t Ponteiro para o texto onde a cor de preenchimento será definida.
/// @param corP Nova cor de preenchimento que será definida.
/// @warning
void setCorPTexto(Texto t,char* corP);

/// @brief Pega a âncora do texto sem modifica-la.
/// @param t Ponteiro para o texto analisado.
/// @return Um caractere que representa a âncora do texto.
/// @warning
char getATexto(Texto t);

/// @brief Define a nova âncora do texto.
/// @param t Ponteiro para o texto onde a âncora será definida.
/// @param a Nova âncora que será definida.
/// @warning
void setATexto(Texto t, char a);

/// @brief Pega o conteúdo do texto sem modifica-lo.
/// @param t Ponteiro para o texto analisado.
/// @return Uma string que representa o conteúdo do texto.
/// @warning
char* getTxtoTexto(Texto t);

/// @brief Define o novo conteúdo do texto.
/// @param t Ponteiro para o texto onde o conteúdo será definido.
/// @param txto Novo conteúdo que será definido.
/// @warning
void setTxtoTexto(Texto t, char* txto);

/// @brief Pega a família da fonte do texto sem modifica-lo.
/// @param e Ponteiro para o estilo analisado.
/// @return Uma string que representa a família da fonte do texto.
/// @warning
char* getFontFamilyTexto(Estilo e);

/// @brief Define a nova família da fonte do texto.
/// @param e Ponteiro para o estilo onde a família da fonte será definida.
/// @param family Nova família da fonte que será definida.
/// @warning
void setFontFamilyTexto(Estilo e, char* family);

/// @brief Pega o peso da fonte do texto sem modifica-lo.
/// @param e Ponteiro para o estilo analisado.
/// @return Uma string que representa o peso da fonte do texto.
/// @warning
char* getFontWeightTexto(Estilo e);

/// @brief Define o novo peso da fonte do texto.
/// @param e Ponteiro para o estilo onde o peso da fonte será definido.
/// @param weight Novo peso da fonte que será definido.
/// @warning
void setFontWeightTexto(Estilo e, char* weight);

/// @brief Pega o tamanho da fonte do texto sem modifica-lo.
/// @param e Ponteiro para o estilo analisado.
/// @return Uma string que representa o tamanho da fonte do texto.
/// @warning
char* getFontSizeTexto(Estilo e);

/// @brief Define o novo tamanho da fonte do texto.
/// @param e Ponteiro para o estilo onde o tamanho da fonte será definido.
/// @param size Novo tamanho da fonte que será definido.
/// @warning
void setFontSizeTexto(Estilo e, char* size);

/// @brief Pega a quantidade de caracteres do texto.
/// @param t Ponteiro para texto analisado.
/// @return A quantidade de caracteres do texto.
/// @warning
size_t quantidadeCaracteresTexto(Texto t);

/// @brief Calcula a área do texto (20 * número de caracteres).
/// @param t Ponteiro para o texto analisado.
/// @return Um double que representa a área do texto.
/// @warning
double calcAreaTexto(Texto t);

/// @brief Libera a memória alocada para o estilo.
/// @param e Ponteiro para o o estilo analisado.
/// @warning
void eliminarEstilo(Estilo e);

/// @brief Libera a memória alocada para o texto, incluindo strings de cor
/// @param t Ponteiro para o texto analisado.
/// @warning
void eliminarTexto(Texto t);

#endif //TEXTO_H
