#include "CommandParser.h"

/* A string is a flag if is consists of a single word (no spaces) and starts with a '-' */
bool isFlag(const char* string)
{
    if(strlen(string) == 0)
        return false;
    if(string[0] != '-')
        return false;
    for (size_t i = 0; i < strlen(string); i++)
    {
        switch (string[i])
        {
        case ' ':
        case '\n':
        case '\t':
            return false;
            break;
        }
    }
    return true;
}

CommandFlags getFlagsFromCommand(int argc, const char* argv[])
{
    CommandFlags res;
    res.params = (Param*) malloc((argc-1) * sizeof(Param));
    bool waiting_for_value = false;
    int param_index = 0;

    Param temp = {"", ""};

    // Ignore first argument as it is the executed command's name
    for (int i = 1; i < argc; i++)
    {
        if(!waiting_for_value && !isFlag(argv[i])) // no current flag and we get a value : error
        {
            printf("Invalid command \n");
            return (CommandFlags){NULL, -1};
        }

        if(isFlag(argv[i])) // new flag detected : add a parameter
        {
            if (waiting_for_value)
            {
                // printf("Added flag [%s]\n", temp.flag);
                res.params[param_index] = temp;
                param_index++;
            }
            waiting_for_value = true;
            strcpy(temp.flag, argv[i]);
            strcpy(temp.value, "");

        }
        else
        {
            strcpy(temp.value, argv[i]);
            waiting_for_value = false;

            // printf("Added flag [%s] with value [%s]\n", temp.flag, temp.value);
            res.params[param_index] = temp;
            param_index++;
            strcpy(temp.flag, "");
            strcpy(temp.value, "");
        }
    }
    
    // Add last flag if it has no value
    if (strcmp(temp.flag, "")) // Flag exists
    {
        // printf("Added flag [%s]\n", temp.flag);
        res.params[param_index] = temp;
        param_index++;
    }

    res.size = param_index;
    return res;
}
