/**
 * @file expr.c
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Implementación de las clases Expression y Command
 * @version 0.1
 * @date 2020-06-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "expr.h"
#include "command.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct Command COMMANDS_BASE[] = {
    {INIT, "init", 1, COMMANDS_BASE + 1},
    {STEP, "step", 3, COMMANDS_BASE + 2},
    {REPR, "repr", 0, COMMANDS_BASE + 3},
    {COEF, "coef", 3, NULL}
};

struct Command * COMMANDS = COMMANDS_BASE;

struct Command * Command_get_command(struct Command * self, char * repr)
{
    return (self && strcmp(self->repr, repr) != 0) ? 
             Command_get_command(self->next, repr) : 
                                              self ;
};

struct Expression * Command_get_expression(struct Command * self, char * * args)
{
    struct Expression * expression = NULL;
    int count = 0;
    while (args[count]) count++;
    if (count > self->argc)
    {
        fprintf(stderr, "# Max args for command %s is %i.\n", self->repr, self->argc);
    }
    else
    {
        expression = Expression_create(self, self->argc);
        if (Expression_curry(expression, args) != count)
        {
            Expression_destroy(expression);
            expression = NULL;
        }
    }
    return expression;
};

struct Expression * Expression_create(struct Command * command, int argc)
{
    struct Expression * expresion = malloc(sizeof(struct Expression));
    expresion->command = command;
    expresion->args = calloc(argc, sizeof(float));
    expresion->argc = 0;
    return expresion;
};

void Expression_destroy(struct Expression * self)
{
    if(self)
    {
        free(self->args);
        free(self);
    }
};

int Expression_curry(struct Expression * self, char * * args)
{
    int error = 0;
    while(!error && args[self->argc])
    {
        error = sscanf(args[self->argc], "%f", &self->args[self->argc]) != 1;
        if (error)
            fprintf(stderr, "# %s is not a float.\n", args[self->argc]);
        else
            self->argc++;
    };
    return self->argc;
};

enum Symbol Command_get_symbol(struct Command * self)
{
    return self->symbol;
};