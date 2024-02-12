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
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (c == str[i])
            return true;
    }
    return false;
}

/* Flag processing */
void processFlag_language(CommandParams* params, char* param_value);
void processFlag_name(CommandParams* params, char* param_value);

CommandParams processFlags(CommandFlags flags)
{
    CommandParams params = (CommandParams) {false, "New_project", ""};

    for (int i = 0; i < flags.size; i++)
    {
        const char* valid_l_flags[] = {"-l", "--lang", "--language"};
        // const char* valid_p_flags[] = {"-p", "--path"};
        const char* valid_n_flags[] = {"-n", "--name"};

        if (isStringIn(flags.params[i].flag, valid_l_flags, 3))
            processFlag_language(&params, flags.params[i].value);

       /*  else if (isStringIn(flags.params[i].flag, valid_p_flags, 2))
            processFlag_path(&params, flags.params[i].value); */

        else if (isStringIn(flags.params[i].flag, valid_n_flags, 2))
            processFlag_name(&params, flags.params[i].value);

        else if (!strcmp(flags.params[i].flag, "--help"))
            params.help_asked = true;

        else // Invalid flag
        {
            printf("[%s] : invalid flag.\n", flags.params[i].flag);
            params = (CommandParams) {true, "error", "error"};
            return params;
        }
    }

    return params;
}

/* processFlag type functions */

void processFlag_language(CommandParams* params, char* param_value)
{
    const char* valid_c_values[] = {"c", "C"};
    const char* valid_cpp_values[] = {"cpp", "C++", "c++"};

    if(isStringIn(param_value, valid_c_values, 2)) // C
    {
        strcpy(params->project_language, "c"); 
        return;
    }
    if(isStringIn(param_value, valid_cpp_values, 3)) // C++
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
    const char valid_chars[] = {'/', '.', '-', '_'};

    for (size_t i = 0; i < strlen(param_value); i++)
    {
        if(!isalnum(param_value[i]) && !isCharIn(param_value[i], valid_chars))
        {
            strcpy(params->project_name, "error");
            printf("Error : [%s] - invalid name (contains forbidden characters)\n", param_value);
            return;
        }        
    }
    strcpy(params->project_name, param_value);
}