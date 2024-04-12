/* file containing the migration functions*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matx.h"
#include "divide.h"
#include "structdef.h"
#include "perim_centroid.h"

#include <unistd.h>        
#include <sys/stat.h>  


extern Model Mod;

int migrate_sphere()
{
	int i,j,sz,k,n,m,p;
	sz = Mod.M_Nutr.sz;
	int row_perim[1000];  
	int col_perim[1000];
	int row_shift[8];  
	int col_shift[8];
	int row_ctrd, row;
	int col_ctrd, col;
	int lgth_perim=0;
	int rad_sq[1000];
	int rad_sq_n[8];
	int min_rad;
	int n_closer,n_closest;
	int closer[8],closest[8];
	int chosen_site;
	float D_buff;
	/*FILE *f;*/


	row_shift[0] = -1; col_shift[0] = -1;
	row_shift[1] = -1; col_shift[1] = 0;
	row_shift[2] = -1; col_shift[2] = 1;
	row_shift[3] = 0; col_shift[3] = -1;
	row_shift[4] = 0; col_shift[4] = 1;
	row_shift[5] = 1; col_shift[5] = -1;
	row_shift[6] = 1; col_shift[6] = 0;
	row_shift[7] = 1; col_shift[7] = 1;

	/*test*/
	/*Mod.M_Cell.Grid[4][5]=2;
	Mod.M_Cell.Grid[4][3]=3;
	Mod.M_Cell.Grid[3][5]=4;
	Mod.M_Cell.Grid[4][6]=9;
	Mod.M_Cell.Grid[5][4]=8;
	Mod.M_Cell.Grid[3][4]=7;
	Mod.M_Cell.Grid[3][3]=6;
	Mod.M_Cell.Grid[5][3]=5;
	Mod.M_Cell.Grid[4][7]=10;
	Mod.M_Cell.N_Cell=10;

	Mod.M_Cell.LD[4][5]=1;
	Mod.M_Cell.LD[4][3]=1;
	Mod.M_Cell.LD[3][5]=1;
	Mod.M_Cell.LD[5][5]=1;
	Mod.M_Cell.LD[5][4]=1;
	Mod.M_Cell.LD[3][4]=1;
	Mod.M_Cell.LD[3][3]=1;
	Mod.M_Cell.LD[5][3]=1;
	Mod.M_Cell.LD[5][2]=1;*/

	sz = Mod.M_Nutr.sz;
	min_rad = sz;

		/* initialise le générateur de nombres*/
	srand(time(0));


	row_ctrd = (sz/2) - 1;
	col_ctrd = (sz/2) - 1;



	/*lgth_perim =*/ 
	perim(sz,&lgth_perim,row_perim,col_perim);


	for(k=0;k<lgth_perim;k++)
	{

		/*for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				printf("%d ",Mod.M_Cell.Grid[i][j]);
			}
			printf("\n");

		}*/
	
		rad_sq[k] = ((row_perim[k]-row_ctrd)*(row_perim[k]-row_ctrd))
			 + ((col_perim[k]-col_ctrd)*(col_perim[k]-col_ctrd));

		for(n=0;n<8;n++)
		{
				
			if(n==0)
			{			
				n_closer = 0;

			}	
			rad_sq_n[n] = ((row_perim[k]+row_shift[n]-row_ctrd)*(row_perim[k]+row_shift[n]-row_ctrd))
			 	+ ((col_perim[k]+col_shift[n]-col_ctrd)*(col_perim[k]+col_shift[n]-col_ctrd));

			/* if the neighbor is free save it*/

			/*keeping index of closer neighbors*/
			if((rad_sq_n[n]<rad_sq[k])&&(Mod.M_Cell.LD[row_perim[k]+row_shift[n]][col_perim[k]+col_shift[n]]==0))
			{	
				
				closer[n_closer] = n;
				n_closer = n_closer +1;
					
			} 
			

		}

		if(n_closer>0)
		{
			/* if exactly one neighbor is closer*/
			if(n_closer==1)
			{
				/*printf("l.163 \n");*/
				chosen_site = closer[n_closer-1];


				/*shifts w/ said neighbor*/
				Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Cell.Grid[row_perim[k]][col_perim[k]];
				Mod.M_Cell.Grid[row_perim[k]][col_perim[k]] = 0;

				/*after displacement,update position in state_vector*/
				find_int(sz,Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]],Mod.M_Cell.Grid,&row,&col);
								
				Mod.M_Cell.state[Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]]-1][7] = (float)(row);
				Mod.M_Cell.state[Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]]-1][8] = (float)(col);
				

				Mod.M_Cell.LD[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = 1;
				Mod.M_Cell.LD[row_perim[k]][col_perim[k]] = 0;
				Mod.M_Cell.state_mat[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Cell.Grid[row_perim[k]][col_perim[k]];
				Mod.M_Cell.state_mat[row_perim[k]][col_perim[k]] = 0;
				Mod.M_Nutr.kS[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.kS[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.kS[row_perim[k]][col_perim[k]] = 0;
				Mod.M_Nutr.kO[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.kO[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.kO[row_perim[k]][col_perim[k]] = 0;
				D_buff = Mod.M_Nutr.DSm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]];
				Mod.M_Nutr.DSm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.DSm[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.DSm[row_perim[k]][col_perim[k]] = D_buff;
				D_buff = Mod.M_Nutr.DOm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]];
				Mod.M_Nutr.DOm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.DOm[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.DOm[row_perim[k]][col_perim[k]] = D_buff;
				
				/*for(i=0;i<sz;i++)
				{
					for(j=0;j<sz;j++)
					{
						printf("%d ",Mod.M_Cell.Grid[i][j]);
					}
					printf("\n");

				}*/				
				

				/*if a shift occurs get back to the start w/ new perim and centroid*/				
				/*centroid(mod,&row_ctrd,&col_ctrd);*/	
				perim(sz,&lgth_perim,row_perim,col_perim);			
				k=-1;/*you shifted so you need to calculate again*/
				/*break;*/ 			
			}

			/*if more than one neighbor is closer*/
			if(n_closer>1)
			{
		
			
				/*the neighbors w/ min distance is found*/
				min_rad = rad_sq_n[closer[0]];
				n_closest=0;
				
				for(m=0;m<n_closer;m++)
				{
					if(rad_sq_n[closer[m]]<min_rad)
					{
					
						min_rad= rad_sq_n[closer[m]];
						closest[0] = closer[m];
						n_closest = 1;
					}

					if(rad_sq_n[closer[m]]==min_rad)
					{
						closest[n_closest] = closer[m];
						n_closest = n_closest+1;	
					}
				}
				

	
				/* if one neighbor closer*/
				if(n_closest==1)
				{
					chosen_site = closest[0];
				}

				if(n_closest>1)
				{
					chosen_site = closest[(rand() % 
					((n_closest-1) - 0 + 1)) + 0];
				}


				n_closest= 0;
				n_closer =0;

				/*printf("several neighbs; \t col_perim[%d]: %d  \t  chosen_site : %d  \t Grid : %d \n\n",k,col_perim[k],chosen_site,Mod.M_Cell.Grid[row_perim[k]][col_perim[k]]);*/

				Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Cell.Grid[row_perim[k]][col_perim[k]];
				Mod.M_Cell.Grid[row_perim[k]][col_perim[k]] = 0;


				/*after displacement,update position in state_vector*/
				find_int(sz,Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]],Mod.M_Cell.Grid,&row,&col);
				
				Mod.M_Cell.state[Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]]-1][7] = (float)(row);
				Mod.M_Cell.state[Mod.M_Cell.Grid[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]]-1][8] = (float)(col);


				Mod.M_Cell.LD[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = 1;
				Mod.M_Cell.LD[row_perim[k]][col_perim[k]] = 0;
				Mod.M_Cell.state_mat[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Cell.Grid[row_perim[k]][col_perim[k]];
				Mod.M_Cell.state_mat[row_perim[k]][col_perim[k]] = 0;
				Mod.M_Nutr.kS[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.kS[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.kS[row_perim[k]][col_perim[k]] = 0;
				Mod.M_Nutr.kO[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.kO[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.kO[row_perim[k]][col_perim[k]] = 0;
				D_buff = Mod.M_Nutr.DSm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]];
				Mod.M_Nutr.DSm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.DSm[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.DSm[row_perim[k]][col_perim[k]] = D_buff;
				D_buff = Mod.M_Nutr.DOm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]];
				Mod.M_Nutr.DOm[row_perim[k]+row_shift[chosen_site]][col_perim[k]+col_shift[chosen_site]] = Mod.M_Nutr.DOm[row_perim[k]][col_perim[k]];
				Mod.M_Nutr.DOm[row_perim[k]][col_perim[k]] = D_buff;


				/*for(i=0;i<sz;i++)
				{
					for(j=0;j<sz;j++)
					{
						printf("%d ",Mod.M_Cell.Grid[i][j]);
					}
					printf("\n");

				}*/

				/*centroid(mod,&row_ctrd,&col_ctrd);*/
				perim(sz,&lgth_perim,row_perim,col_perim);			
				k=-1;/*you shifted so you need to calculate again*/
				/*break;*/
		
			}
		}				
		
	}


}
