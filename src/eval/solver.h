#ifndef SOLVER_H
#define SOLVER_H
/**
 * @file solver.h
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Clases concretas de interfaces del módulo eval
 * @version 0.1
 * @date 2020-06-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "eval.h"

/**
 * @brief TAD de las clases concretas para la interfaz Function
 * 
 * Tipo abstracto de datos que compartiran las clases concretas
 * que implementarán la interfaz Function.
 * 
 */
struct Solution
{
    /**
     * @brief Tabla virtual de las funciones que implementan
     *        la interfaz Function
     * 
     */
    struct Function vtable;
    /**
     * @brief Vector con las clausuras para evaluar la solución
     * 
     */
    float clousure[4];
};

/**
 * @brief Constructor de la clase concreta StaticSolver
 * 
 * Constructor de la clase concreta StaticSolver que implementa
 * la clase abstracta Evaluator y su método abstracto 
 * Evaluator_set_function.
 * 
 * @memberof StaticSolver
 * 
 */
struct Evaluator * StaticSolver_create();

/**
 * @brief Constructor de la Solución 1 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "0y' + 0y + 0 = 0" cuya
 * solución más sencilla es "y = d" donde "d" es la condición inicial "y(0)" 
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial 
 * @memberof Solution1
 * 
 */
struct Function * Solution1_create(struct Evaluator * evaluator, struct Expression * expression);

/**
 * @brief Constructor de la Solución 2 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "ay' + 0y + 0 = 0" donde "a" es
 * distinto de cero y cuya solución es "y = d" donde "d" es la condición
 * inicial "y(0)".
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial 
 * @memberof Solution2
 * 
 */
struct Function * Solution2_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Constructor de la Solución 3 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "0y' + by + 0 = 0" donde "b"
 * es distinto de cero y cuya solución es "y = 0". Es válida siempre
 * que la condición inicial sea "y(0) = 0". 
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial. Puede ser nula.
 * @memberof Solution3
 * 
 */
struct Function * Solution3_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Constructor de la Solución 4 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "ay' + by + 0 = 0" donde "a" y "b"
 * son distintos de cero y cuya solución es "y = d*exp(-b/a*x)" donde "d"
 * es la condición inicial "y(0)". 
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial 
 * @memberof Solution4
 * 
 */
struct Function * Solution4_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Constructor de la Solución 5 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "0y' + 0y + c = 0" donde "c" es
 * distinto de cero. Es evidente que no es una ecuación válida ni
 * tiene solución.
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result El resultado es nulo 
 * @memberof Solution5
 * 
 */
struct Function * Solution5_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Constructor de la Solución 6 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "ay' + 0y + c = 0" cuya
 * solución más sencilla es "y = d - c/a*x" donde "d" es la condición 
 * inicial "y(0)".
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial 
 * @memberof Solution6
 * 
 */
struct Function * Solution6_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Constructor de la Solución 7 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "0y' + by + c = 0" donde "b" y "c"
 * son distintos de cero y cuya solución es "y = -c/b" siempre que la 
 * condición inicial sea "y(0) = -c/b" 
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial. Puede ser nula.
 * @memberof Solution7
 * 
 */
struct Function * Solution7_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Constructor de la Solución 8 de las ecuaciones diferenciales
 * 
 * Corresponde a la ecuación del tipo "ay' + by + c = 0" cuya
 * solución más es "y = (d + c/b) * exp(-b/a * x) - c/b" donde "d" es 
 * la condición inicial "y(0)". 
 * 
 * @param evaluator Clase con el contexto de evaluación
 * @param expression Expresión de la ecuación diferencial
 * @result Función solución a la ecuación diferencial 
 * @memberof Solution8
 * 
 */
struct Function * Solution8_create(struct Evaluator * evaluator, struct Expression * Expression);

/**
 * @brief Implementación del método para obtener el resultado
 * 
 * Método concreto que implementa la interfaz Function para obtener
 * el resultado numérico de la ecuación diferencial. Se unifica una
 * única expresión matemática para todas las soluciones por lo que
 * todas lo comparten en su tabla virtual.
 * 
 * @memberof Solution
 * 
 */
float Solution_image(struct Function * self, float preimage);

/**
 * @brief Destructor de la clases Solution
 *  
 * @memberof Solution
 * 
 */
void Solution_destroy(struct Function * self);

/**
 * @brief Representación matemática de la solución 2
 * 
 * Corresponde a "y = d" donde "d" es la condición inicial "y(0)".
 */
void Solution2_repr(struct Function * self, FILE * stream);

/**
 * @brief Representación matemática de la solución 3
 * 
 * Corresponde a "y = 0".
 * 
 */
void Solution3_repr(struct Function * self, FILE * stream);

/**
 * @brief Representación matemática de la solución 4
 * 
 * Corresponde a "y = d * exp(-b/a * x)" donde "d"
 * es la condición inicial "y(0)" y "a" y "b" son
 * respectivamente el coeficiente de la derivada y 
 * de la función. 
 * 
 */
void Solution4_repr(struct Function * self, FILE * stream);

/**
 * @brief Representación matemática de la solución 6
 * 
 * Corresponde a  "y = d - c/a*x" donde "d" es la condición 
 * inicial "y(0)", "c" es el término independiente y "a" el
 * coeficiente de la derivada.
 * 
 */
void Solution6_repr(struct Function * self, FILE * stream);

/**
 * @brief Representación matemática de la solución 8
 * 
 * Corresponde a "y = (d + c/b) * exp(-b/a * x) - c/b" donde 
 * "d" es la condición inicial "y(0)".
 *  
 */
void Solution8_repr(struct Function * self, FILE * stream);
#endif