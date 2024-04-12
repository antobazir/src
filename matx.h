#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>        
#include <sys/stat.h>

int find_int(int sz, int value, int Mat[sz][sz], int* row, int* col);
int find_float(float value, float** Mat, unsigned int sz, int* row, int* col);
