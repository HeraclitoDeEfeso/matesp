/**
 * @file laplace.c
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Aplicación de la transformada de Laplace a EDO
 * @version 0.1
 * @date 2020-06-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "eval/solver.h"
#include "expr/expr.h"
#include "reader/reader.h"

int main(int argc, char const *argv[])
{
    struct Parser * parser = Parser_create(Lexer_create());
    struct Evaluator * evaluator = StaticSolver_create();
    struct Expression * expression = NULL;
    while (!feof(stdin) 
            && (expression = Parser_read(parser, stdin))
            && !Evaluator_eval(evaluator, expression, stdout));
    return 0;
}
