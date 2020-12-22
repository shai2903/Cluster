/*
 * Helper.c
 */


#include "Helper.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

double epsilon = 0.00001;




double getSum(double *vector, int n)
{
	int i;
	double sum=0;
	for(i=0;i<n;i++ )
	{
		sum+=vector[i];
	}
	return sum;

}


double getSumAbs (double *vector,int n)
{
	int i;
	double sum=0.000;
	for(i=0;i<n;i++ )
	{
		sum+=fabs(vector[i]);
	}
	return sum;
}



void calculateKM(int *k, int M, int *g, int currLine, int size, double *saved)
{
	int i;
	int ki;
	double ki_M;

	ki=k[currLine];

	/* calculate ki/M */
	ki_M=(double)ki/M;
	for(i=0;i<size;i++)
	{
		/* calculate ki*kj/M */
		saved[i]=ki_M*k[g[i+1]];
	}
}


double dotProduct(double *v1, double *v2, int n) {
	int i;
	double sum = 0;

	for (i = 0; i < n; i++)
	{
		sum += v1[i] * v2[i];
	}
	return sum;
}


void norm(double *v, int n) {
	int i;
	double m = sqrt(dotProduct(v, v, n));

	if(m<epsilon && m> (-1)* epsilon)
	{
		printf("SP_DIVISION_BY_ZERO");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < n; i++)
	{
		v[i] = v[i] / m;
	}
}


double maxDiffer(double *v1, double *v2, int n) {

	double differ;
	int i;
	double max =0; /* the max value of differ between each corresponding pair of values in v1 and v2 */
	for (i = 0; i < n; i++) {
		differ=fabs(v1[i]) - fabs(v2[i]); /* the differ between corresponding pair of values in v1 and v2 */
		if (isPositive(differ -max))
		{
			max = differ;
		}
	}
	return max;
}


void generateRandom(double *b0, int n)
{
	int i;

	for(i = 0; i <n; i++)
	{
		/* initialize the first random vector */
		b0[i] = (double) rand(); /* returns a pseudo-random integer between 0 and RAND_MAX */
	}
}


void computeS(double *vec, double *s, int n)
{
	int i;

	for(i=0;i<n;i++)
	{
		if(isPositive(vec[i]))
			s[i]=1;
		else
			s[i]=-1;
	}
}


int countOne(double *s, int n)
{
	int i;
	int counter=0;

	for(i=0;i<n;i++)
		if(s[i]==1)
			counter++;
	return counter;
}


void makeDivision(int * P,double *s, int **division, int n)
{
	int i,n1,counterOne,counterZero;

	n1=countOne(s,n),counterOne=1,counterZero=1;

	division[0]=(int*)malloc(sizeof(int)*((n-n1)+1));
	if(division[0]==NULL)
	{
		 printf("SP_ALLCOATE_PROBLEM");
					exit(EXIT_FAILURE);
	}
	division[1]=(int*)malloc(sizeof(int)*(n1+1));
	if(division[1]==NULL)
	{
		 printf("SP_ALLCOATE_PROBLEM");
					exit(EXIT_FAILURE);
	}
	for(i=1;i<n+1;i++)
	{
		if(s[i-1]==1)
		{
			division[1][counterOne]=P[i];
			counterOne++;
		}
		else
		{
			division[0][counterZero]=P[i];
			counterZero++;
		}
	}
	/*first cell is the size of group*/
	division[1][0]=counterOne-1;
	division[0][0]=counterZero-1;

}




double multLineVec(int *k, int *g, const double *v, int n) {
	double sum;
	int i;
	sum=0.0;

	/* while the line is not over*/
	for(i=0;i<n;i++)
	{
		sum+=k[g[i+1]]*v[i];
	}
	return sum;
}


void allOneDouble(double *array,int size)
{
	 int i;

	 for( i=0;i<size;i++)
		 array[i]=1;
}


void changeLocMax (double *max,int *loc ,double data, int i)
{
	*max  = data;
	*loc = i;
}



 int max_location(double *s,int size,int *unmoved,int checkNeeded){
	 int i,location;
	 double max;
	 location=-1;

	 for (i = 0; i <size; i++){
		 if(checkNeeded==0)
		 {
			 if(location==-1)
			 {
				 changeLocMax(&max,&location,s[i],i);

			 }
			 else
			 {
				if (isPositive(s[i] - max)){
					changeLocMax(&max,&location,s[i],i);
				}
			}
		 }
		 else
		 {
			 if( unmoved[i]==1)
			 {
				 if(location==-1)
				 {
					 changeLocMax(&max,&location,s[i],i);

				 }

				 else
				 {
					 if (isPositive(s[i] - max)){
						 changeLocMax(&max,&location,s[i],i);

						}
				 }
			 }
		 }
	 }
	 return location;
 }

void buildFirstG(int *group,int ng)
{
	int i;
	group[0]=ng;
	for( i=1 ;i <ng+1 ;i++)
	{

				group[i]=i-1;

	}

}



void buildInverse(int *o,int* g,int ng)
{
	int j;
	for(j=0;j<ng;j++)
		o[g[j+1]]=j;


}
