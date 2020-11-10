/*
 * LinkedList.h
 *
 *  Created on: 12 Sep 2020
 *      Author: shai
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/**
 *LinkedList.h Summary:
 *
 *module for linked list with data = array
 *
 *freeLinkedList - free linked list
 *addToListA - add linked list to A
 *addToOorP - add linked list to O or P
 *removeFirst - remove first element from linked list , and return it's array
 */




typedef struct NodeA{
	struct NodeA *next; /*points to next cell*/
	int *array;/*number in each cell*/

} ElementA;
typedef ElementA* ListA;


/*
 * free lst
 * */
void freeLinkedList(ElementA * lst);


/*
 * add g as new Node to A
 * */
void addToListA(ElementA ** A, int *g);

/*
 * add division[i] to P or O
 * n - size of original group (before division)
 * */
int addToOorP(ElementA ** P,ElementA ** O,int ** division,int i,int n);

/*
 * remove the first element in A and return it's array
 * */
int* removeFirst(ElementA **   A);

#endif /* LINKEDLIST_H_ */
