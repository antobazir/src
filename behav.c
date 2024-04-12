#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structdef.h"

#include <unistd.h>        
#include <sys/stat.h>  

extern Model Mod;

void behav(char* behavior, float kS, float kO)
{

	
	int i,j,sz;
	sz = Mod.M_Nutr.sz;
	unsigned char prev_state_mat[sz][sz]; 
	unsigned char state_change[sz][sz];
	float conso_state[5][2];
	

	/*on met à jour la matrice d'état*/
	for (i=0; i<sz; i++)
	{
		for (j=0; j<sz; j++)
		{
			/*previous state_matrix*/
			prev_state_mat[i][j] = Mod.M_Cell.state_mat[i][j];
			

			/*well fed*/
			if(Mod.M_Nutr.S[i][j]>=Mod.M_Cell.S_prol
			&&Mod.M_Nutr.O[i][j]>=Mod.M_Cell.O_norm
			&& prev_state_mat[i][j]!=1
			&&Mod.M_Cell.LD[i][j]!=0)
			{
				Mod.M_Cell.state_mat[i][j] = 5;
			}

			/*hypoxia*/
			if(Mod.M_Nutr.S[i][j]>=Mod.M_Cell.S_prol
			&&Mod.M_Nutr.O[i][j]<Mod.M_Cell.O_norm
			&& prev_state_mat[i][j]!=1
			&&Mod.M_Cell.LD[i][j]!=0)
			{
				Mod.M_Cell.state_mat[i][j] = 4;
			}

			/*hyposia*/
			if(Mod.M_Nutr.S[i][j]<Mod.M_Cell.S_prol
			&&Mod.M_Nutr.S[i][j]>=Mod.M_Cell.S_maint
			&&Mod.M_Nutr.O[i][j]>=Mod.M_Cell.O_norm
			&& prev_state_mat[i][j]!=1
			&&Mod.M_Cell.LD[i][j]!=0)
			{
				Mod.M_Cell.state_mat[i][j] = 3;
			}

			/*hypox+hypos*/
			if(Mod.M_Nutr.S[i][j]<Mod.M_Cell.S_prol
			&&Mod.M_Nutr.S[i][j]>=Mod.M_Cell.S_maint
			&&Mod.M_Nutr.O[i][j]<Mod.M_Cell.O_norm
			&& prev_state_mat[i][j]!=1
			&&Mod.M_Cell.LD[i][j]!=0)
			{
				Mod.M_Cell.state_mat[i][j] = 2;
			}

			if(Mod.M_Nutr.S[i][j]<Mod.M_Cell.S_maint
			&&Mod.M_Cell.LD[i][j]!=0)
			{
				Mod.M_Cell.state_mat[i][j] = 1;
			}

			if(Mod.M_Nutr.S[i][j]<Mod.M_Cell.S_maint
			&&Mod.M_Cell.LD[i][j]!=-1)
			{
				Mod.M_Cell.state_mat[i][j] = 1;
			}

			if(Mod.M_Cell.LD[i][j]==0)
			{
				Mod.M_Cell.state_mat[i][j] = 0;
			}

			state_change[i][j] = Mod.M_Cell.state_mat[i][j] - prev_state_mat[i][j];
		}
	}

	/*ref*/
	if(strcmp(behavior,"ref") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = kS; conso_state[0][1] = kO;
		conso_state[1][0] = kS; conso_state[1][1] = kO;
		conso_state[2][0] = kS; conso_state[2][1] = kO; 
		conso_state[3][0] = kS; conso_state[3][1] = kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site to a value that is not zero,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1)
				{

				}
			}
		}

	}

	/*starv*/
	if(strcmp(behavior,"starv") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = kS; conso_state[1][1] = kO;
		conso_state[2][0] = kS; conso_state[2][1] = kO; 
		conso_state[3][0] = kS; conso_state[3][1] = kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}
			}
		}

	}

		if(strcmp(behavior,"savy") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = 0.3*kS; conso_state[1][1] = kO;
		conso_state[2][0] = 0.3*kS; conso_state[2][1] = kO; 
		conso_state[3][0] = kS; conso_state[3][1] = kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}
			}
		}

	}

	if(strcmp(behavior,"compens_prol") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = 0.3*kS; conso_state[1][1] = 2.0*kO;
		conso_state[2][0] = 0.3*kS; conso_state[2][1] = 2.0*kO; 
		conso_state[3][0] = kS; conso_state[3][1] = kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}
			}
		}

	}

	if(strcmp(behavior,"OS_fragile") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = 0.0; conso_state[1][1] = 0.0;
		conso_state[2][0] = 0.3*kS; conso_state[2][1] = 0.3*kO; 
		conso_state[3][0] = 0.3*kS; conso_state[3][1] = 0.3*kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1||Mod.M_Cell.state_mat[i][j]==2)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}
			}
		}

	}


	if(strcmp(behavior,"OS_hypos_tol") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = 0.3*kS; conso_state[1][1] = 0.3*kO;
		conso_state[2][0] = 0.3*kS; conso_state[2][1] = 2.0*kO; 
		conso_state[3][0] = 2.0*kS; conso_state[3][1] = 0.3*kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1||Mod.M_Cell.state_mat[i][j]==2)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}
			}
		}

	}

	if(strcmp(behavior,"OS_hypox_tol") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = 0.3*kS; conso_state[1][1] = 0.3*kO;
		conso_state[2][0] = 0.3*kS; conso_state[2][1] = 2.0*kO; 
		conso_state[3][0] = 2.0*kS; conso_state[3][1] = 0.3*kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1||Mod.M_Cell.state_mat[i][j]==2)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}
			}
		}

	}

	if(strcmp(behavior,"OS_hypox_boost") == 0)
	{
		/*printf("here?\n");*/
		conso_state[0][0] = 0.0; conso_state[0][1] = 0.0;
		conso_state[1][0] = kS; conso_state[1][1] = 0.3*kO;
		conso_state[2][0] = 0.3*kS; conso_state[2][1] = 2.0*kO; 
		conso_state[3][0] = 2.0*kS; conso_state[3][1] = 0.3*kO;
		conso_state[4][0] = kS; conso_state[4][1] = kO;
		 

		for (i=0; i<sz; i++)
		{
			for (j=0; j<sz; j++)
			{  
				/*if the state has changed on a site,
				state vector timer is set*/
				if(state_change[i][j]!=0&&Mod.M_Cell.Grid[i][j]!=0)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][2] = Mod.M_Cell.reac_time;
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][4] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][0]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][3])/(float)(Mod.M_Cell.reac_time);
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][6] = (conso_state[Mod.M_Cell.state_mat[i][j]-1][1]-Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][5])/(float)(Mod.M_Cell.reac_time);	
				}

				if(Mod.M_Cell.state_mat[i][j]==1||Mod.M_Cell.state_mat[i][j]==2)
				{
					Mod.M_Cell.LD[i][j]=-1;
				}

				if(Mod.M_Cell.state_mat[i][j]==4)
				{
					Mod.M_Cell.state[Mod.M_Cell.Grid[i][j]-1][1]=2.0;
				}
			}
		}

	}


}
