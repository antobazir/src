#include <stdio.h>
#include <math.h>
#include <time.h>

#include "structdef.h"

extern Model Mod;

void diff_metvar()
{

	int i,j,sz,h,nt;
	sz = Mod.M_Nutr.sz;
	/*printf("15 here : dt : %f \n",Mod.M_Nutr.dt);*/
	nt = (int)(1.0/Mod.M_Nutr.dt);
	/*printf("1/dt: %f \n",1.0/Mod.M_Nutr.dt);
	printf("nt: %d \n",nt);*/

	for (h=0; h<nt; h++)
	{
		for (i=1; i<sz-1; i++)
		{
			for (j=1; j<sz-1; j++)
			{	
				if(Mod.M_Nutr.S[i][j]>0.0)
				{
					Mod.M_Nutr.S[i][j] = Mod.M_Nutr.S[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
							  0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i-1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i-1][j]))*(Mod.M_Nutr.S[i-1][j] - Mod.M_Nutr.S[i][j]) 
							+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i+1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i+1][j]))*(Mod.M_Nutr.S[i+1][j] - Mod.M_Nutr.S[i][j]) 
							+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j-1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j-1]))*(Mod.M_Nutr.S[i][j-1] - Mod.M_Nutr.S[i][j])	
							+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j+1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j+1]))*(Mod.M_Nutr.S[i][j+1] - Mod.M_Nutr.S[i][j])
							) -  Mod.M_Nutr.dt*Mod.M_Nutr.kS[i][j];
				}

				if(Mod.M_Nutr.S[i][j]<=0.0)
				{
					Mod.M_Nutr.S[i][j] = Mod.M_Nutr.S[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
							  0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i-1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i-1][j]))*(Mod.M_Nutr.S[i-1][j] - Mod.M_Nutr.S[i][j]) 
							+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i+1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i+1][j]))*(Mod.M_Nutr.S[i+1][j] - Mod.M_Nutr.S[i][j]) 
							+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j-1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j-1]))*(Mod.M_Nutr.S[i][j-1] - Mod.M_Nutr.S[i][j])	
							+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j+1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j+1]))*(Mod.M_Nutr.S[i][j+1] - Mod.M_Nutr.S[i][j])
							);
				}




				if(Mod.M_Nutr.O[i][j]>0.0)
				{
					Mod.M_Nutr.O[i][j] = Mod.M_Nutr.O[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
							  0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i-1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i-1][j]))*(Mod.M_Nutr.O[i-1][j] - Mod.M_Nutr.O[i][j]) 
							+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i+1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i+1][j]))*(Mod.M_Nutr.O[i+1][j] - Mod.M_Nutr.O[i][j]) 
							+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j-1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j-1]))*(Mod.M_Nutr.O[i][j-1] - Mod.M_Nutr.O[i][j])	
							+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j+1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j+1]))*(Mod.M_Nutr.O[i][j+1] - Mod.M_Nutr.O[i][j])
							) -  Mod.M_Nutr.dt*Mod.M_Nutr.kO[i][j];
				}

				if(Mod.M_Nutr.O[i][j]<=0.0)
				{
					Mod.M_Nutr.O[i][j] = Mod.M_Nutr.O[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
							  0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i-1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i-1][j]))*(Mod.M_Nutr.O[i-1][j] - Mod.M_Nutr.O[i][j]) 
							+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i+1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i+1][j]))*(Mod.M_Nutr.O[i+1][j] - Mod.M_Nutr.O[i][j]) 
							+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j-1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j-1]))*(Mod.M_Nutr.O[i][j-1] - Mod.M_Nutr.O[i][j])	
							+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j+1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j+1]))*(Mod.M_Nutr.O[i][j+1] - Mod.M_Nutr.O[i][j])
							);
				}

				if(Mod.M_Cell.LD[i][j]==0)
				{
					Mod.M_Nutr.S[i][j] =1.0;
					Mod.M_Nutr.O[i][j] =1.0;
				}
			}
		}
	}

	/*printf("done\n");*/
}


