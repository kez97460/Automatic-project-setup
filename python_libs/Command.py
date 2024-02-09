import getopt, sys

help = f"""---Automatic Project Setup---
Usage : {sys.argv[0]} [COMMAND] [OPTIONS...]

Valid commands : 
project             create a new project (needs a name and language)
lib                 create a new library (needs a name)
header              create a header file (needs a name)

Options : 
-n, --name          path/name of the created object 
-l, --language      language of the project (for projects only)
-h, --help          show this

Example : {sys.argv[0]} -n ../great_idea -l c++

Not using any options opens an interactive menu instead.
"""

class Command:
    def __init__(self, args : list) -> None:
        self.command_name = ""
        self.object_name = ""
        self.language = ""

        if len(args) == 1 :
            print("ERROR : Not enough args.")
            print(help)
            return
        
        self.command_name = args[1] # Command name : first arg (header/lib/project)
        if self.command_name not in ("header", "lib", "project") :
            print(f"ERROR : invalid argument [{self.command_name}]")
            print(help)
            return

        if len(args) == 2 :
            # Interactive mode
            self.object_name = input("Name : ")
            if self.command_name == "project" :
                self.language = input("Language : ")
        else : 
            # Argument management for CLI mode
            args = args[2:]
            options = "hl:n:"
            long_options = ["help", "language=", "name="]

            arguments, values = getopt.getopt(args, options, long_options)
            for current_arg, current_val in arguments :
                if current_arg in ("-h", "--help"):
                    print(help) 
                elif current_arg in ("-n", "--name") :
                    self.object_name = current_val
                elif current_arg in ("-l", "--language") :
                    if self.command_name != "project" :
                        raise getopt.GetoptError(f"A {self.command_name} does not support the language option")
                    self.language = current_val

    def __str__(self) -> str:
        return f"---\ncommand_name : {self.command_name} \nobject_name : {self.object_name} \nlanguage : {self.language}\n---"

    


# -----Testing-----

# command = Command(sys.argv)
# print(command)