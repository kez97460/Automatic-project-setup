#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <settings.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARG_SIZE 128

typedef struct Param
{
    char flag[MAX_ARG_SIZE];
    char value[MAX_ARG_SIZE];
} Param;

typedef struct CommandFlags
{
    Param* params;
    int size;
} CommandFlags;

bool isFlag(const char* string);
CommandFlags getFlagsFromCommand(int argc, const char* argv[]);





#endif /* COMMANDPARSER_H */
