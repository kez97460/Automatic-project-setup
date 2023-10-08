#include "FileWriter.h"

/* @param filepath Path to the folder where 'main.c' is created, without a / at the end
 * @retval Error status : should be 0 or there was an error
 */
int c_writeMain(char* filepath)
{
    strcat(filepath, "/main.c");

    FILE* main_file = fopen(filepath, "w");
    if(main_file == NULL)
    {
        printf("Unable to create the file \"main.c\"\n");
        return 1;
    }
    fprintf(main_file, "/*---Includes---*/\n\n/*---Main---*/\nint main(int argc, char const *argv[])\n{\n    \n    return 0;\n}\n");
    fclose(main_file);

    return 0;
}

/* @param filepath Path to the folder where 'Makefile' is created, without a / at the end
 * @retval Error status : should be 0 or there was an error
 */
int c_writeMakefile(char* filepath)
{
    strcat(filepath, "/Makefile");

    FILE* makefile = fopen(filepath, "w");
    if(makefile == NULL)
    {
        printf("Unable to create the file \"Makefile\"\n");
        return 1;
    }
    
    fprintf(makefile, "# Compiler, flags, executable_name\n");
    fprintf(makefile, "CC = gcc\n");
    fprintf(makefile, "CFLAGS = -g -Wall -Wextra -I$(INCLUDE_DIR) # Do not remove -I$(INCLUDE_DIR)\n");
    fprintf(makefile, "EXECUTABLE = app\n\n");

    fprintf(makefile, "# Directories\n");
    fprintf(makefile, "SRC_DIR = src\n");
    fprintf(makefile, "BUILD_DIR = build\n");
    fprintf(makefile, "INCLUDE_DIR = include\n\n");

    fprintf(makefile, "#---------------------------------------------------------------#\n");
    fprintf(makefile, "#--/ It is recommended to NOT TOUCH anything below that line /--#\n");
    fprintf(makefile, "#---------------------------------------------------------------#\n\n");

    fprintf(makefile, "# Source and object files\n");
    fprintf(makefile, "SRC_FILES = $(wildcard $(SRC_DIR)/*.c)\n");
    fprintf(makefile, "OBJ_FILES = $(patsubst $(SRC_DIR)/%%.c,$(BUILD_DIR)/%%.o,$(SRC_FILES))\n\n");

    fprintf(makefile, "# Automatically find library directories\n");
    fprintf(makefile, "LIBRARY_DIRS = $(wildcard $(INCLUDE_DIR)/*/)\n\n");

    fprintf(makefile, "# Include directories for libraries\n");
    fprintf(makefile, "LIBRARY_INCLUDES = $(foreach dir, $(LIBRARY_DIRS), -I$(dir))\n\n");

    fprintf(makefile, "# Library source files\n");
    fprintf(makefile, "LIBRARY_SRC_FILES = $(wildcard $(addsuffix *.c, $(LIBRARY_DIRS)))\n");
    fprintf(makefile, "LIBRARY_OBJ_FILES = $(patsubst %%c, $(BUILD_DIR)/%%.o, $(notdir $(LIBRARY_SRC_FILES)))\n\n");

    fprintf(makefile, "# Default target\n");
    fprintf(makefile, "all: $(EXECUTABLE)\n\n");

    fprintf(makefile, "# Compile main source files into object files\n");
    fprintf(makefile, "$(BUILD_DIR)/%%.o: $(SRC_DIR)/%%.c\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@\n\n");

    fprintf(makefile, "# Compile library source files into object files\n");
    fprintf(makefile, "$(BUILD_DIR)/%%.o: $(INCLUDE_DIR)/*/%%.c\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@\n\n");

    fprintf(makefile, "# Link object files to create the executable\n");
    fprintf(makefile, "$(EXECUTABLE): $(OBJ_FILES) $(LIBRARY_OBJ_FILES)\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) $^ -o $@\n\n");

    fprintf(makefile, "# Clean build artifacts\n");
    fprintf(makefile, "clean:\n");
    fprintf(makefile, "\trm -f $(BUILD_DIR)/*.o\n");
    fprintf(makefile, "\trm -f $(EXECUTABLE)\n");


    fclose(makefile);

    return 0;
}

/* @param filepath Path to the folder where 'README.md' is created, without a / at the end
 * @retval Error status : should be 0 or there was an error
 */
