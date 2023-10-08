#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

int c_writeMain(char* filepath);
int c_writeMakefile(char* filepath);

int cpp_writeMain(char* filepath);
int cpp_writeMakefile(char* filepath);

#endif /* FILEWRITER_H */
