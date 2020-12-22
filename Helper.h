/*
 * Helper.h
 */

#ifndef HELPER_H_
#define HELPER_H_

/**
 *Helper.h Summary:
 *
 *Module for general function
 *
 *isPositive(a) - macro ,return if a is positive
 *getSum - return sum of vector
 *getSumAbs - return the Abs sum
 *calculateKM - calculate kikj/M
 *norm - return normalised vector
 *maxDiffer - return the max different between cells of 2 vector
 *dotProduct - return multiplication of 2 vector
 *generateRandom - return new random vector
 *computeS - make division of s
 *countOne - return counter of "1" in vector
 *makeDivision - return division of 2 groups
 *multLineVec - return multiplication of line in B with vector
 *allOneDouble - put 1 in all cells
 *changeLocMax - change max value and location
 *buildFirstG - build the first group
 *buildInverse - build g inverse
 */


extern double epsilon ;

/*return 1 if 'a' is positive ,else return 0*/
#define isPositive(a) ((a)>(epsilon) ? (1) : (0))

/* return sum of vector */
double getSum(double *vector, int n);

/* return sum of absolute values in vector */
double getSumAbs(double *vector, int n);

/*
  *calculate k_currLine*kj\M , save result in saved
  *size : size of  saved*/
void calculateKM(int *k, int M, int *g, int currLine, int size, double *saved);

/* calculating the norm of vector */
void norm(double *v, int n) ;

/* return the max of (v1[i]-v2[i]) for all i={0...n} */
double maxDiffer(double *v1, double *v2, int n) ;

/* calculate (v1^T)*v2 */
double dotProduct(double *v1, double *v2, int n) ;

/* generate new random vector b0 of size n */
void generateRandom(double *b0, int n);

/* compute s according to vec*/
void computeS(double *vec, double *s, int n);

/* count all  '1' in s */
int countOne(double *s, int n);

/*
 * divide to groups according to s
 * s=1 go to group division[1]
 * s=-1 go to group division[0]
 * */
void makeDivision(int*g,double *s, int **division, int n);

/* return multiplication k (according to the index in g) with vector v^T */
double multLineVec(int *k, int *g, const double *v, int n) ;

/*put '1' in all cells (of array)*/
void allOneDouble(double *array,int size);


/* return the index of the highest value in the array
 * if checkNeeded==1 -> return the highest from s only if unmoved[i]==1
 * otherwise return the highest from s
 * */
int max_location(double *s,int size,int *unmoved,int checkNeeded);

/*put data in max and i in  loc */
void changeLocMax (double *max,int *loc ,double data, int i);

/*build g[i]=i till ng*/
void buildFirstG(int *group,int ng);

/*build the inverse of g*/
void buildInverse(int *o,int* g,int ng);

#endif /* HELPER_H_ */