int c_writeReadme(char* filepath)
{
    strcat(filepath, "/README.md");

    FILE* readme = fopen(filepath, "w");
    if(readme == NULL)
    {
        printf("Unable to create the file \"README.md\"\n");
        return 1;
    }
    
    fprintf(readme, "# Automatically setup project\n");
    fprintf(readme, "The software that generated this project configuration can be found on [Github](https://github.com/kez97460/Automatic-project-setup).\n");
    fprintf(readme, "This README can help you understand how to properly use this setup.\n\n");

    fprintf(readme, "## Directories\n\n");

    fprintf(readme, "### build\n");
    fprintf(readme, "The Build directory will contain the object files (.o) that are generated when compiling.\n\n");

    fprintf(readme, "### include\n");
    fprintf(readme, "The include directory will contain all libraries included by the project (.h and .c files). These libraries may be put into as many independent folders as needed.\n\n");

    fprintf(readme, "### src\n");
    fprintf(readme, "The src directory contains the source files (.c), including the main function.\n\n");

    fprintf(readme, "### Example\n");
    fprintf(readme, "This structure is an example of how a project could look like :\n\n");
    fprintf(readme, "```\n");
    fprintf(readme, "|--lib\n");
    fprintf(readme, "|  |\n");
    fprintf(readme, "|  |--Bar\n");
    fprintf(readme, "|  |  |- Bar.c\n");
    fprintf(readme, "|  |  |- Bar.h\n");
    fprintf(readme, "|  |\n");
    fprintf(readme, "|  |--Foo\n");
    fprintf(readme, "|  |  |- Foo.c\n");
    fprintf(readme, "|  |  |- Foo.h\n");
    fprintf(readme, "|  \n");
    fprintf(readme, "|--src\n");
    fprintf(readme, "|  |- main.c\n");
    fprintf(readme, "```\n\n");

    fprintf(readme, "## Makefile\n");
    fprintf(readme, "This project can be compiled using the `make` command (assuming you have it installed). The object files, as well as the executable, which are generated during the compilation, may be removed at any time by using the `make clean` command.\n\n");
    fprintf(readme, "The readme can be edited to change the compiler, compilation flags or the name of the generated executable.\n");

    fclose(readme);

    return 0;
}


/* @param filepath Path to the folder where 'main.cpp' is created, without a / at the end
 * @retval Error status : should be 0 or there was an error
 */
int cpp_writeMain(char* filepath)
{
    strcat(filepath, "/main.cpp");

    FILE* main_file = fopen(filepath, "w");
    if(main_file == NULL)
    {
        printf("Unable to create the file \"main.cpp\"\n");
        return 1;
    }
    fprintf(main_file, "/*---Includes---*/\n\n/*---Main---*/\nint main(int argc, char const *argv[])\n{\n    \n    return 0;\n}\n");
    fclose(main_file);

    return 0;
}

/* @param filepath Path to the folder where 'Makefile' is created, without a / at the end
 * @retval Error status : should be 0 or there was an error
 */
