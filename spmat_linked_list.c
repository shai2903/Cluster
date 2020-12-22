

/*#include "ModMatrix.h"*/

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "SPBufferset.h"
#include "spmat.h"
#include "Helper.h"
#include "LinkedListInt.h"







void add_row_linked(struct _spmat *A, const int *row, int i,int  size) {
	int j;
	List *head; /* pointer to the first node in this line */
	List tmpNode;
	head=&(((List*)A->private)[i]);

	/* iterate over the row */
	for(j=0; j<size; j++) {


			/* create the node we need to add*/
			tmpNode=(Element*)malloc(sizeof(Element));
			if(tmpNode==NULL)
				{
							 printf("SP_ALLCOATE_PROBLEM");
										exit(EXIT_FAILURE);
				}

			tmpNode->col=row[j];
			/*printf("%d",row[j] );*/
			tmpNode->next=NULL;

			/* if it is not the first node in tmp */
			if((*head)!=NULL) {
				/* add the new node, and advanced p */
				(*head)->next=tmpNode;
				head=&((*head)->next);
			}
			else {
				(*head)=tmpNode;
			}
	}

}


void free_linked_list (struct _spmat *A) {
	int j;
	List head;

	/* free all linked list */
	for(j=0; j<A->n; j++) {
		head=((List*)A->private)[j];
		if(head!=NULL) {
			/* free each link */
			delete_list(head);
			}
		}

	/* free main array */
	free(A->private);
	free(A);
}



double oneMult(const struct _spmat *A,const double *v,int j,int *o) {
	List *head;
		int line;
		double result=0.0;
		line=j;


			/*get relevant line from A*/
			head=&(((List*)A->private)[line]);
			if( head!=NULL && (*head)!=NULL ) {

						result=mul_single_line(head,v,o);
			}
			else {
						result=0;
			}
			return result;

}

void mul_linked_list(const struct _spmat *A,int ng,const double *v, double *result,int *o) {
	int i;
	List *head;
	int line;


	for(i=0;i<ng;i++)
	{
		line=i;

		/*get relevant line from A*/
		head=&(((List*)A->private)[line]);
		if( head!=NULL && (*head)!=NULL ) {

					result[i]=mul_single_line(head,v,o);
		}
		else {
					result[i]=0;
		}

	}

}



void calculateLineB(spmat *A, double *lineKM,int n,int index, int *o)
{
	int i;
	List *head;
	head=&(((List*)A->private)[index]);

	for(i=0; i<n; i++)
	{

		lineKM[i]=(-1)*lineKM[i];

	}
	while( head!=NULL && (*head)!=NULL )
	{
		i=o[(*head)->col];
		lineKM[i]=(-1)*lineKM[i];
		lineKM[i]=1-lineKM[i];
		head = &((*head)->next);
	}

}


spmat* spmat_allocate_list(int n) {
	int i;
	spmat *s; /* the new matrix */

	s=(spmat*)malloc(sizeof(spmat));
	if(s==NULL)
	{
		 printf("SP_ALLCOATE_PROBLEM");
		 exit(EXIT_FAILURE);
	}

	s->n=n;
	s->private =(List*)malloc(n*sizeof(Element));
	if(s->private==NULL)
		{
			 printf("SP_ALLCOATE_PROBLEM");
			 exit(EXIT_FAILURE);
		}


	/* all the lines point to null at the beginning */
	for(i=0; i<n; i++) {
		((List*)s->private)[i]=NULL;
	}
	s->add_row=add_row_linked;
	s->free=free_linked_list;
	s->mult=mul_linked_list;
	return s;
}


int getRowAccordingToG(List *head,int *g,int n,int *binary,int *row)
{

	int i ,count;
	buildBinaryA(head,binary,n,g);
	count=0;
	for(i=0; i<n; i++)
	{
		if(binary[g[i+1]] ==1)
		{
			row[count]=g[i+1];
			count++;
		}


	}
	return count;



}


spmat* BuildAg(spmat *A, int *g,int n,int *binary,int *row)
{

	int i,count;
	List *head;

	spmat * Ag=spmat_allocate_list(n);

	for (i=0;i<n;i++)
	{
		head=&(((List*)A->private)[g[i+1]]);
		count=getRowAccordingToG(head,g,n,binary,row);
		add_row_linked(Ag,row,i,count);
	}

	return Ag;




}



int BulidA (spmat *A,int *k,FILE *Input_mat,int n)
{
	int line,M,nr;

	int *neighbors,*kNode;
	M=0;

	/*the degree of node i*/
	kNode=(int*)malloc(sizeof(int));
	neighbors=(int*)malloc(sizeof(int)*n);/*all the neighbors of vector i */
	if(kNode==NULL ||neighbors==NULL )
			{
				 printf("SP_ALLCOATE_PROBLEM");
				 exit(EXIT_FAILURE);
			}

	for(line=0;line<n;line++)
	{

			/*read the degree of current node*/
			nr=fread(kNode, sizeof(int), 1, Input_mat);
			if(nr!=1)
			{

						printf("SP_COMMUNITY_STRUCTURE_FILE_INPUT_ERROR");
						exit(EXIT_FAILURE);
			}

			/*add to vector k*/
			k[line]=kNode[0];


			/*Calculate M*/
			M+=k[line];

			/*read all the node that have an edge with node i */
			nr=fread(neighbors, sizeof(int), k[line], Input_mat); /*the neighbors of node i*/
			if(nr!=k[line])
			{
				printf("SP_COMMUNITY_STRUCTURE_FILE_INPUT_ERROR");
				exit(EXIT_FAILURE);
			}


			/*put 1 in A for every neighbour in neighbors */
			A->add_row(A, neighbors, line,k[line]);


	}
	free(neighbors);
	free(kNode);
	return M;
}


