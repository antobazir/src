#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>        
#include <sys/stat.h>
#include <time.h>
#include "structdef.h"
#include "matx.h"

extern Model Mod;

int divide(int cell_idx) 
{
	int ngh[3][3];
	int ngh_vec[8];
	int i,j;
	int n_free = 0;
	int k=0;
	int l=0;
	int n_row[8];
	int nf_row[8];
	int n_col[8];
	int nf_col[8];	 
	int idx_ngh[8]; 
	int chosen_site;
	int interm_row, row;
	int interm_col, col;
	int row_shift[8];
	int col_shift[8];

	row_shift[0] = -1; col_shift[0] = -1;
	row_shift[1] = -1; col_shift[1] = 0;
	row_shift[2] = -1; col_shift[2] = 1;
	row_shift[3] = 0; col_shift[3] = -1;
	row_shift[4] = 0; col_shift[4] = 1;
	row_shift[5] = 1; col_shift[5] = -1;
	row_shift[6] = 1; col_shift[6] = 0;
	row_shift[7] = 1; col_shift[7] = 1;

	
	/* initialise le générateur de nombres*/
	srand(time(0));
	
	find_int(Mod.M_Nutr.sz,cell_idx,Mod.M_Cell.Grid,&row,&col);

	/*test:  cas plusieurs voisins libres */ 
	/*Mod.M_Cell.Grid[4][5]=2;
	Mod.M_Cell.N_Cell=Mod.M_Cell.N_Cell+1;*/

	/*test:  cas tous les voisins libres */ 


	/*test:  cas aucun voisin libre */ 
	/*Mod.M_Cell.Grid[4][5]=2;
	Mod.M_Cell.Grid[4][3]=3;
	Mod.M_Cell.Grid[3][5]=4;
	Mod.M_Cell.Grid[5][5]=9;
	Mod.M_Cell.Grid[5][4]=8;
	Mod.M_Cell.Grid[3][4]=7;
	Mod.M_Cell.Grid[3][3]=6;
	Mod.M_Cell.Grid[5][3]=5;
	Mod.M_Cell.N_Cell=9;*/
	
	if(row==-1||col==-1)
	{
		printf("sz: %d \n",Mod.M_Nutr.sz);
		printf("%d Not found \n",cell_idx);
		return -1;
	}


	/* on compte les voisins vide et on identifie les voisins vides*/
	for(i=-1; i<2;i++)
	{
		for(j=-1; j<2;j++)
		{
			ngh[i+1][j+1] = Mod.M_Cell.Grid[row+i][col+j];
			/*printf("current: %d \n",ngh[i+1][j+1]);*/
			n_row[l] = row+i;
			n_col[l] = col+j;	
			if(ngh[i+1][j+1]==0)
			{	
				if(i!=0||j!=0)
				{	
					nf_row[k] = row+i;
					nf_col[k] = col+j;
					idx_ngh[k] = l+1;			
					n_free = n_free+1;
					k = k+1;
				}
					
			}
			l=l+1; 
		}
	}


	/*no free neighbor*/
	if(n_free==0)
	{
		/* no free site, selection in general list */
		chosen_site = (rand() % 
		(7 - 0 + 1)) + 0; 
		interm_row = row ;  interm_col = col;
		
		/*Si la case n'est pas vide on passe à côté*/
		while(Mod.M_Cell.Grid[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]]!=0)
		{
			interm_row = interm_row+row_shift[chosen_site];
			interm_col = interm_col+col_shift[chosen_site];
				
		} 

		/* now interm_row/col is on the border */
		/* as long as the intermediate position is not back to before you switch and skip*/
		while(interm_row!=row||interm_col!=col) 
		{
			/*1.shift the grids*/
			Mod.M_Cell.Grid[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Cell.Grid[interm_row][interm_col];
			Mod.M_Cell.state[Mod.M_Cell.Grid[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]]-1][7] = (float)(interm_row+row_shift[chosen_site]);
			Mod.M_Cell.state[Mod.M_Cell.Grid[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]]-1][8] = (float)(interm_col+col_shift[chosen_site]);			
			Mod.M_Cell.LD[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Cell.LD[interm_row][interm_col];
			Mod.M_Nutr.DSm[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.DSm[interm_row][interm_col];
			Mod.M_Nutr.DOm[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.DOm[interm_row][interm_col];
			Mod.M_Nutr.kS[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.kS[interm_row][interm_col];
			Mod.M_Nutr.kO[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.kO[interm_row][interm_col];

			/*2. shift back*/			
			interm_row = interm_row-row_shift[chosen_site];
			interm_col = interm_col-col_shift[chosen_site];
		}

		/*shift is done new cell is placed*/
		
		
		/*state vector update*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][0] = 0.0;
		Mod.M_Cell.state[cell_idx-1][0] = 0.0; /*divison timer*/

		Mod.M_Cell.state[Mod.M_Cell.N_Cell][1] = Mod.M_Cell.state[cell_idx-1][1];/* prolif index*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][2] = Mod.M_Cell.state[cell_idx-1][2];/* state change timer*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][3] = Mod.M_Cell.state[cell_idx-1][3];/*substrate consumption*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][4] = Mod.M_Cell.state[cell_idx-1][4];/*substrate consumption evolution*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][5] = Mod.M_Cell.state[cell_idx-1][5];/*oxygen consumption*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][6] = Mod.M_Cell.state[cell_idx-1][6];/*oxygen consumption evolution*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][7] = (float)(interm_row+row_shift[chosen_site]);/*row*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][8] = (float)(interm_col+col_shift[chosen_site]);/*column*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][9] = (float)(cell_idx);/*parent*/

		Mod.M_Cell.N_Cell = Mod.M_Cell.N_Cell+1; 


		Mod.M_Cell.Grid[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Cell.N_Cell;
		Mod.M_Cell.LD[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = 1;
		Mod.M_Nutr.DSm[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.DSm[row][col];
		Mod.M_Nutr.DOm[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.DOm[row][col];		
		Mod.M_Nutr.kS[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.kS[row][col];
		Mod.M_Nutr.kO[interm_row+row_shift[chosen_site]][interm_col+col_shift[chosen_site]] = Mod.M_Nutr.kO[row][col];		

	
	}

	/* one free neighbor*/
	if(n_free==1)
	{	
		/*if only one site, it is chosen */

		interm_row = row ;  interm_col = col;

		Mod.M_Cell.state[Mod.M_Cell.N_Cell][0] = 0.0; /*divison timer*/
		Mod.M_Cell.state[cell_idx-1][0] = 0.0; 
	
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][1] = Mod.M_Cell.state[cell_idx-1][1];/* prolif index*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][2] = Mod.M_Cell.state[cell_idx-1][2];/* state change timer*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][3] = Mod.M_Cell.state[cell_idx-1][3];/*substrate consumption*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][4] = Mod.M_Cell.state[cell_idx-1][4];/*substrate consumption evolution*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][5] = Mod.M_Cell.state[cell_idx-1][5];/*oxygen consumption*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][6] = Mod.M_Cell.state[cell_idx-1][6];/*oxygen consumption evolution*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][7] = (float)(nf_row[chosen_site]);/*row*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][8] = (float)(nf_col[chosen_site]);/*column*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][9] = (float)(cell_idx);/*parent*/

		Mod.M_Cell.N_Cell = Mod.M_Cell.N_Cell+1;
 
		Mod.M_Cell.Grid[nf_row[0]][nf_col[0]] = Mod.M_Cell.N_Cell;
		Mod.M_Cell.LD[nf_row[0]][nf_col[0]] = 1;
		Mod.M_Nutr.DSm[nf_row[0]][nf_col[0]] = Mod.M_Nutr.DSm[row][col];
		Mod.M_Nutr.DOm[nf_row[0]][nf_col[0]] = Mod.M_Nutr.DOm[row][col];
		Mod.M_Nutr.kS[nf_row[0]][nf_col[0]] = Mod.M_Nutr.kS[row][col];
		Mod.M_Nutr.kO[nf_row[0]][nf_col[0]] = Mod.M_Nutr.kO[row][col];

		
		/*printf("\t chosen site:\n");
		printf("\t row: %d | col: %d \n",nf_row[0],nf_col[0]);*/
	}

	/*several free neighbors*/
	if(n_free>1)
	{

		interm_row = row ;  interm_col = col;
		/*Si la case n'est pas vide on passe à côté*/

		/*printf("here, \t row: %d \t col : %d \n",row,col);*/

		/*if several free site, random selection in list */
		chosen_site = (rand() % 
		((n_free-1) - 0 + 1)) + 0; 
		

		Mod.M_Cell.state[Mod.M_Cell.N_Cell][0] = 0.0; /*divison timer*/
		Mod.M_Cell.state[cell_idx-1][0] = 0.0; 

		Mod.M_Cell.state[Mod.M_Cell.N_Cell][1] = Mod.M_Cell.state[cell_idx-1][1];/* prolif index*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][2] = Mod.M_Cell.state[cell_idx-1][2];/* state change timer*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][3] = Mod.M_Cell.state[cell_idx-1][3];/*substrate consumption*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][4] = Mod.M_Cell.state[cell_idx-1][4];/*substrate consumption evolution*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][5] = Mod.M_Cell.state[cell_idx-1][5];/*oxygen consumption*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][6] = Mod.M_Cell.state[cell_idx-1][6];/*oxygen consumption evolution*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][7] = (float)(nf_row[chosen_site]);/*row*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][8] = (float)(nf_col[chosen_site]);/*column*/
		Mod.M_Cell.state[Mod.M_Cell.N_Cell][9] = (float)(cell_idx);/*parent*/

		Mod.M_Cell.N_Cell = Mod.M_Cell.N_Cell+1;

		Mod.M_Cell.Grid[nf_row[chosen_site]][nf_col[chosen_site]] = Mod.M_Cell.N_Cell ;
		Mod.M_Cell.LD[nf_row[chosen_site]][nf_col[chosen_site]] = 1;
		Mod.M_Nutr.DSm[nf_row[chosen_site]][nf_col[chosen_site]] = Mod.M_Nutr.DSm[row][col];
		Mod.M_Nutr.DOm[nf_row[chosen_site]][nf_col[chosen_site]] = Mod.M_Nutr.DOm[row][col];
		Mod.M_Nutr.kS[nf_row[chosen_site]][nf_col[chosen_site]] = Mod.M_Nutr.kS[row][col];
		Mod.M_Nutr.kO[nf_row[chosen_site]][nf_col[chosen_site]] = Mod.M_Nutr.kO[row][col];

	}

	/*printf("div finished \n\n");*/

	return 0;
} 