void diff_chip(int rad_pellet)
{

	int i,j,sz,h,nt;
	int rad_sq=0;
	sz = Mod.M_Nutr.sz;
	/*printf("15 here : dt : %f \n",Mod.M_Nutr.dt);*/
	nt = (int)(1.0/Mod.M_Nutr.dt);
	/*printf("1/dt: %f \n",1.0/Mod.M_Nutr.dt);
	printf("nt: %d \n",nt);*/

	for (h=0; h<nt; h++)
	{
		for (i=1; i<sz-1; i++)
		{
			for (j=1; j<sz-1; j++)
			{
				rad_sq = (i-(sz/2-1))*(i-(sz/2-1))+(j-(sz/2-1))*(j-(sz/2-1));
				if(rad_sq<=rad_pellet*rad_pellet)
				{	
					if(Mod.M_Nutr.S[i][j]>0.0)
					{
						Mod.M_Nutr.S[i][j] = Mod.M_Nutr.S[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
								  0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i-1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i-1][j]))*(Mod.M_Nutr.S[i-1][j] - Mod.M_Nutr.S[i][j]) 
								+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i+1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i+1][j]))*(Mod.M_Nutr.S[i+1][j] - Mod.M_Nutr.S[i][j]) 
								+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j-1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j-1]))*(Mod.M_Nutr.S[i][j-1] - Mod.M_Nutr.S[i][j])	
								+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j+1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j+1]))*(Mod.M_Nutr.S[i][j+1] - Mod.M_Nutr.S[i][j])
								) -  Mod.M_Nutr.dt*Mod.M_Nutr.kS[i][j];
					}

					if(Mod.M_Nutr.S[i][j]<=0.0)
					{
						Mod.M_Nutr.S[i][j] = Mod.M_Nutr.S[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
								  0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i-1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i-1][j]))*(Mod.M_Nutr.S[i-1][j] - Mod.M_Nutr.S[i][j]) 
								+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i+1][j]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i+1][j]))*(Mod.M_Nutr.S[i+1][j] - Mod.M_Nutr.S[i][j]) 
								+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j-1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j-1]))*(Mod.M_Nutr.S[i][j-1] - Mod.M_Nutr.S[i][j])	
								+ 0.5*Mod.M_Nutr.DSm[i][j]*Mod.M_Nutr.DSm[i][j+1]/((Mod.M_Nutr.DSm[i][j]+Mod.M_Nutr.DSm[i][j+1]))*(Mod.M_Nutr.S[i][j+1] - Mod.M_Nutr.S[i][j])
								);
					}




					if(Mod.M_Nutr.O[i][j]>0.0)
					{
						Mod.M_Nutr.O[i][j] = Mod.M_Nutr.O[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
								  0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i-1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i-1][j]))*(Mod.M_Nutr.O[i-1][j] - Mod.M_Nutr.O[i][j]) 
								+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i+1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i+1][j]))*(Mod.M_Nutr.O[i+1][j] - Mod.M_Nutr.O[i][j]) 
								+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j-1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j-1]))*(Mod.M_Nutr.O[i][j-1] - Mod.M_Nutr.O[i][j])	
								+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j+1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j+1]))*(Mod.M_Nutr.O[i][j+1] - Mod.M_Nutr.O[i][j])
								) -  Mod.M_Nutr.dt*Mod.M_Nutr.kO[i][j];
					}

					if(Mod.M_Nutr.O[i][j]<=0.0)
					{
						Mod.M_Nutr.O[i][j] = Mod.M_Nutr.O[i][j] + Mod.M_Nutr.d0*Mod.M_Nutr.d0*Mod.M_Nutr.dt/Mod.M_Nutr.tau/Mod.M_Nutr.dx/Mod.M_Nutr.dx*(
								  0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i-1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i-1][j]))*(Mod.M_Nutr.O[i-1][j] - Mod.M_Nutr.O[i][j]) 
								+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i+1][j]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i+1][j]))*(Mod.M_Nutr.O[i+1][j] - Mod.M_Nutr.O[i][j]) 
								+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j-1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j-1]))*(Mod.M_Nutr.O[i][j-1] - Mod.M_Nutr.O[i][j])	
								+ 0.5*Mod.M_Nutr.DOm[i][j]*Mod.M_Nutr.DOm[i][j+1]/((Mod.M_Nutr.DOm[i][j]+Mod.M_Nutr.DOm[i][j+1]))*(Mod.M_Nutr.O[i][j+1] - Mod.M_Nutr.O[i][j])
								);
					}
				}
				
				if(rad_sq>rad_pellet*rad_pellet)
				{
					Mod.M_Nutr.S[i][j] =1.0;
					Mod.M_Nutr.O[i][j] =1.0;
				}	

			}
		}
	}

	/*printf("done\n");*/
}
