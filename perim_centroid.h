#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>        
#include <sys/stat.h>
#include <time.h>
#include "structdef.h"

void centroid(int *row_ctrd, int *col_ctrd);

void perim(int sz,int *lgth_perim,int row_perim[400], int col_perim[400]);

