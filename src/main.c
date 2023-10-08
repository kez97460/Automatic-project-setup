#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "settings.h"
#include "FileWriter.h"

int createProject(const char* project_name, const char* file_extension, const char* path);

int main(int argc, char const *argv[])
{
    int status;
    char project_name[STRING_MAX_SIZE / 4] = "";
    char file_extension[STRING_MAX_SIZE / 4] = "";
    char project_path[STRING_MAX_SIZE / 4] = "";

    // Verify the size of the arguments (we don't need buffer overflows)
    int charcount = 0;
    for (int i = 0; i < argc; i++)
    {
        charcount += strlen(argv[i]);
    }
    if(charcount > STRING_MAX_SIZE / 4)
    {
        printf("Why are these arguments so f*cking LONG ?\n");
        return 1;
    }
    
    // Do different things based on number of args

    if(argc == 1)
    {
        printf("Incorrect use. There are 2 ways to use this program : \n");
        printf("1. '%s -interactive' or '%s -i' - open an interactive menu \n", argv[0], argv[0]);
        printf("2. '%s [project_name] [language_file_extension] [path(optional)]' \n\n", argv[0]);
        printf("Currently supported languages : \n");
        printf("- C (file extension : c), \n");
        printf("- C++ (file extension : cpp), \n");
        // printf("- SystemVerilog (file extension : sv), WIP and simple projects only \n");

        exit(EXIT_FAILURE);
    }

    if(argc == 2 && (!strcmp(argv[1], "-i") || !strcmp(argv[1], "-interactive")))
    {
        printf("Project name : ");
        if (fgets(project_name, 40, stdin))
        {
            project_name[strcspn(project_name, "\n")] = 0;
        }
        printf("File extension (c/cpp) : ");
        if (fgets(file_extension, 40, stdin))
        {
            file_extension[strcspn(file_extension, "\n")] = 0;
        }
        printf("Path to the project folder : ");
        if (fgets(project_path, 40, stdin))
        {
            project_path[strcspn(project_path, "\n")] = 0;
        }
        status = createProject(project_name, file_extension, project_path);
    }
        
    if(argc == 3)
        status = createProject(argv[1], argv[2], "");

    if(argc == 4)
        status = createProject(argv[1], argv[2], argv[3]);
    
    if(status == 0) printf("Setup finished.\n");
    else printf("A problem accured, could not create project\n");
    return status;
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
        sprintf(command, "mkdir -v %s/src", path_to_project);
        system(command);
        sprintf(command, "mkdir -v %s/include", path_to_project);
        system(command);
        sprintf(command, "mkdir -v %s/build", path_to_project);
        system(command);

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
        sprintf(command, "mkdir -v %s/src", path_to_project);
        system(command);
        sprintf(command, "mkdir -v %s/include", path_to_project);
        system(command);
        sprintf(command, "mkdir -v %s/build", path_to_project);
        system(command);

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