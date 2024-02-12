#-----------------------------------------------------------------------#

# -----C/C++ Main function-----
def main_c_cpp():
    main_c_cpp_contents = """
/*----- Includes -----*/

/*----- Prototypes and global vars -----*/

/*----- Main -----*/
int main()
{
    // feur
}

/*----- Functions -----*/

"""
    return main_c_cpp_contents

# h_file needs the lib name for include guards
def h_file(lib_name : str):
    h_file_contents = f"""#ifndef {lib_name.upper()}_H
#define {lib_name.upper()}_H

/*----- Includes -----*/

/*----- Typedefs -----*/

/*----- Functions -----*/

#endif
"""
    return h_file_contents

# c_file needs the lib name to include it
def c_cpp_file(lib_name : str):
    c_cpp_file_contents = f"""#include "{lib_name}.h"
"""
    return c_cpp_file_contents

#-----------------------------------------------------------------------#

# -----C Makefile-----
def makefile_c():
	makefile_c_contents = """# Compiler, flags, executable_name
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror # -g : debug flag
EXECUTABLE = app

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = lib

#---------------------------------------------------------------#
#--/ It is recommended to NOT TOUCH anything below that line /--#
#---------------------------------------------------------------#

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Automatically find library directories
LIBRARY_DIRS = $(wildcard $(INCLUDE_DIR)/*/) $(INCLUDE_DIR)/

# Include directories for libraries
LIBRARY_INCLUDES = $(foreach dir, $(LIBRARY_DIRS), -I$(dir))

# Library source files
LIBRARY_SRC_FILES = $(wildcard $(addsuffix *.c, $(LIBRARY_DIRS)))
LIBRARY_OBJ_FILES = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(LIBRARY_SRC_FILES)))

# Default target
all: $(EXECUTABLE)

# Compile main source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@

# Compile library source files into object files
$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/*/%.c # Libraries in separate folders
	$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.c # libraries directly in include/
	$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@

# Link object files to create the executable
$(EXECUTABLE): $(OBJ_FILES) $(LIBRARY_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(EXECUTABLE)

run:
	make $(EXECUTABLE)
	./$(EXECUTABLE)

"""
	return makefile_c_contents

# -----C++ Makefile-----
def makefile_cpp():
	makefile_cpp_contents = """# Compiler, flags, executable_name
CC = g++
CFLAGS = -g -Wall -Wextra # -g : debug flag
EXECUTABLE = app

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = lib

#---------------------------------------------------------------#
#--/ It is recommended to NOT TOUCH anything below that line /--#
#---------------------------------------------------------------#

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Automatically find library directories
LIBRARY_DIRS = $(wildcard $(INCLUDE_DIR)/*/) $(INCLUDE_DIR)/

# Include directories for libraries
LIBRARY_INCLUDES = $(foreach dir, $(LIBRARY_DIRS), -I$(dir))

# Library source files
LIBRARY_SRC_FILES = $(wildcard $(addsuffix *.cpp, $(LIBRARY_DIRS)))
LIBRARY_OBJ_FILES = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(LIBRARY_SRC_FILES)))

# Default target
all: $(EXECUTABLE)

# Compile main source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@

# Compile library source files into object files
$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/*/%.cpp # Libraries in separate folders
	$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: $(INCLUDE_DIR)/%.cpp # libraries directly in include/
	$(CC) $(CFLAGS) $(LIBRARY_INCLUDES) -c $< -o $@

# Link object files to create the executable
$(EXECUTABLE): $(OBJ_FILES) $(LIBRARY_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(EXECUTABLE)

run:
	make $(EXECUTABLE)
	./$(EXECUTABLE)

"""
	return makefile_cpp_contents

#-----------------------------------------------------------------------#

# -----C/C++ README-----
def readme_c_cpp(project_name : str):
    readme_c_cpp_contents = f"""# {project_name}

## Automatically setup project

The software that generated this project configuration can be found on [Github](https://github.com/kez97460/Automatic-project-setup).
This README is here to help you understand how to properly use this setup.

## Directories

### build
The Build directory will contain the object files (.o) that are generated when compiling.

### lib
The lib directory will contain all libraries included by the project (.h **and** .c files). These libraries may be put into as many independent folders as needed.

### src
The src directory contains source files (.c or .cpp), including the main function.

### Example
This structure is an example of how a project could look like :

```
|--lib
|  |
|  |--Bar
|  |  |- Bar.c
|  |  |- Bar.h
|  |
|  |- Foo.c
|  |- Foo.h
|  
|--src
|  |- main.c
```

## Makefile

This project can be compiled using the `make` command (assuming you have it installed). 
The object files, as well as the executable, which are generated during the compilation, may be removed at any time by using the `make clean` command. 
The `make run`command can be used to compile, then immediately run the executable.

The readme can be edited to change the compiler, compilation flags or the name of the generated executable.

"""
    return readme_c_cpp_contents