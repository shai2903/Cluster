
#include <stdlib.h>
#include "ModMatrix.h"
#include "Helper.h"

#include <string.h>
#include <float.h>


ModMatrix* allocateMatrix( int ng,int M, struct _spmat *A, int *k)
{

	ModMatrix *b;
	b=(ModMatrix*) malloc(sizeof(struct ModMatrix));

	b->M=M;
	b->f=(double*) calloc(ng,sizeof(double));
	b->norm=0;
	b->A=A;
	b->k=k;

	return b;
}


void freeMatrix(ModMatrix *B)
{
	free(B->f);
	free(B);
}



void multKM(ModMatrix* B, double* v, double* res,double* helperCalc)
{
	int i, n;
	int* g;

	double sum;
	g = B->g; /* get the lines from B in B[g] */
	n = B->ng; /* get the size of matrix B_hat[g] */


	for (i = 0; i < n; i++)
	{

		/* mult (ki*kj/M)*ezer for each line */
		helperCalc[i] = (double)(B->k)[g[i + 1]] *v[i];
		
	}
	sum = getSum(helperCalc, n) * (1.000/B->M);

	for (i = 0; i < n; i++)
	{
		res[i] = sum * (B->k)[g[i + 1]];
	}
	


}

void multF(ModMatrix *B, double *v, double *res)
{
	int i;
	int *g;
	int n=B->ng;

	g=B->g;

	for(i=0;i<n;i++)
	{
		res[i]=B->f[g[i+1]]*v[i];
	}
}


void multB(ModMatrix *B, double *v, double *res,double* helperCalcB,double *helperKm)
{

	int i;


	/* calculate A*ezer and the result saved in resMultA */
	(B->A)->mult(B->Ag,B->ng,v,res,B->inverseG);

	/* calculate (ki*kj/M)*ezer and the result saved in resMultA */
	multKM(B, v, helperCalcB,helperKm);

	for(i=0;i<B->ng;i++)
	{
			res[i]-=helperCalcB[i];
	}

	/* calculate f*I*ezer (f with shift or without) */
	multF(B,v,helperCalcB);
	for(i=0;i<B->ng;i++)
	{
				res[i]-=helperCalcB[i];
	}

}


void addNormToF(ModMatrix *B, double norm)
{
	int i;
	int *g;
	g=B->g;
	for(i=0;i<(B->ng);i++)
	{
		(B->f)[g[i+1]]-=norm;
	}
}


double Shift(ModMatrix *B,double* helperResB,int first)
{
	/*double max=0.0;*/
	double sumAbsLine;
	double sumLine;
	int n,i;
	int *g;

	n=B->ng; /* get the size of matrix B_hat[g] */

	g=B->g; /* get the lines from B in B[g] */



	for(i=0;i<n;i++)
	{
		/* calculate the second(kikj/M) part from B */
		calculateKM(B->k,B->M,g,g[i+1],n,helperResB);


		/* calculate line i of B (=lineA-lineKM) */
		calculateLineB(B->Ag,helperResB,n,i,B->inverseG);

		/* sum of line i from B */
		sumLine=getSum(helperResB,n);

		/* save the sum in ModMatrx for each line */
		(B->f)[g[i+1]]=sumLine;

		/* calculate B_hat */
		helperResB[i]-=sumLine;

		if(first==1)
		{
			/* calculate absolute sum of line */
			sumAbsLine=getSumAbs(helperResB,n); /* calculate the abs sum of line */

			if(i==0)
			{
				B->norm=sumAbsLine;
			}
			else
			{
				if(B->norm<sumAbsLine)
					B->norm=sumAbsLine;
			}
		}

	}

	/* calculate shift */
	addNormToF(B,B->norm);

	return B->norm;
}




double findEigenValue(ModMatrix *B,double* bk,double *helperRes,double *helperCalc,double *helperMultB)
{
	double denominator,numerator ;

	/*calculate the denominator of formula*/
	denominator=dotProduct(bk,bk,B->ng);
	if(denominator<epsilon && denominator> (-1)* epsilon)
		{
			printf("SP_DIVISION_BY_ZERO");
			exit(EXIT_FAILURE);
		}

	/*calculate right side of numerator of formula  (A*bk) */
	multB(B,bk,helperCalc,helperRes,helperMultB);

	/*calculate left side of numerator of formula bk*(A*bk)*/
	numerator=dotProduct(bk,helperCalc,B->ng);

	return (numerator/denominator);


}


double calculteQ(ModMatrix *B,double *s,double *helperResMult,double *helperCalc,double *helperMultB)
{
	/*double *Bs;*/
	double resMult;
	double Q;


	/*calculate Bs*/
	multB(B,s,helperResMult,helperCalc,helperMultB);

	/*calculate s^T *(Bs)*/
	resMult=dotProduct(s,helperResMult,B->ng);

	Q=0.5*resMult;

	return Q;
}




double powerItertion(ModMatrix *B,double* res,double *helperCalc,double *random,double *helperMultB)
{
	double differ;

	double eigenValue;
	/*double *tmp;*/
	int size_tmp;
	int counter=0;
	/* int i;*/
	generateRandom(random,B->ng);

	size_tmp = (B->ng)*sizeof(double);

	differ = DBL_MAX;

	while (isPositive(differ)) {
		if(counter>100000*B->ng)
		{

			printf("INFINTE_LOOP");
				exit(EXIT_FAILURE);
		}
		multB(B,random,res,helperCalc,helperMultB);

		norm(res,B->ng);

		differ = maxDiffer(random, res,(B->ng));



		memcpy(random, res, size_tmp);
		counter++;

	}
	/*find EigenValue from the formula (2 Leading Egienpair)*/
	eigenValue=findEigenValue(B,res,helperCalc,random,helperMultB);
	return eigenValue;
}


double computeLeadingEigenPair(ModMatrix *B,double *eigenVector,double *helperRes,double *random,int first,double *helperMultB)
{


	double tmpEigenVal;

	if(first==1)
	{
		/*calculate norm of B_hat and shift B*/
		B->norm=Shift(B,helperRes,first);

	}
	else
	{
		Shift(B,helperRes,first);
	}

	/*Calculate eigenValue*/
	tmpEigenVal=powerItertion(B,eigenVector,helperRes,random,helperMultB);

	/*return b_hat_shifted  to b_hat (un-shifted)*/
	addNormToF(B,(-1)*B->norm);

	return (tmpEigenVal-B->norm);
}


double caculateNewQ(double Q, int j, double* s, ModMatrix* B,double resk)
{


	double sumLine;
	int* g;
	double bjj;
	double kiM;

	double finalMult;
	double resA = 0.0;


	g = B->g; /* get the lines from B in B[g] */



	s[j] = (-1) * s[j];

	/* mult (ki*kj/M)*s  */
	kiM = (double)(B->k)[g[j + 1]] / (B->M);

	resA = oneMult(B->Ag, s, j, B->inverseG);

	finalMult = resA - resk* kiM - (B->f)[g[j + 1]] * s[j];

	bjj = (0 - kiM * (B->k)[g[j + 1]] - (B->f)[g[j + 1]]);

	sumLine = 4 * s[j] * finalMult;
	s[j] = s[j] * (-1);


	return (Q - sumLine + 4 * bjj);


}
