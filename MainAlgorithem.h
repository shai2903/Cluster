/*
 * MainAlgorithem.h
 *
 *  Created on: 19 Sep 2020
 *      Author: Shai
 */

#ifndef MAINALGORITHEM_H_
#define MAINALGORITHEM_H_

#include "LinkedList.h"
#include "spmat.h"
#include "LinkedListCol.h"
#include "ModMatrix.h"


/**
 *MainAlgorithem.h Summary:
 *
 *module for main algoritem in project
 *
 *algorithm3 - return O (final divison)
 *algorithm2 - making division
 *algorithm4 - modularity maximization

 */



/*
 * return the divison of the graph
 * A -  sparse matrix
 * k - vector with degrees of nodes
 * M - sum of all degrees
 * ng - size of k
 * */
ElementA* algorithm3 (spmat *A,int *k, int M, int ng );



/*
 * g - group of node
 * ng - size of g
 * B-mod matrix
 * s - vector for division
 * eigenVector - the eigen vector
 * helper,helper2 - vector for calculation and result
 * first - if first=1 - calculate shift otherwise dont
 * return the eigenVal
 * */
double algorithm2 (ModMatrix *B,int ng, double *s,double *eigenVector,double *helper,double *helper2,int first,double *saved);



/*modularity maximization
 * B -matrix
 * s - division from algo 2
 * unmoved,score,improve,improve - vector for maximization
 * helperRes,helperCalc - helper vector for Q calculation
 *  */
void algorithm4(double *s,ModMatrix *B,int* indices,double *helperRes,double *helperCalc,double *savedQ,double *saved);




#endif /* MAINALGORITHEM_H_ */
