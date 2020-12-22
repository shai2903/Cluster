/*
 * LinkedListCol.h
 *
 *  Created on: 17 Sep 2020
 *      Author: Shai
 */

#ifndef LINKEDLISTINT_H_
#define LINKEDLISTINT_H_
#define LINKEDLIST_H_

/**
 *LinkedListCol.h Summary:
 *
 *module for linked list with data = int
 *
 *mul_single_line - mult linked list with given v
 *delete_list - free list
 *buildBinaryA - build binary vector with the data from linked list
 *initializUnmoved - create linked list with 1...nP as column
 *deleteItem - delete given item from linked list
 */


struct node {
	struct node *next; /*points to next cell*/
	int col;/*column of original cell*/
};


typedef struct node Element;
typedef Element* List;



/* return  multiplication of lst( size of lst = 1xng )  with vector v^T*/
double mul_single_line (List *lst,const double *v,int *o) ;

/* free all nodes */
void delete_list(List lst);

/*bulid vector binaryA
 * binaryA[i]=1 -> if A[line,i]=1
 * binaryA[i]=0 - >otherwise
 * */
void buildBinaryA(List* lst, int* binaryA, int ng, int* g);

/*
 * bulid unmoved
 * bulid linkes list , cell in index i = i ,till nP
 *
 * */
void initializUnmoved(Element **unmoved,int nP);

/*
 * delete toDelete Element in List
 * prev - the Element before toDelete
 * */
void deleteItem(Element **List,Element **prev,Element **toDelete);

/*
 * binaryA[g[i+1]]=0 for every i
 * ng - size of binaryA
 * */
void initializBinaryA(int ng, int* g,int * binaryA);

#endif /* LINKEDLISTINT_H_ */
