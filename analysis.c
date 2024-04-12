#include <string.h>
#include <math.h>
#include "structdef.h"
#include <stdio.h>
#include <stdlib.h>

void analysis(char* folder)
{


	int i,j,l,k,m;
	char suffix[6]; 
	char exp[4];
	char path_r[100] = "../results/";
	char path_f[100] = "../plots/";
	char path_cpy[100], pc2[100], pc3[100], pc4[100];
	
	FILE *f;
	FILE *f2, *f3, *f4;
	Model *Mod;
	
	strcat(path_r,folder);
	strcpy(path_cpy,path_r);
	
	for(m=1;m<=3;m++)
	{
		switch(m)
		{
			case 1:	
				strcpy(exp,"/Id");
				break;	
	
			case 2:			
				strcpy(exp,"/Gl");
				break;

			case 3:			
				strcpy(exp,"/Ox");
				break;

		}
		strcat(path_cpy,exp);
		printf("%s \n",path_cpy);
		Mod = (Model*) malloc (sizeof (Model));
		f = fopen(path_cpy,"r+");
		l=0;
		while(! feof( f ))
		{
			strcpy(path_cpy,path_r);
			strcpy(path_cpy,folder);
			strcpy(pc2,path_cpy);/*Grid*/
			strcpy(pc2,"Grid"); strcpy(pc2,exp);
			strcpy(pc3,path_cpy);/*S*/
			strcpy(pc3,"S"); strcpy(pc3,exp);
			strcpy(pc4,path_cpy);
			strcpy(pc4,"S_center"); strcpy(pc4,exp);
			sprintf(suffix, "%d.dat", l);
			strcpy(pc2,suffix);strcpy(pc3,suffix);
			printf("%s \n",pc2);
			printf("%s \n",pc3);
			printf("%s \n",pc4);
			fread(Mod,sizeof(Model),1,f);
			f2 = fopen(pc2,"w"); f3 = fopen(pc3,"w");f4 =fopen(pc4,"w");
			for(i=0;i<(*Mod).M_Nutr.sz;i++)
			{
				for(j=0;j<(*Mod).M_Nutr.sz;j++)
				{
					fprintf(f2,"%d ",(*Mod).M_Cell.Grid[i][j]);
					fprintf(f3,"%3.2f ",(*Mod).M_Nutr.S[i][j]);

				}
				fprintf(f2,"\n");
			}
			fprintf(f2,"%d \t %3.2f",l,(*Mod).M_Nutr.S[(*Mod).M_Nutr.sz/2-1][(*Mod).M_Nutr.sz/2-1]);
			printf("\n");


			l++;

		}

	}

	return;
	/*for(l=0;l<50;l++)
	{
		strcpy(path_cpy,path_f);
		sprintf(folder, "starv/Grid/Id%d.dat", l);
		strcat(path_cpy,folder); 
		printf("%s \n",path_cpy);
		Mod = (Model*) malloc (sizeof (Model));
		fread(Mod,sizeof(Model),1,f);
		f2 = fopen(path_cpy,"w");
		for(i=0;i<(*Mod).M_Nutr.sz;i++)
		{
			for(j=0;j<(*Mod).M_Nutr.sz;j++)
			{
				fprintf(f2,"%d ",(*Mod).M_Cell.Grid[i][j]);
			}
			fprintf(f2,"\n");
		}
		printf("\n");
		free(Mod);

		
		
	}
	fclose(f);

	f = fopen(path_r,"r+");
	for(l=0;l<50;l++)
	{
		strcpy(path_cpy,path_f);
		sprintf(folder, "starv/S/Id%d.dat", l);
		strcat(path_cpy,folder); 
		printf("%s \n",path_cpy);
		Mod = (Model*) malloc (sizeof (Model));
		fread(Mod,sizeof(Model),1,f);
		f2 = fopen(path_cpy,"w");
		for(i=0;i<(*Mod).M_Nutr.sz;i++)
		{
			for(j=0;j<(*Mod).M_Nutr.sz;j++)
			{
				fprintf(f2,"%f ",(*Mod).M_Nutr.S[i][j]);
			}
			fprintf(f2,"\n");
		}
		printf("\n");
		free(Mod);

		
		
	}
	
	fclose(f);*/

	/*f = fopen(path_r,"r+");
	strcpy(path_cpy,path_f);
	sprintf(folder, "starv/S_center_Id.dat");
	strcat(path_cpy,folder); 
	for(l=0;l<50;l++)
	{
		Mod = (Model*) malloc (sizeof (Model));
		fread(Mod,sizeof(Model),1,f);
		f2 = fopen(path_cpy,"w");
				fprintf(f2,"%f ",(*Mod).M_Nutr.S[i][j]);
			}
			fprintf(f2,"\n");
		}
		printf("\n");
		free(Mod);

		
		
	}
	
	fclose(f);*/

	
	

}  
