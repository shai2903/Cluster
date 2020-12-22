/*
 * ModMatrix.h
 */


#ifndef MODMATRIX_H_
#define MODMATRIX_H_
#include "spmat.h"

/**
 *ModMatrix.h Summary:
 *
 *module for matrix B_hat
 *
 *allocateMatrix - allocate space for matrix
 *freeMatrix - free B
 *Shift - calculte shif of matrix
 *addNormToF - add the norm to F
 *multB - mult B in v
 *multF  - mult f in v
 *findEigenValue - find eigen value given eigen vector
 *computeLeadingEigenPair - calculte LeadingEigenPair
 *powerItertion - do powerItertion
 *calculteQ - calculte Q
 *caculateNewQ - calculte Q from given Q (when s changed in one cell only)
 */


/**
 * represent B_hat
 * g- the cols from B (sub matrix)
 * ng- the size of g
 * f- sum of lines from B
 * M - sum of all degrees (sum of k)
 * A-sparse matrix
 * Ag - sparse matrix with line from g
 * k - degree of all nodes (size ng)
 * norm - norm of matrix ( nXn)
 */
typedef struct ModMatrix {
	int* g;
	int* inverseG ;
	int ng;
	double *f;/* calculated in Shift*/
	int M;/*const*/
	spmat *A;/*const*/
	spmat *Ag;

	int *k;/*const*/
	double norm;/*const*/

}ModMatrix;

/* return ModMatrx after allocate space for f */
ModMatrix* allocateMatrix( int ng,int M, struct _spmat *A, int *k);

/* free all memory allocated for b */
void freeMatrix(ModMatrix *b);

/* return the 1-Norm of B_hat and calculate shift
 * B - matrix
 *first - 1 if first time calculate norm
 *helperResB - vector for calculation
 * */
double Shift(ModMatrix *B,double* helperResB,int first);

/* calculate f=f-norm */
void addNormToF(ModMatrix *B, double norm);

/**
 * mult B with ezer and saved the result in res
 *
 * B - matrix B
 * ezer - vector
 * res -calculated vector saved in res
 * helperResB,helperKm-helper vector for calculation
 *
 * calculate (A-kikj\M)*ezer
 */
void multB(ModMatrix *B, double *v, double *res,double* helperCalcB,double *helperKm);


/*
 * mult f*I*ezer
 * f  line vector with sum of each line
 * saved calculation in res
 * */
void multF(ModMatrix *B, double *ezer, double *res);


/*find the eigenValue according to Formula in the assignment*/
/*
 * B - matrix B
 * bk - eigenVector
 * helperRes - helper vector for result of mult B*bk
 * helperCalc,helperMultB - helper vector for calculation mult B*bk
 * */
double findEigenValue(ModMatrix *B,double* bk,double *helperRes,double *helperCalc,double *helperMultB);

/*compute leading eigenPair
 * B- matrix
 * eigenVector - the calculated eigenVector
 * helperRes,saved - vector for calculation
 * random - vector for random vec in powerItertion
 *  first - if first=1 - calculate shift otherwise dont
 * */
double computeLeadingEigenPair(ModMatrix *B,double *eigenVector,double *helperRes,double *random,int first,double *saved);

/*
 * B - b_hat_shifted matrix
 * res - the eigen vector calculated
 * helperCalc,saved- helper or calculation
 * random - vector for the first vector for powerItertion
 * */
double powerItertion(ModMatrix *B,double* res,double *helperCalc,double *random,double *saved);



/*
 * calculate Q according to : s^TBs
 * helperResMult -helper vector for saved result
 * helperCalc,helperMultB - helper vector for calculation
 * */
double calculteQ(ModMatrix *B,double *s,double *helperResMult,double *helperCalc,double *helperMultB);

/*
 *  calculte Q from given Q (when s changed in one cell only -j )
 *
 */
double caculateNewQ(double Q, int j, double* s, ModMatrix* B,double resk);
#endif /* MATRIXMOD_H_ */
