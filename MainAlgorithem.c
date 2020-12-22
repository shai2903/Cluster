/*
 * MainAlgorithm.c
 *
 *  Created on: 19 Sep 2020
 *      Author: Shai
 */

#include <time.h>
#include <math.h>
#include "MainAlgorithem.h"

#include "Helper.h"


#include <stdlib.h>


double algorithm2 (ModMatrix *B,int ng, double *s,double *eigenVector,double *helper,double *helper2,int first,double *saved)
{

	double eigenVal,Q;
	int isDivisble;

	/*1.compute leading eigen_pair*/
	/*get leading eigen-pair*/
	eigenVal=computeLeadingEigenPair(B,eigenVector,helper,helper2,first,saved);

	/*2.check if eigen_value<=0*/
	isDivisble=isPositive(eigenVal);
	if(isDivisble==0)
	{
		return eigenVal;
	}

	/*3. compute s*/
	computeS(eigenVector,s,ng);

	/*4. calculate Q and check negativity*/
	Q=calculteQ(B,s,helper,helper2,saved);

	isDivisble=isPositive(Q);
	if(isDivisble==0)
	{
		allOneDouble(s,ng);
		return eigenVal;
	}


	return eigenVal;
}




void algorithm4(double *s,ModMatrix *B,int* indices,double *helperRes,double *helperCalc,double *savedQ,double *saved){
	double q0, d_q,scoreMax,scoreCurr,improveMax,improvePrev,improveCurr,resk;
	int i,j,m, im,nP,p,index,isFirstRoundLoop2, isFirstRoundLoop1;

	Element * prev,*maxElement, *prevMax ,*unmoved, *tmp;
	unmoved=NULL;
	d_q=0,im=0.0,improveMax = 0.0,scoreMax = 0.0;
	isFirstRoundLoop1 = 1,isFirstRoundLoop2 = 1,im = 0,nP=B->ng;

	do{
		initializUnmoved(&unmoved,nP);

		for (i=0;i<nP;i++){
			 prev=NULL,prevMax=NULL;
			 tmp=unmoved;
		  	 maxElement=tmp;
			 if(isFirstRoundLoop1 ==1)
			 {
				 q0=2*calculteQ(B,s,helperRes,helperCalc,saved);/*caclute Q according to new s*/
				 isFirstRoundLoop1 =0;
				 resk = multLineVec(B->k, B->g, s, B->ng);
			 }
			 else
			 {
				 q0=savedQ[m];
			 }

			 isFirstRoundLoop2 = 1;
			 /* trying to find the highest quality when moving nodes from one group to another */
			 while (tmp != NULL)
			 {
			 	 j=tmp->col;
				 s[j]=(-1)*s[j];
				 savedQ[j]=caculateNewQ(q0,j,s,B, resk);
				 if (isFirstRoundLoop2 == 1)
				 {
					 scoreMax = savedQ[j] - q0;
					 m = j ,isFirstRoundLoop2 = 0;
     			 }
				 else
				 {
					 scoreCurr = savedQ[j] - q0;
					 if (scoreMax < scoreCurr)
					 {
						 scoreMax = scoreCurr;
						 m = j;
						 maxElement=tmp;
						 prevMax=prev;
					 }
				 }

				 s[j]=(-1)*s[j];
				 prev=tmp;
				 tmp=tmp->next;
		 }
		 s[m]=(-1)*s[m];
		 indices[i]=m;

		 resk = multLineVec(B->k, B->g, s, B->ng) ;
		 if(i==0){/*saved the max of all indexes*/
			 improvePrev = scoreMax;
			 improveMax = scoreMax;
			 im = i;

		 }
		 else{
			 improveCurr = improvePrev + scoreMax;
			 improvePrev = improveCurr;
			 if (improveMax < improveCurr)
			 {
				 improveMax = improveCurr;
				 im = i;
			 }
		 }
		 deleteItem(&unmoved,&prevMax,&maxElement);/*delete the max from unmvoed*/
	 }

		isFirstRoundLoop1 =1;
	 for(p=nP-1;  p > im ;p--){
		 index=indices[p];
		 s[index]=(-1)*s[index];
	 }
	 if(im==(nP-1)){
		 d_q=0;
	 }
	 else{
		 d_q=improveMax;
	 }

	}while(isPositive(d_q));
}





