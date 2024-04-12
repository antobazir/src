/* Implémentation 170324 test lecture/écriture et construction de structures*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>        
#include <sys/stat.h>  

#define SZ 10 
	struct Nutr {
		float S[SZ][SZ];
		float O[SZ][SZ];
	};   

int metvar_f(float kS, float kO ,char* behavior ,char* file)
{
	float kO_tissue = kO;
	float kS_tissue = kS;

	struct Nutr Nutr_w;
	struct Nutr Nutr_r;
	
	int i=0,j=0;
	FILE *f;
	FILE *f2;

	f = fopen("Id","a+");
	printf("kS = %f \n",kS); 

	for (i=0; i<SZ; i++)
	{
		for (j=0; j<SZ; j++)
		{
			Nutr_w.S[i][j] = 1.0;
			Nutr_w.O[i][j] = 0.8;
		}
	}

	/*saving variables*/
	/*fwrite(S, sizeof(float), 100, f);*/
	fwrite(&Nutr_w,sizeof(struct Nutr),1,f);
	/*fwrite(O, sizeof(float), sizeof(O), f);*/
	fclose(f);

	f2 = fopen("Id","r");
	fread(&Nutr_r, sizeof(struct Nutr), 1, f2);
	/*fread(O_r, sizeof(float), sizeof(O), f2);*/
	fclose(f2);

	/*printing the save variable*/
	for (i=0; i<SZ; i++)
	{
		for (j=0; j<SZ; j++)
		{
			printf("%f ",Nutr_r.S[i][j]);
		}
		printf("\n");
	}
	
}
