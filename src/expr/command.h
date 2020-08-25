#ifndef COMMAND_H
#define COMMAND_H
/**
 * @file command.h
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Interfaz de la clase Command
 * @version 0.1
 * @date 2020-06-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "expr.h"

/**
 * @brief TAD del comando ingresado en la expresión
 * 
 * Tipo abstracto de dato que modela el comando que se ha utilizado
 * en la expresion.
 * 
 */
struct Command
{
    /**
     * @brief Tipo de comando ingresado
     * 
     */
    enum Symbol symbol;
    /**
     * @brief Representación en caracteres del comando
     * 
     */
    char * repr;
    /**
     * @brief Cantidad máxima de argumentos que acepta el comando
     * 
     */
    int argc;
    /**
     * @brief Enlace al siguiente comando en la cadena
     * 
     */
    struct Command * next;
};
#endif
