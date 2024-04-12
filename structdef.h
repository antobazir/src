#ifndef INCLUDE_STRUCTDEF_H
#define INCLUDE_STRUCTDEF_H

#define SZ 400

	typedef struct Nutrs
	{
		/*nutrient*/
		float S[SZ][SZ];
		float O[SZ][SZ];

		/*Diffusion*/
		float DSm[SZ][SZ];
		float DOm[SZ][SZ];
		float DS_med;
		
		/*consommation*/
		float kS[SZ][SZ];
		float kO[SZ][SZ];

		/* model parameters*/
		float dx;
		float dt;
		float d0;
		float tau;
		int sz;
	}Nutr;   

	typedef struct Cells
	{
		/* Cell & State Grids*/
		int Grid[SZ][SZ];
		int LD[SZ][SZ];
		unsigned char state_mat[SZ][SZ];
		float state[SZ*SZ][10];
		/*|1 d_time| 2 div_ind | 3 chg_timer |4 kS 
		|5 dkS |6 kO |7 dkO|8 row| 9 cols| 10 prt| */

		/*limits*/
		float S_prol;
		float S_maint;
		float O_norm;

		/*other variables*/
		int N_Cell; /*all cells (dead or alive) in the model*/
		int N_Dead;
		int N_Live;
		int reac_time; /*time for consumption changes*/
		int n_min; /*cell cycle reaction*/
		int n_pts;
		int max_rad_sq;
	}Cell;

	typedef struct Models
	{
		Cell M_Cell;
		Nutr M_Nutr;
	}Model;


#endif /* INCLUDE_FOO_H */

