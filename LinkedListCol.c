/*
 * LinkedListCol.c
 *
 *  Created on: 17 Sep 2020
 *      Author: Shai
 */

#include <time.h>
#include "LinkedListCol.h"
#include <stdio.h>
#include <stdlib.h>

/* free all nodes */
void delete_list(List lst) {
	if(lst!=NULL) {
		delete_list(lst->next);
		free(lst);
	}
}

/*
 * binaryA[g[i+1]]=0 for every i
 * ng - size of binaryA
 * */
void initializBinaryA(int ng, int* g,int * binaryA)
{
	int i;
	for (i = 0; i < ng; i++)
		binaryA[g[i + 1]] = 0;
}

/*bulid vector binaryA
 * binaryA[i]=1 -> if A[line,i]=1
 * binaryA[i]=0 - >otherwise
 *
 * */
void buildBinaryA(List *lst,int *binaryA ,int ng,int *g)
{
	int last;
	initializBinaryA(ng,g, binaryA);

	last=g[ng];
	while ((*lst) != NULL)
	{
		binaryA[(*lst)->col]=1;
		if ((*lst)->col >= last)
		{	
			
			break;
		}
		lst = &((*lst)->next);
	}

}
/* mult lst( size of lst = 1xng )  with vector v^T*/
double mul_single_line (List *lst,const double *v,int *o) {
	double sum;
	int j;

	sum=0.0;



	while ((*lst) != NULL)
	{
		j=o[(*lst)->col];
		sum+=v[j];
		lst = &((*lst)->next);

	}


	return sum;

}

/*
 * delete toDelete Element in List
 * prev - the Element before toDelete
 * */
void deleteItem(Element **List,Element **prev,Element **toDelete)
{

	if(*prev==NULL)
	{
		*List=(*List)->next;

		free(*toDelete);
		return;

	}
	((*prev)->next)=(*toDelete)->next;

	free(*toDelete);

}

/*
 * bulid unmoved
 * bulid linkes list , cell in index i = i ,till nP
 *
 * */

void initializUnmoved(Element **unmoved,int nP)
{
	int i;
	Element **tmp,*newNode;

	tmp=unmoved;
	for(i=0 ; i<nP;i++)
	{


		/* create the node we need to add*/
		newNode=(Element*)malloc(sizeof(Element));

		if(newNode==NULL)
		{
			 printf("SP_ALLCOATE_PROBLEM");
						exit(EXIT_FAILURE);
		}
		newNode->col=i;
			/*printf("%d",row[j] );*/
		newNode->next=NULL;

			/* if it is not the first node in tmp */
			if(*tmp!=NULL) {
				/* add the new node, and advanced p */
				(*tmp)->next=newNode;
				tmp=&((*tmp)->next);
			}
			else {
				(*tmp)=newNode;
			}

	}
}
