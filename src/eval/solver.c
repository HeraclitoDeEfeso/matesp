/**
 * @file solver.c
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Clases concretas de interfaces del módulo eval
 * @version 0.1
 * @date 2020-06-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "solver.h"
#include <stdlib.h>
#include <math.h>

struct Function * (*CONSTRUCTORS[])(struct Evaluator * evaluator, 
                                    struct Expression * expression) = {
    &Solution1_create, &Solution2_create, &Solution3_create, 
    &Solution4_create, &Solution1_create, &Solution6_create,
    &Solution7_create, &Solution8_create
};

struct Evaluator * StaticSolver_create()
{
    struct Evaluator * evaluator = malloc(sizeof(struct Evaluator));
    evaluator->function = NULL;
    evaluator->init = INIT_DEFAULT;
    return evaluator;
};

int Evaluator_set_function(struct Evaluator * self, struct Expression * expression)
{
    int success = 0;
    int indice = (expression->args[0] != 0) * 4 
                    + (expression->args[1] != 0) * 2 
                    + (expression->args[2] != 0);
    struct Function * function = CONSTRUCTORS[indice](self, expression);
    if ((success = function != NULL))
    {
        if (self->function)
        {
            Function_destroy(self->function);
        }
        self->function = function;
    }
    return success;
};

struct Function * Solution1_create(struct Evaluator * evaluator, struct Expression * expression)
{
    return NULL;
}

struct Function * Solution2_create(struct Evaluator * evaluator, struct Expression * expression)
{
    struct Solution * solution = malloc(sizeof(struct Solution));
    solution->vtable.image = &Solution_image;
    solution->vtable.repr = &Solution2_repr;
    solution->vtable.destroy = &Solution_destroy;
    solution->clousure[0] = evaluator->init;
    solution->clousure[1] = 0;
    solution->clousure[2] = 0;
    solution->clousure[3] = 0;
    return &solution->vtable;
};

struct Function * Solution3_create(struct Evaluator * evaluator, struct Expression * expression)
{
    struct Function * function = NULL;
    if (evaluator->init == 0)
    {
        struct Solution * solution = malloc(sizeof(struct Solution));
        solution->vtable.image = &Solution_image;
        solution->vtable.repr = &Solution3_repr;
        solution->vtable.destroy = &Solution_destroy;
        solution->clousure[0] = 0;
        solution->clousure[1] = 0;
        solution->clousure[2] = 0;
        solution->clousure[3] = 0;
        function = &solution->vtable;
    }
    return function;
}

struct Function * Solution4_create(struct Evaluator * evaluator, struct Expression * expression)
{
    struct Solution * solution = malloc(sizeof(struct Solution));
    solution->vtable.image = &Solution_image;
    solution->vtable.repr = &Solution4_repr;
    solution->vtable.destroy = &Solution_destroy;
    solution->clousure[0] = 0;
    solution->clousure[1] = 0;
    solution->clousure[2] = evaluator->init;
    solution->clousure[3] = - expression->args[1]/expression->args[2];
    return &solution->vtable;
};

struct Function * Solution6_create(struct Evaluator * evaluator, struct Expression * expression)
{
    struct Solution * solution = malloc(sizeof(struct Solution));
    solution->vtable.image = &Solution_image;
    solution->vtable.repr = &Solution6_repr;    
    solution->vtable.destroy = &Solution_destroy;
    solution->clousure[0] = evaluator->init;
    solution->clousure[1] = - expression->args[0]/expression->args[2];
    solution->clousure[2] = 0;
    solution->clousure[3] = 0;
    return &solution->vtable;
}

struct Function * Solution7_create(struct Evaluator * evaluator, struct Expression * expression)
{
    struct Function * function = NULL;
    if (evaluator->init == - expression->args[0]/expression->args[1])
    {
        struct Solution * solution = malloc(sizeof(struct Solution));
        solution->vtable.image = &Solution_image;
        solution->vtable.repr = &Solution2_repr;
        solution->vtable.destroy = &Solution_destroy;
        solution->clousure[0] = evaluator->init;
        solution->clousure[1] = 0;
        solution->clousure[2] = 0;
        solution->clousure[3] = 0;
        function = &solution->vtable;
    }
    return function;
}

struct Function * Solution8_create(struct Evaluator * evaluator, struct Expression * expression)
{
    struct Solution * solution = malloc(sizeof(struct Solution));
    solution->vtable.image = &Solution_image;
    solution->vtable.repr = &Solution8_repr;
    solution->vtable.destroy = &Solution_destroy;
    solution->clousure[0] = - expression->args[0]/expression->args[1];
    solution->clousure[1] = 0;
    solution->clousure[2] = evaluator->init + expression->args[0]/expression->args[1];
    solution->clousure[3] = - expression->args[1]/expression->args[2];
    return &solution->vtable;
};

float Solution_image(struct Function * self, float preimage)
{
    struct Solution * object = (struct Solution *) self;
    return object->clousure[0] + object->clousure[1] * preimage 
            + object->clousure[2] * expf(object->clousure[3] * preimage);
}

void Solution2_repr(struct Function * self, FILE * stream)
{
    fprintf(stdout, "# y = %f\n", ((struct Solution *)self)->clousure[0]);
};

void Solution3_repr(struct Function * self, FILE * stream)
{
    fprintf(stdout, "# y = 0\n");
};

void Solution4_repr(struct Function * self, FILE * stream)
{
    struct Solution * object = (struct Solution *) self;
    fprintf(stdout, "# y = %f * exp( %f * x )\n", 
            object->clousure[2], object->clousure[3]);
};

void Solution6_repr(struct Function * self, FILE * stream)
{
    struct Solution * object = (struct Solution *) self;
    fprintf(stdout, "# y = (%f) + (%f) * x\n", 
            object->clousure[0], object->clousure[1]);
}

void Solution8_repr(struct Function * self, FILE * stream)
{
    struct Solution * object = (struct Solution *) self;
    fprintf(stdout, "# y = %f * exp( %f * x ) + (%f)\n", 
            object->clousure[2], object->clousure[3], object->clousure[0]);

};

void Solution_destroy(struct Function * self)
{
    free((struct Solution *)self);
};