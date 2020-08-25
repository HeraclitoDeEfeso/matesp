/**
 * @file eval.c
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Implementacion del módulo eval de la aplicación laplace
 * @version 0.1
 * @date 2020-06-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "eval.h"
#include <stdlib.h>
#include <stdio.h>

void Function_destroy(struct Function * self)
{
    self->destroy(self);
};

int Evaluator_eval(struct Evaluator * self, struct Expression * expression, FILE * stream)
{
    int error = 0;
    float value, step, limit;
    switch (Command_get_symbol(expression->command))
    {
    case INIT:
        self->init = (expression->argc > 0)? expression->args[0] : INIT_DEFAULT;
        if (self->function)
        {
            Function_destroy(self->function);
            self->function = NULL;
        }
        break;

    case STEP:
        if ((error = self->function == NULL))
        {
            fprintf(stderr, "# Function undefined\n");
        }
        else
        {
            value = (expression->argc > 2)? expression->args[2]: 0;
            step = (expression->argc > 1)? expression->args[1]: STEP_DEFAULT;
            limit = value + 
                step * ((expression->argc > 0)? expression->args[0]: POINTS_DEFAULT);
            for (; value < limit; value += step)
            {
                fprintf(stdout, "%f %f\n", value, Function_image(self->function, value));
            }            
            fprintf(stdout, "\n");
        }
        break;

    case REPR:
        if ((error = self->function == NULL))
        {
            fprintf(stderr, "# Function undefined\n");
        }
        else
        {
            Function_repr(self->function, stdout);
        }
        break;

    case COEF:
        if ((error = !Evaluator_set_function(self, expression)))
        {
            fprintf(stderr, "# Invalid initial condition for function\n");
        };
        break;

    default:
        error = fprintf(stderr, "# Dynamic error\n");
        break;
    }
    return error;
};

float Function_image(struct Function * self, float preimage)
{
    return self->image(self, preimage);
};

void Function_repr(struct Function * self, FILE * stream)
{
    self->repr(self, stream);
};