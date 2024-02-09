import os, sys
from python_libs.Command import *
from python_libs.file_strings import * 

def create_lib(lib_name : str) :
    # Test if "lib" folder exists
    if not os.path.isdir("lib") :
        print("ERROR : The \"lib\" directory was not found.")
        print("Aborted library creation")
        return

    os.makedirs(f"lib/{lib_name}")

    with open(f"lib/{lib_name}/{lib_name}.h", "w") as file :
        file.write(h_file(lib_name))

    with open(f"lib/{lib_name}/{lib_name}.c", "w") as file :
        file.write(c_cpp_file(lib_name))

    print(f"Successfully created library {lib_name}")  

def create_header(header_name : str) :
    """
    Create a header without an associated file (.h) directly in the lib folder
    """
    # Test if "lib" folder exists
    if not os.path.isdir("lib") :
        print("ERROR : The \"lib\" directory was not found.")
        print("Aborted header creation")
        return
    
    with open(f"lib/{header_name}.h", "w") as file :
        file.write(h_file(header_name))

    print(f"Successfully created header {header_name}") 

def create_project_c_cpp(project_name : str, language : str) :
    
    # test language validity
    if language in ["c", "C"] :
        language = "c"
    elif language in ["cpp", "c++", "C++"] :
        language = "cpp"
    else :
        print(f"ERROR : invalid language ({language})")
        print("Aborted project creation")
        return
    
    os.makedirs(project_name)
    os.chdir(project_name)

    os.makedirs("lib")
    os.makedirs("src")
    os.makedirs("build")

    with open(f"README.md", "w") as file :
        file.write(readme_c_cpp(project_name))

    with open(f"src/main.{language}", "w") as file :
        file.write(main_c_cpp())

    with open("Makefile", "w") as file :
        if language == "c" : 
            file.write(makefile_c())
        elif language == "cpp" : 
            file.write(makefile_cpp())

    print(f"Successfully created project {project_name}")

# -------- Main --------
    
command = Command(sys.argv)
# print(command)

if command.command_name == "project" :
    create_project_c_cpp(command.object_name, command.language)
elif command.command_name == "lib" :
    create_lib(command.object_name)
elif command.command_name == "header" :
    create_header(command.object_name)

print("Finished")
