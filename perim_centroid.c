/*ne recalculer le centroid qu'avant la fonction pour éviter la dérive.*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>        
#include <sys/stat.h>
#include <time.h>
#include "structdef.h"

extern Model Mod;

void centroid(int *row_ctrd, int *col_ctrd)
{

	int N_pts = 0;
	int i,j,sz;	
	int mod_div;
	*row_ctrd = 0;
	*col_ctrd = 0;
	/*printf("here...1\n");
	/*printf("wtf: %d \n", Mod.M_Nutr.sz);*/
	sz = Mod.M_Nutr.sz;

	
	for (i=0; i<sz; i++)
	{
		for (j=0; j<sz; j++)
		{
			/*printf("here...2\n");*/
			/* if the spot is not empty*/
			if(Mod.M_Cell.Grid[i][j]!=0) 
			{
				*row_ctrd = *row_ctrd + i;
				*col_ctrd = *col_ctrd + j;
				N_pts = N_pts +1;
			}
		}
	}

	/*if the remainder of the division is higher than half the dividend,
	then the result is rounded*/
	mod_div = 2*((*row_ctrd)%N_pts);
	if(mod_div>N_pts) 
	{
		*row_ctrd = *row_ctrd/N_pts;
		*row_ctrd = *row_ctrd +1;
	}
	else
	{
		*row_ctrd = *row_ctrd/N_pts;
	}


	if(mod_div>N_pts) 
	{
		*col_ctrd = *col_ctrd/N_pts;
		*col_ctrd = *col_ctrd +1;
	}
	else
	{
		*col_ctrd = *col_ctrd/N_pts;
	}

	/**row_ctrd = *row_ctrd/N_pts;
	*col_ctrd = *col_ctrd/N_pts;*/
	/*printf("\tcentroid: \n");
	printf("\t\t row : %d | col: %d \n\n",*row_ctrd,*col_ctrd);*/
	

}

void perim(int sz,int *lgth_perim,int row_perim[1000], int col_perim[1000])
{

	/*caution: this alogrithm works for the LD grid
	/*option 2 : any point w zero neighbor is at the rim*/
	/*printf("perim***********\n");*/
	int i,j,k,p;
	int i_val[1000], j_val[1000];
	int row_shift[1000];
	int col_shift[1000];
	*lgth_perim =0;
	
	row_shift[0] = -1; col_shift[0] = -1;
	row_shift[1] = -1; col_shift[1] = 0;
	row_shift[2] = -1; col_shift[2] = 1;
	row_shift[3] = 0; col_shift[3] = -1;
	row_shift[4] = 0; col_shift[4] = 1;
	row_shift[5] = 1; col_shift[5] = -1;
	row_shift[6] = 1; col_shift[6] = 0;
	row_shift[7] = 1; col_shift[7] = 1;
	


	for (i=0; i<sz; i++)
	{
		
		for (j=0; j<sz; j++)
		{
			for(k=0;k<8;k++)
			{
				/*Si un des voisins est vide, le point est sur le périmètre*/
				if((Mod.M_Cell.LD[i][j]!=0)&&(Mod.M_Cell.LD[i+row_shift[k]][j+col_shift[k]]==0))
				{
					i_val[*lgth_perim] = i; j_val[*lgth_perim]=j;
					row_perim[*lgth_perim] = i;
					col_perim[*lgth_perim] = j;
					*lgth_perim = *lgth_perim+1;
					break;
				}
			}
		}

	}


}
	
	


