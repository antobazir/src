#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>        
#include <sys/stat.h>

int find_int( int sz, int value, int Mat[sz][sz], int *row, int *col)
{
	/*printf("find_int\n");*/
	int i, j;
	for (i=0; i<sz; i++)
	{
		for (j=0; j<sz; j++)
		{

			if(Mat[i][j]==value)
			{
				*col = j;
				*row = i;
				return;
			} 
			
		}

	}
	*row = -1;
	*col = -1;
	/*printf("row : %d | col : %d \n",*row,*col);
	printf("\n");*/
	return 0;
	
}

int find_float(float value, float** Mat, int sz, int* row, int* col)
{
	int i, j;
	for (i=0; i<sz; i++)
	{
		for (j=0; j<sz; j++)
		{
			if(Mat[i][j]==value)
			{
				col = j;
				break;
			}
			row = i;
			break; 
		}

	}

}
