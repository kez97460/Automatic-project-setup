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
int createProject(const char* project_name, const char* file_extension, const char* path);
void printHelpMessage();

int main(int argc, char const *argv[])
{    
    CommandFlags flags = getFlagsFromCommand(argc, argv);
    for (int i = 0; i < flags.size; i++)
    {
        printf("Flag : [%s], argument : [%s]\n", flags.params[i].flag, flags.params[i].value);
    }
    
    CommandParams params = processFlags(flags);

    printf("Name : %s, Path : %s, Language : %s\n", params.project_name, params.path_to_project, params.project_language);
    
    return 0;
}

/*---Other functions---*/

/* Returns 0 if the project was successfully created and 1 otherwise */
int createProject(const char* project_name, const char* file_extension, const char* path)
{
    char command[3*STRING_MAX_SIZE];
    char path_to_project[2*STRING_MAX_SIZE];
    char temp_path[2*STRING_MAX_SIZE];
    int status = 0;

    /* Setup path_to_project */
    if(!strcmp(path, ""))
        strcpy(path_to_project, "./");
    else
    {
        strcpy(path_to_project, path);
        if(path_to_project[strlen(path_to_project) - 1] != '/')
            strcat(path_to_project, "/");
    }
    strcat(path_to_project, project_name);

    // Create the project folder
    sprintf(command, "mkdir -v %s", path_to_project);
    system(command);

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
    printf("This program can simply be executed without any arguments in order to be used.\n");
    printf("However, it may be faster to use them.\n");
    printf("Here is a list of valid flags. \n\n");

    printf("--help \tshow this message\n\n");

    printf("-l [language] (same as --lang, --language) \tchoose the project language\nValid languages : c, cpp\n\n");

    printf("-n [name] (same as --name) \tchoose the name of the project directory\n\n");

    printf("-p [path] (same as --path) \tpath to the project directory\n\n");

}