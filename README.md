## Compiling python code

You can compile the program into a single portable executable by simply executing the script `compile.sh`.

It requires you to have [**pyinstaller**](https://pyinstaller.org/en/stable/index.html) installed. 

## Usage

```bash
aps header # interactif
aps lib # interactif
aps project # interactif

aps project -n [path/name] -l [language]
aps lib -n [name]
aps header -n [name]
```