#ifndef FILE_OPERATIONS_GUARD__H
#define FILE_OPERATIONS_GUARD__H

#include <stdio.h>

#define MAXSIZE 66

int SetupArray(char* fileName);//, int (*array)[MAXSIZE]);
int SaveData(char* fileName, int (*array)[MAXSIZE]);

#endif