int cpp_writeMakefile(char* filepath)
{
    strcat(filepath, "/Makefile");

    FILE* makefile = fopen(filepath, "w");
    if(makefile == NULL)
    {
        printf("Unable to create the file \"Makefile\"\n");
        return 1;
    }
    
    fprintf(makefile, "# Compiler, flags, executable_name\n");
    fprintf(makefile, "CC = g++\n");
    fprintf(makefile, "CFLAGS = -g -Wall -Wextra -I$(INCLUDE_DIR) # Do not remove -I$(INCLUDE_DIR)\n");
    fprintf(makefile, "EXECUTABLE = app\n\n");

    fprintf(makefile, "# Directories\n");
    fprintf(makefile, "SRC_DIR = src\n");
    fprintf(makefile, "BUILD_DIR = build\n");
    fprintf(makefile, "INCLUDE_DIR = include\n\n");

    fprintf(makefile, "#---------------------------------------------------------------#\n");
    fprintf(makefile, "#--/ It is recommended to NOT TOUCH anything below that line /--#\n");
    fprintf(makefile, "#---------------------------------------------------------------#\n\n");

    fprintf(makefile, "# Source and object files\n");
    fprintf(makefile, "SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)\n");
    fprintf(makefile, "OBJ_FILES = $(patsubst $(SRC_DIR)/%%.cpp,$(BUILD_DIR)/%%.o,$(SRC_FILES))\n\n");

    fprintf(makefile, "# Automatically find library directories\n");
    fprintf(makefile, "LIBRARY_DIRS = $(wildcard $(INCLUDE_DIR)/*/)\n\n");

    fprintf(makefile, "# Include directories for libraries\n");
    fprintf(makefile, "LIBRARY_INCLUDES = $(foreach dir, $(LIBRARY_DIRS), -I$(dir))\n\n");

    fprintf(makefile, "# Library source files\n");
    fprintf(makefile, "LIBRARY_SRC_FILES = $(wildcard $(addsuffix *.cpp, $(LIBRARY_DIRS)))\n");
    fprintf(makefile, "LIBRARY_OBJ_FILES = $(patsubst %%c, $(BUILD_DIR)/%%.o, $(notdir $(LIBRARY_SRC_FILES)))\n\n");

    fprintf(makefile, "# Default target\n");
    fprintf(makefile, "all: $(EXECUTABLE)\n\n");

    fprintf(makefile, "# Compile main source files into object files\n");
    fprintf(makefile, "$(BUILD_DIR)/%%.o: $(SRC_DIR)/%%.cpp\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@\n\n");

    fprintf(makefile, "# Compile library source files into object files\n");
    fprintf(makefile, "$(BUILD_DIR)/%%.o: $(INCLUDE_DIR)/*/%%.cpp\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@\n\n");

    fprintf(makefile, "# Link object files to create the executable\n");
    fprintf(makefile, "$(EXECUTABLE): $(OBJ_FILES) $(LIBRARY_OBJ_FILES)\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) $^ -o $@\n\n");

    fprintf(makefile, "# Clean build artifacts\n");
    fprintf(makefile, "clean:\n");
    fprintf(makefile, "\trm -f $(BUILD_DIR)/*.o\n");
    fprintf(makefile, "\trm -f $(EXECUTABLE)\n");

    fclose(makefile);

    return 0;
}

/* @param filepath Path to the folder where 'README.md' is created, without a / at the end
 * @retval Error status : should be 0 or there was an error
 */
int cpp_writeReadme(char* filepath)
{
    strcat(filepath, "/README.md");

    FILE* readme = fopen(filepath, "w");
    if(readme == NULL)
    {
        printf("Unable to create the file \"README.md\"\n");
        return 1;
    }
    
    fprintf(readme, "# Automatically setup project\n");
    fprintf(readme, "The software that generated this project configuration can be found on [Github](https://github.com/kez97460/Automatic-project-setup).\n");
    fprintf(readme, "This README can help you understand how to properly use this setup.\n\n");

    fprintf(readme, "## Directories\n\n");

    fprintf(readme, "### build\n");
    fprintf(readme, "The Build directory will contain the object files (.o) that are generated when compiling.\n\n");

    fprintf(readme, "### include\n");
    fprintf(readme, "The include directory will contain all libraries included by the project (.h and .cpp files). These libraries may be put into as many independent folders as needed.\n\n");

    fprintf(readme, "### src\n");
    fprintf(readme, "The src directory contains the source files (.cpp), including the main function.\n\n");

    fprintf(readme, "### Example\n");
    fprintf(readme, "This structure is an example of how a project could look like :\n\n");
    fprintf(readme, "```\n");
    fprintf(readme, "|--lib\n");
    fprintf(readme, "|  |\n");
    fprintf(readme, "|  |--Bar\n");
    fprintf(readme, "|  |  |- Bar.cpp\n");
    fprintf(readme, "|  |  |- Bar.h\n");
    fprintf(readme, "|  |\n");
    fprintf(readme, "|  |--Foo\n");
    fprintf(readme, "|  |  |- Foo.cpp\n");
    fprintf(readme, "|  |  |- Foo.h\n");
    fprintf(readme, "|  \n");
    fprintf(readme, "|--src\n");
    fprintf(readme, "|  |- main.cpp\n");
    fprintf(readme, "```\n\n");

    fprintf(readme, "## Makefile\n");
    fprintf(readme, "This project can be compiled using the `make` command (assuming you have it installed). The object files, as well as the executable, which are generated during the compilation, may be removed at any time by using the `make clean` command.\n\n");
    fprintf(readme, "The readme can be edited to change the compiler, compilation flags or the name of the generated executable.\n");

    fclose(readme);

    return 0;
}