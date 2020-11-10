#ifndef _SPMAT_H
#define _SPMAT_H

#include <stdio.h>


/**
 *spmat.h Summary:
 *
 *module for sparse matric
 *
 *add_row -add row for A
 *free - free A
 *mult - nult A with vector
 *spmat_allocate_list - allocate space for A
 *calculateLineB  - calculte line in matrix B (from A)
 *one_mult - mult line j from A with v
 *BuildAg - bulid mini A according to g
 *getRowAccordingToG - get the correvt line from Ag


 */


typedef struct _spmat {
	/* Matrix size (n*n) */
	int		n;

	/* Adds row i the matrix. Called before any other call,
	 * exactly n times in order (i = 0 to n-1) */
	void	(*add_row)(struct _spmat *A, const int *row, int i,int size);

	/* Frees all resources used by A */
	void	(*free)(struct _spmat *A);

	/* Multiplies matrix A by vector v, into result (result is pre-allocated) */
	void	(*mult)(const struct _spmat *A,int ng,const double *v, double *result,int *o);




	/* Private field for inner implementation.
	 * Should not be read or modified externally */
	void	*private;
} spmat;

/* Allocates a new linked-lists sparse matrix of size n */
spmat* spmat_allocate_list(int n);


/*
 *calculate lineB=lineA- lineKM*/
/*n - size of lineKm
 *index - current line in A
 *g- the groups from B shifted
 * */
void calculateLineB(spmat *A, double *lineKM,int n,int index, int *o);

/*
 *  mult line j from A with v
 * */
double one_mult(const struct _spmat *A,const double *v,int j,int *o) ;
/* bulid mini A according to g*/
spmat* BuildAg(spmat *A, int *g,int n,int *binary,int *row);

/**
 * build matrix A from Input_mat
 * return M=sum of all degree
 */
int BulidA (spmat *A,int *k,FILE *Input_mat,int n);


#endif


