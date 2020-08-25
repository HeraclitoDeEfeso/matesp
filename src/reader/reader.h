#ifndef READER_H
#define READER_H
/**
 * @file reader.h
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Interfaz de la clases Parser y Tokenizer de la aplicación laplace 
 * @version 0.1
 * @date 2020-06-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include "../expr/expr.h"

/**
 * @brief Cantidad de caracteres máximos permitidos en un comando
 * 
 */
#define MAX_LINE_SIZE 80

/**
 * @brief Delimitador de símbolos en un comando
 * 
 */
#define COMMAND_DELIM " \t\n"

/**
 * @brief TAD que representa el analizador léxico del lenguaje
 * 
 */
struct Lexer {
    /**
     * @brief Campo que conserva la cantidad de líneas leídas
     * 
     */
    int lines;
};

/**
 * @brief TAD que representa el analizador sintáctico del lenguaje
 * 
 */
struct Parser {
    /**
     * @brief Analizador léxico con el que se encadenará
     * 
     */
    struct Lexer * lexer;
};

/**
 * @brief Método que lee los diversos símbolos de un flujo de datos
 * 
 * Este método devuelve en un vector de referencias los símbolos 
 * leídos de un flujo de datos. Precondición: el flujo de datos 
 * debe estar abierto, debe existir memoria suficiente para leer 
 * dos líneas del flujo y el vector resultado. Poscondición: se 
 * leerá del flujo de datos, se solicitará memoria para leer dos
 * líneas del flujo de datos, podría solicitarse memoria para el 
 * vector resultado. La última posición del vector es nula.
 * 
 * @param self Autoreferencia al objeto
 * @param stream Flujo de datos del que se leerán los símbolos
 * @return Vector donde se alojarán los símbolos
 * @memberof Lexer
 */
char * * Lexer_read(struct Lexer * self, FILE * stream);

/**
 * @brief Constructor del analizador lexicográfico
 * 
 * @return una referencia al objeto creado
 * @memberof Lexer
 */
struct Lexer * Lexer_create(void);

/**
 * @brief Método que lee un comando del flujo de datos
 * 
 * Este método devuelve un árbol sintáctico abstracto que se 
 * corresponde con un comando leído del flujo de datos. 
 * Precondición: el flujo de datos debe estar abierto, debe 
 * existir memoria suficiente para crear el árbol sintáctico. 
 * Poscondición: se leerá del flujo de datos, se solicitará 
 * memoria para el árbol sintáctico.
 * 
 * @param self Autoreferencia al objeto
 * @param stream Flujo de datos del que se leerán los comandos
 * @return Árbol sintáctico abstracto correspondiente al comando 
 */
struct Expression * Parser_read(struct Parser * self, FILE * stream);

/**
 * @brief Constructor del analizador sintáctico
 * 
 * @param lexer Analizador léxico con el que se encadenará 
 * @return una referencia al objeto creado
 * @memberof Parser
 */
struct Parser * Parser_create(struct Lexer * lexer);
#endif