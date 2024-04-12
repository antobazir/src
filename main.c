#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "full_study.h"

int main(int argc, char*argv[])
{
	char* ptr;
	char path_f[100] = "/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/";
	printf("main\n\n");
	ptr = strcat(path_f,"starv");
	full_study(path_f,"starv");
	
	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"ref");
	full_study(path_f,"ref");

	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"savy");
	full_study(path_f,"savy");

	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"compens_prol");
	full_study(path_f,"compens_prol");

	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"OS_fragile");
	full_study(path_f,"OS_fragile");

	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"OS_hypos_tol");
	full_study(path_f,"OS_hypos_tol");

	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"OS_hypox_tol");
	full_study(path_f,"OS_hypox_tol");

	ptr = strcpy(path_f,"/home/antonybazir/Documents/Post-doc/metvar_c_chip_scc/results/");
	ptr = strcat(path_f,"OS_hypox_boost");
	full_study(path_f,"OS_hypox_boost");	

	return 0;
}