ElementA* algorithm3 (spmat *A,int *k, int M, int ng ){

	ElementA* P,*O;
	ModMatrix *B;
	int *group,*currnet,*counterO,*indices,*binaryA,*row,*inverse;
	int isFirstLoop,n,count;
	double *s,*helper,*helper2,*helper4 ,*helper3,*eigenVector;
	int **division;

	double eigenVal;

	group=(int*)malloc(sizeof(int)*(ng+1));
	buildFirstG(group,ng);

	P=NULL,O=NULL;
	count=0,isFirstLoop=1;

	division=(int**)malloc(sizeof(int*)*2);

	/*add first group to P*/
	addToListA(&P,group);

	/*built b_hat shift*/
	B=allocateMatrix(ng,M,A,k);

	s=(double*)malloc(sizeof(double)*(ng));
	eigenVector=(double*) malloc((ng)*sizeof(double));
	indices=(int*)malloc(sizeof(int)*(ng));
	helper=(double*)malloc(ng*sizeof(double));
	helper2=(double*)malloc(ng*sizeof(double));
	helper3=(double*)malloc(ng*sizeof(double));
	helper4=(double*)malloc(ng*sizeof(double));
	binaryA=(int*)malloc(ng*sizeof(int));
	row=(int*)malloc(ng*sizeof(int));
	inverse=(int*)malloc(ng*sizeof(int));
	if(s==NULL ||eigenVector==NULL ||  indices==NULL || helper==NULL||helper2==NULL)
	{
		printf("SP_ALLCOATE_PROBLEM");
		 exit(EXIT_FAILURE);
	}
	if(helper3==NULL ||helper4==NULL ||  binaryA==NULL || row==NULL||inverse==NULL)
	{
			printf("SP_ALLCOATE_PROBLEM");
			 exit(EXIT_FAILURE);
	}

	/*3.repeat until P is empty*/
	while( P !=NULL)
	{
		/*3.1 remove group g from P*/
		currnet=removeFirst(&P);
		n=currnet[0];

		B->ng=n;
		B->g=currnet;

		buildInverse(inverse,B->g,n);
		B->inverseG=inverse;
		if(!isFirstLoop)
		{

			B->Ag=BuildAg(B->A,B->g,B->ng, binaryA ,row);
		}
		else
		{
			B->Ag=B->A;
		}

		allOneDouble(s,n);
		/*3.2 divide g into g1 and g2 with algoritem 2*/
		eigenVal=algorithm2(B,n,s,eigenVector,helper,helper2,isFirstLoop,helper3);

		/*algo 4*/
		if(isPositive(eigenVal) || eigenVal<(-1)*epsilon)
		{
			algorithm4(s,B,indices,helper,helper2,helper3,helper4);

		}

		makeDivision(currnet,s,division,n);
		free(currnet);

		/*3.4 add to O any group of size 1 , add to P any group larger than 1*/
		count+=addToOorP(&P,&O,division,0,n);
		count+=addToOorP(&P,&O,division,1,n);
		if(!isFirstLoop)
		{
				B->Ag->free(B->Ag);
		}
		isFirstLoop=0;

	}

	counterO=(int*)malloc(sizeof(int));
	counterO[0]=count;
	addToListA(&O,counterO);
	free(division);
	freeMatrix(B);
	free(eigenVector),free(helper2),free(indices),free(helper4),free(helper),free(inverse),free(binaryA);
	free(helper3),free(row),free(s);
	return O;
}


