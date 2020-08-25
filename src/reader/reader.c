/**
 * @file reader.c
 * @author Alejandro Araneda (eloscurodeefeso@gmail.com)
 * @brief Implementación del módulo reader de la aplicación laplace
 * @version 0.1
 * @date 2020-06-22
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"

char * * Lexer_read(struct Lexer * self, FILE * stream)
{
    char * * symbols = NULL;
    int symbolc = 0;
    char * token = NULL;
    static char buffer[MAX_LINE_SIZE];
    static char copy[MAX_LINE_SIZE];
    if (fgets(buffer, MAX_LINE_SIZE, stream)) 
    {
        memcpy(copy, buffer, MAX_LINE_SIZE);
        self->lines++;
        token = strtok(copy, COMMAND_DELIM);
        while(token) 
        {
            symbolc++;
            token = strtok(NULL, COMMAND_DELIM);
        };
        if(symbolc)
        {
            symbols = calloc(symbolc + 1, sizeof(char *));
            symbolc = 0;
            token = strtok(buffer, COMMAND_DELIM);
            while(token) 
            {
                symbols[symbolc] = token;
                symbolc++;
                token = strtok(NULL, COMMAND_DELIM);
            };
        }
    }
    return symbols;
};

struct Lexer * Lexer_create(void)
{
    struct Lexer * self = malloc(sizeof(struct Lexer));
    (* self).lines = 0;
    return self;
};

struct Expression * Parser_read(struct Parser * self, FILE * stream)
{
    struct Expression * expression = NULL;
    char * * symbols = Lexer_read(self->lexer, stream);
    struct Command * command = NULL;
    if (symbols)
    {
        command = Command_get_command(COMMANDS, symbols[0]);
        if (!command)
        {
            fprintf(stderr, 
                    "# Unknown command at line %i.\n", 
                    self->lexer->lines);
        }
        else if (!(expression = Command_get_expression(command, &symbols[1])))
        {
            fprintf(stderr, "# Syntax error at line %i.\n", self->lexer->lines);
        }
    }
    return expression;
};

struct Parser * Parser_create(struct Lexer * lexer)
{
    struct Parser * self = malloc(sizeof(struct Parser));
    (* self).lexer = lexer;
    return self;
};