#ifndef VALIDFLAGS_H
#define VALIDFLAGS_H

#include "settings.h"
#include "CommandParser.h"

// All parameters of the command, modified by flags and their values
typedef struct CommandParams
{
    bool help_asked;
    char project_name[MAX_ARG_SIZE];
    char path_to_project[MAX_ARG_SIZE];
    char project_language[MAX_ARG_SIZE];
} CommandParams;

const CommandParams DEFAULT_PARAMS = (CommandParams) {false, "New_project", "", ""};
const CommandParams HELP_PARAMS = (CommandParams) {true, "error", "", "error"};

CommandParams processFlags(CommandFlags flags);

#endif /* VALIDFLAGS_H */
