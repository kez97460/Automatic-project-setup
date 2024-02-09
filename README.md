## Compiling python code

Use pyinstaller to compile the code to a single executable with the command : 

```bash
pyinstaller -F main.py
```
## Usage

```bash
aps header # interactif
aps lib # interactif
aps project # interactif

aps project -n [path/name] -l [language]
aps lib -n [name]
aps header -n [name]
```