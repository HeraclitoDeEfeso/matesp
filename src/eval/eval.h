#ifndef EVAL_H
#define EVAL_H
/**
 * @file eval.h
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Interfaces del módulo eval de la aplicación laplace
 * @version 0.1
 * @date 2020-06-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include "../expr/expr.h"

/**
 * @brief Valor de condición inicial y(0) por defecto en cero
 * 
 */
#define INIT_DEFAULT 0
/**
 * @brief Distancia por defecto entre los puntos del conjunto de datos
 * 
 */
#define STEP_DEFAULT 1
/**
 * @brief Puntos a generar por defecto para el conjunto de datos
 * 
 */
#define POINTS_DEFAULT 20

/**
 * @brief Tabla virtual de la interfaz Function
 * 
 */
struct Function
{
    /**
     * @brief Método que devuelve el resultado de la función en un punto
     * 
     * @param preimagen Valor del que se calculará la imagen
     * @result punto flotante con el resultado de la función
     * @memberof Function
     * 
     */
    float (*image)(struct Function * self, float preimage);
    /**
     * @brief Representación de la función en expresión matemática
     *
     * Éste método devuelve una representación en caracteres de la 
     * función. Precondición: el flujo de salida ya ha sido abierto
     * para escritura. Poscondición: se escribirá en el flujo de 
     * datos de salida.
     *  
     * @param stream Flujo de salida donde se devolverá la representación
     * @memberof Function
     * 
     */
    void (*repr)(struct Function * self, FILE * stream);
    /**
     * @brief Destructor de la clase que implemente la funcion
     * 
     * @memberof Function
     * 
     */
    void (*destroy)(struct Function * self);
};

/**
 * @brief TAD correspondiente al evaluador
 * 
 * La clase Evaluator es la encargada de mantener el contexto
 * de evaluación y modificarlo de acuerdo a las expresiones
 * que se le proveen. Se define como abstracta poque es
 * necesario implementar en la clase concreta el método 
 * encargado de obtener la solución para una ecuación 
 * diferencial y su condición inicial.
 * 
 */
struct Evaluator
{
    /**
     * @brief Solución a la ecuación integral actualmente definida 
     * 
     */
    struct Function * function;
    /**
     * @brief Condición inicial correspondiente a y(0)
     * 
     */
    float init;
};

/**
 * @brief Despachador del método virtual image
 * 
 * @memberof Function
 * 
 */
float Function_image(struct Function * self, float preimage);

/**
 * @brief Despachador del método virtual repr
 * 
 * @memberof Function
 * 
 */
void Function_repr(struct Function * self, FILE * stream);

/**
 * @brief Despachador del destructor
 * 
 * @memberof Function
 * 
 */
void Function_destroy(struct Function * self);

/**
 * @brief Método abstracto solucionador de ecuaciones
 * 
 * Método abstracto que deberá implementar la clase concreta
 * del evaluador. Devolverá la solución siempre que sean
 * válidos tanto la ecuación como las condiciones iniciales.
 * Precondición: el evaluador y la expresión deben haber
 * sido creadas, debe haber memoria suficiente para crear
 * la solución. Poscondición: es posible que se solicite
 * memoria para crear la solución
 * 
 * @param self Autoreferencia al objeto
 * @param expression Expresión con la definición de la ecuación
 * @result valor baleano a la proposición "se obtuvo solución"
 * @memberof Evaluator
 * 
 */
extern int Evaluator_set_function(struct Evaluator * self, struct Expression * expression);

/**
 * @brief Método que evalúa las expresiones 
 * 
 * Método que evalúa las expresiones y modifica el contexto
 * de evaluación de forma acorde. Precondición: el evaluador 
 * y la expresión deben haber sido creadas, debe haber memoria 
 * suficiente para crear una la solución, el flujo de datos de 
 * salida debe haber sido abierto para escritura. Poscondición: 
 * es posible que se solicite memoria para crear la solución,
 * es posible que se modifiquen los atributos del evaluador 
 * que contienen el contexto de evaluación, es posible que se
 * escriba en el flujo de datos de salida.
 * 
 * @param self Autoreferencia al objeto
 * @param expression Expresión correspondiente a los comandos
 * @param stream Flujo de datos de salida
 * @result valor baleano a la proposición "se produjo un error"
 * @memberof Evaluator
 * 
 */
int Evaluator_eval(struct Evaluator * self, struct Expression * expression, FILE * stream);
#endif