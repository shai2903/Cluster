/*
 * main.c
 *
 */

#include "main.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MainAlgorithem.h"

#include <assert.h>
#include "SPBufferset.h"
#include "Helper.h"




/*
 * writeInFile - write the result of division in Output
 *
 * */

void writeInFile(ElementA * head,FILE *Output)
{
	int *pointer;
	int isFirstLoop,counter,nr;
	isFirstLoop=1;
	while(head!=NULL)
	{
		if(isFirstLoop==0)
		{
			/*printf("group");
			printf(" ");*/

			pointer=(*head).array;
			counter=pointer[0];
			nr = fwrite(pointer, sizeof(int), counter+1, Output);
			if(nr!=counter+1)
			{

					printf("SP_COMMUNITY_STRUCTURE_FILE_OUTPUT_ERROR");
					exit(EXIT_FAILURE);


			}
			/*for(l=1;l<counter+1;l++){

					printf("%d",pointer[l]);
					printf(" ");


				}*/
		}
		head=(ElementA*)((*head).next);
		isFirstLoop=0;
		/*printf("\n");*/
	}


}
int main(int argc, char *argv[]) {


	FILE *Input_mat, *Output;
	int *n,*k;
	int M,nr;

	/*int l;*/
	spmat *A;

	ElementA * final_division, *head;


	SP_BUFF_SET();
	if(argc <= 2)
	{
		 printf("no input file or output file");
		exit(EXIT_FAILURE);
	}


	/* open the input file-a symmetric matrix*/
	Input_mat = fopen(argv[1], "rb");
	if(Input_mat==NULL)
	{
		 printf("SP_COMMUNITY_STRUCTURE_FILE_INPUT_ERROR");
			exit(EXIT_FAILURE);
		}

	/* number of nodes in the network */
	n = (int*) malloc(sizeof(int));
	if(n==NULL)
	{
				 printf("SP_ALLCOATE_PROBLEM");
							exit(EXIT_FAILURE);
	}
	nr = fread(n, sizeof(int), 1, Input_mat);
	if(nr!=1)
	{
		 printf("SP_COMMUNITY_STRUCTURE_FILE_INPUT_ERROR");
			exit(EXIT_FAILURE);
	}


	/*create vector k*/
	k=(int*)malloc(sizeof(int)*n[0]);
	if(k==NULL)
	{
				 printf("SP_ALLCOATE_PROBLEM");
							exit(EXIT_FAILURE);
	}
	A = spmat_allocate_list(n[0]);

	/* power iteration on b_hat shifted */
	srand(time(NULL)); /* initialization, should be called only once */

	/*build A*/
	M=BulidA(A,k,Input_mat,n[0]);
	if(M==0)
	{
		 printf("SP_DIVISION_BY_ZERO");
		exit(EXIT_FAILURE);
	}

	final_division=algorithm3 (A,k,M,n[0] );
	Output = fopen(argv[2], "wb"); /* open the output file*/
	if(Output==NULL)
	{
		printf("SP_COMMUNITY_STRUCTURE_FILE_OUTPUT_ERROR");
				exit(EXIT_FAILURE);
	}
	head=final_division;
	nr = fwrite((final_division)->array, sizeof(int), 1, Output);
	if(nr!=1)
	{
			printf("SP_COMMUNITY_STRUCTURE_FILE_OUTPUT_ERROR");
				exit(EXIT_FAILURE);
	}

	writeInFile(head,Output);

	freeLinkedList(final_division);
	free(n);
	free(k);
	fclose(Input_mat);
	fclose(Output);
	A->free(A);


	return 0;


}











