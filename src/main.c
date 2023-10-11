#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "settings.h"
#include "FileWriter.h"
#include "CommandParser.h"
#include "ValidFlags.h"

// TODO : replace system() with mkdir() when possible to remove at least some of the stupidity behind this idea.
int createProject(const char* project_name, const char* file_extension);
void printHelpMessage();
int interactiveMode();

int main(int argc, char const *argv[])
{    
    int state;
    if (argc == 1)
    {
        state = interactiveMode();
        return state;
    }  

    CommandFlags flags = getFlagsFromCommand(argc, argv);
    if (flags.size < 0) // Error handling
        return 1;

    /* for (int i = 0; i < flags.size; i++)
    {
        printf("Flag : [%s], argument : [%s]\n", flags.params[i].flag, flags.params[i].value);
    } */
    
    CommandParams params = processFlags(flags);
    if(params.help_asked)
    {
        printHelpMessage();
        return 0;
    }

    printf("Name : %s, Language : %s\n", params.project_name, params.project_language);
    


    createProject(params.project_name, params.project_language);

    return 0;
}

/*---Other functions---*/

/* Returns 0 if the project was successfully created and 1 otherwise */
int createProject(const char* project_name, const char* file_extension)
{
    char path_to_project[2*STRING_MAX_SIZE];
    char temp_path[2*STRING_MAX_SIZE];
    int status = 0;

    strcpy(path_to_project, project_name);

    // Create the project folder
    mkdir(path_to_project, 0700);

    // Add things inside the project folder depending on language
    if (!strcmp(file_extension, "c"))
    {
        /* Creation of src, include, build folders and main.c */
        // directories
        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/src");
        mkdir(temp_path, 0700);

        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/include");
        mkdir(temp_path, 0700);

        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/build");
        mkdir(temp_path, 0700);

        // main.c
        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/src");
        status = c_writeMain(temp_path);
        if(status) return 1;

        // makefile
        strcpy(temp_path, path_to_project);
        status = c_writeMakefile(temp_path);
        if(status) return 1;

        // readme
         strcpy(temp_path, path_to_project);
        status = c_writeReadme(temp_path);
        if(status) return 1;

        return 0;
    }
    if(!strcmp(file_extension, "cpp"))
    {
        /* Creation of src, include, build folders and main.c */
        // directories
        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/src");
        mkdir(temp_path, 0700);
        
        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/include");
        mkdir(temp_path, 0700);

        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/build");
        mkdir(temp_path, 0700);

        // main.cpp
        strcpy(temp_path, path_to_project);
        strcat(temp_path, "/src");
        status = cpp_writeMain(temp_path);
        if(status) return 1;

        // makefile
        strcpy(temp_path, path_to_project);
        status = cpp_writeMakefile(temp_path);
        if(status) return 1;

        // readme
        strcpy(temp_path, path_to_project);
        status = cpp_writeReadme(temp_path);
        if(status) return 1;

        return 0;
    }

    printf("Error : Invalid project type. \n");
    printf("Valid types : c, cpp\n");
    return 1;
}

void printHelpMessage()
{
    printf("\n---Help message---\n");
    printf("This program can simply be executed without any arguments in order to be used.\n");
    printf("However, it may be faster to use them.\n");
    printf("Here is a list of valid flags. \n\n");

    printf("--help                                      -> show this message\n\n");

    printf("-l [language] (same as --lang, --language)  -> choose the project language\n");
    printf("                                               valid languages : c, cpp\n\n");

    printf("-n [name] (same as --name)                  -> choose the name of the project directory (could be a path to the directory)\n\n");

   /*  printf("-p [path] (same as --path)                  -> path to the project directory\n\n"); */

}

int interactiveMode()
{
    char path_to_project[256];
    char language[32];
    int state;

    printf("Name / path to the project : ");
    if (!fgets(path_to_project, 256, stdin))
    {
        return 1;
    }
    path_to_project[strcspn(path_to_project, "\n")] = 0;

    printf("Language (c/cpp) : ");
    if (!fgets(language, 32, stdin))
    {
        return 1;
    }
    language[strcspn(language, "\n")] = 0;

    state = createProject(path_to_project, language);
    return state;
}