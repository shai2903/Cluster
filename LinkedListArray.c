/*
 * Linkedlist.c
 *
 *      Author: shai
 */




#include <assert.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "SPBufferset.h"

#include <stdlib.h>

#include "LinkedListArray.h"

void freeLinkedList(ElementA * lst)
{

	 ElementA * tmp;
	while(lst != NULL)
	{
		tmp=lst;

		lst=lst->next;
		free(tmp->array);

		free(tmp);
	}

}




void addToListA(ElementA ** A, int *g)
{


	ElementA * tmpNode;

	/* create the node we need to add*/
	tmpNode=(ElementA *)malloc(sizeof(ElementA));
	if(tmpNode==NULL)
	{
		 printf("SP_ALLCOATE_PROBLEM");
					exit(EXIT_FAILURE);
	}
	tmpNode->array=g;

	if((*A)!=NULL)
	{
		tmpNode->next=*A;


	}
	else
	{

		tmpNode->next=NULL;

	}

	(*A)=tmpNode;


}


int addToOorP(ElementA ** P,ElementA ** O,int ** division,int i,int n)
{
	if(division[i][0]==0)
	{
		free(division[i]);
		return 0;
	}
	if(division[i][0]==1 || division[i][0]==n)
	{
			     addToListA(O,division[i]);
			 	return 1;
	}
	else
	{
				addToListA(P,division[i]);
				return 0;
	}
}


int* removeFirst(ElementA **   A)
{
	ElementA *removed;
	int *g;

	g=(*A)->array;
	removed=*A;
	if((*A)->next==NULL)
	{
		*A=NULL;
	}
	else
	{
		*A=(*A)->next;
	}

	free(removed);


	return g;


}

