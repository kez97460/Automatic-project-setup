import os
import sys
from file_strings import h_file, c_cpp_file

# Test if "lib" folder exists
if not os.path.isdir("lib") :
    print("ERROR : The \"lib\" directory was not found.")
    print("Aborted library creation")
    exit()

lib_name = input("Library name : ")

os.makedirs(f"lib/{lib_name}")

with open(f"lib/{lib_name}/{lib_name}.h", "w") as file :
    file.write(h_file(lib_name))

with open(f"lib/{lib_name}/{lib_name}.c", "w") as file :
    file.write(c_cpp_file(lib_name))

print(f"Successfully created library {lib_name}")    