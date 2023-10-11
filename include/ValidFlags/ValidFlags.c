#include "ValidFlags.h"

/* Compare str to multiple other strings, return true if any comparison is true. Segfaults if size is incorrect */
bool isStringIn(const char* str, const char* array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!strcmp(str, array[i]))
            return true;
    }
    return false;
}

bool isCharIn(const char c, const char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (c == str[i])
            return true;
    }
    return false;
}

CommandParams processFlags(CommandFlags flags)
{
    CommandParams params = DEFAULT_PARAMS;
    for (int i = 0; i < flags.size; i++)
    {
        if (isStringIn(flags.params[i].flag, (char**){"-l", "--lang", "--language"}, 3))
            processFlag_language(&params, flags.params[i].value);

        else if (isStringIn(flags.params[i].flag, (char**){"-p", "--path"}, 2))
            processFlag_path(&params, flags.params[i].value);
        
        else if (isStringIn(flags.params[i].flag, (char**){"-n", "--name"}, 2))
            processFlag_name(&params, flags.params[i].value);

        else if (isStringIn(flags.params[i].flag, (char**){"--help"}, 1))
            params.help_asked = true;

        else // Invalid flag
        {
            printf("[%s] : invalid flag. List of valid flags : \n", flags.params[i].flag);
            params = HELP_PARAMS;
            return params;
        }
    }

    return params;
}

/* processFlag type functions */

void processFlag_language(CommandParams* params, char* param_value)
{
    if(isStringIn(param_value, (char**){"c", "C"}, 2)) // C
    {
        strcpy(params->project_language, "c"); 
        return;
    }
    if(isStringIn(param_value, (char**){"cpp", "C++", "c++"}, 3)) // C++
    {
        strcpy(params->project_language, "cpp"); 
        return;
    }
    
    // Iinvalid values : error
    strcpy(params->project_language, "error"); 
    return;
}

void processFlag_name(CommandParams* params, char* param_value)
{
    for (size_t i = 0; i < strlen(param_value); i++)
    {
        if(!isalnum(param_value[i]) && !isCharIn(param_value[i], (char*){'-', '_', ' '}))
        {
            strcpy(params->project_name, "error");
            printf("Error : [%s] - invalid name (contains forbidden characters)\n", param_value);
            return;
        }        
    }
    strcpy(params->project_name, param_value);
}

void processFlag_path(CommandParams* params, char* param_value)
{
    for (size_t i = 0; i < strlen(param_value); i++)
    {
        if(!isalnum(param_value[i]) && !isCharIn(param_value[i], (char*){'/', '.', '-', '_', ' '}))
        {
            strcpy(params->path_to_project, "error");
            printf("Error : [%s] - invalid path (contains forbidden characters)\n", param_value);
            return;
        }        
    }
    strcpy(params->path_to_project, param_value);
}