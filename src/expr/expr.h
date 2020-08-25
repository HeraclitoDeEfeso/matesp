#ifndef EXPR_H
#define EXPR_H
/**
 * @file expr.h
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Interfaz de la clases Expression y Command
 * @version 0.1
 * @date 2020-06-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/**
 * @brief Tipos de commandos aceptados
 * 
 * Enumeración de los distintos tipos de comandos aceptados
 * 
 */
enum Symbol 
{
    INIT,
    STEP,
    REPR,
    COEF,
};

/**
 * @brief Tipo de la clase abstracta Command
 * 
 * Tipo de la clase abstracta a los efectos 
 * de su utilización, que se corresponde con
 * el TAD de implementación privada del comando. 
 * 
 */
struct Command;

/**
 * @brief Vector con todos los comandos permitidos
 * 
 */
extern struct Command * COMMANDS;

/**
 * @brief TAD del árbol de la expresión abstracta
 * 
 * Tipo abstracto de dato que modela la expresión ingresada
 * en la línea del flujo de comandos
 * 
 */
struct Expression
{
    /**
     * @brief Comando al que corresponde la expresión
     * 
     */
    struct Command * command;
    /**
     * @brief Vector con los argumentos del comando
     * 
     */
    float * args;
    /**
     * @brief Cantidad de argumentos a pasar al commando
     * 
     */
    int argc;
};

/**
 * @brief Método que selecciona el comando correcto
 * 
 * Este método recorrerá la cadena de comandos
 * hasta hallar el que corresponda con la representación. 
 * Precondición: ninguna. Poscondición: ninguna.  
 *
 * @param self Autoreferencia al objeto
 * @param repr Representación en caracteres del comando
 * @result Devuelve el comando de la representación. El
 *         resultado puede ser nulo. 
 * @memberof Command
 *
 */
struct Command * Command_get_command(struct Command * self, char * repr);

/**
 * @brief Accesor del campo del tipo de comando
 * 
 * Método que devuelve el tipo de comando. Precondición: el
 * comando fue creado. Poscondición: ninguna.  
 *
 * @param self Autoreferencia al objeto
 * @result Devuelve el tipo de comando
 * @memberof Command
 *
 */
enum Symbol Command_get_symbol(struct Command * self);

/**
 * @brief Método factoría de la expression con sus argumentos
 * 
 * Método factoria de la expresion. Precondición: debe haber
 * memoria suficiente para crear la expresion. Poscondición: 
 * es posible que se haya solicitado memoria para crear la
 * expresion.  
 *
 * @param self Autoreferencia al objeto
 * @param args Representación en caracteres de los argumentos
 * @result Devuelve una expresión correspondiente al comando 
 *         con sus argumentos. El resultado puede ser nulo. 
 * @memberof Command
 *
 */
struct Expression * Command_get_expression(struct Command * self, char * * args);

/**
 * @brief Constructor de la clase Expression
 * 
 * @param command Comando que contiene la expresion
 * @param argc Cantidad maxima de argumentos
 * @return Referencia a la nueva expresión
 * @memberof Expression
 */
struct Expression * Expression_create(struct Command * command, int argc);

/**
 * @brief Destructor de la clase Expression
 * 
 * @param self Autoreferencia al objeto
 */
void Expression_destroy(struct Expression * self);

/**
 * @brief Método que agrega los argumentos a la expresión
 * 
 * Método que agrega los argumentos al contexto de 
 * ejecución de un comando. Precondición: la expresion 
 * ha sido creada, la cantidad de argumentos no es mayor
 * que la reservada al crearla. Poscondición: se 
 * agregarán los argumentos al vector de argumentos 
 * de la expresion, puede establecer errno como EINVAL 
 * si falla la conversion.
 * 
 * @param self Autoreferencia al objeto
 * @param args Argumentos que se agregarán a la expresion
 * @return cantidad de argumentos que han sido agregados
 * @memberof Expression
 */
int Expression_curry(struct Expression * self, char * * args);

#endif
