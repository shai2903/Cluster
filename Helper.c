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



 /* return the sum of vector */
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

/* return the sum of absolute values from  vector */
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


/*
 * calculate ki*kj\M for i=currLine , saved in saved
 * size- size of  saved
*/
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

/* calculate (v1^T)*v2 */
double dot_product(double *v1, double *v2, int n) {
	int i;
	double sum = 0;

	for (i = 0; i < n; i++)
	{
		sum += v1[i] * v2[i];
	}
	return sum;
}

/* calculating the norm of vector */
void norm(double *v, int n) {
	int i;
	double m = sqrt(dot_product(v, v, n));

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

/* return the max of (v1[i]-v2[i]) for all i={0...n} */
double max_differ(double *v1, double *v2, int n) {

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

/* generate new random vector b0 of size n */
void generateRandom(double *b0, int n)
{
	int i;

	for(i = 0; i <n; i++)
	{
		/* initialize the first random vector */
		b0[i] = (double) rand(); /* returns a pseudo-random integer between 0 and RAND_MAX */
	}
}

/* compute s according to vec , n-size s and vec */
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

/* count all the '1' in s */
int countOne(double *s, int n)
{
	int i;
	int counter=0;

	for(i=0;i<n;i++)
		if(s[i]==1)
			counter++;
	return counter;
}

/*
 * divide to groups according to s
 * s=1 go to group division[1]
 * s=-1 go to group division[0]
 * */
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



/* mult k (according to the index in g) with vector v^T : k*v^T*/
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

/*put 1 in all of array*/
void allOneDouble(double *array,int size)
{
	 int i;

	 for( i=0;i<size;i++)
		 array[i]=1;
}

/*put new val in max and loc */
void changeLocMax (double *max,int *loc ,double data, int i)
{
	*max  = data;
	*loc = i;
}



/* return the index of the highest value in the array
 * if checkNeeded==1 -> return the highest from s only if unmoved[i]==1 unmoved
 * otherwise return the highest from s
 * */
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
 /*bulid g[i]=i till ng*/
void buildFirstG(int *group,int ng)
{
	int i;
	group[0]=ng;
	for( i=1 ;i <ng+1 ;i++)
	{

				group[i]=i-1;

	}

}


/*build the inverse of g*/
void buildInverse(int *o,int* g,int ng)
{
	int j;
	for(j=0;j<ng;j++)
		o[g[j+1]]=j;


}
