/*
 * Helper.h
 */

#ifndef HELPER_H_
#define HELPER_H_

/**
 *Helper.h Summary:
 *
 *module for general function
 *
 *isPositive(a) - macro ,return if a is positive
 *getSum - return sum of vector
 *getSumAbs - return the Abs sum
 *calculateKM - calculate kikj/M
 *norm - return normalised vector
 *max_differ - return the max different between cells of 2 vector
 *dot_product - mult 2 vector
 *generateRandom - return new random vector
 *computeS - make division of s
 *countOne - return the number of  all "1" in vector
 *makeDivision - return division of 2 groups
 *multLineVec - mult line in B with vector
 *allOneDouble - put 1 in all cells
 *changeLocMax - change max value and location
 *buildFirstG - build the first group
 *buildInverse - build g inverse
 */


extern double epsilon ;

/*return 1 if a is potive else return 0*/
#define isPositive(a) ((a)>(epsilon) ? (1) : (0))

/*type used for returning error messages*/
typedef enum _sp_community_structure_messages {
	SP_COMMUNITY_STRUCTURE_FILE_INPUT_ERROR,
	SP_COMMUNITY_STRUCTURE_FILE_OUTPUT_ERROR,
	SP_DIVISION_BY_ZERO,
	SP_ALLCOATE_PROBLEM,
	INFINTE_LOOP
}SP_COMMUNITY_STRUCTURE_MESSAGES;

/* get sum of vector */
double getSum(double *vector, int n);

/* get sum of absolute values in vector */
double getSumAbs(double *vector, int n);

/*
  *calculate ki*kj\M for i=currLine , saved in saved
  *size- size of  saved*/
void calculateKM(int *k, int M, int *g, int currLine, int size, double *saved);

/* calculating the norm of vector */
void norm(double *v, int n) ;

/* return the max of (v1[i]-v2[i]) for all i={0...n} */
double max_differ(double *v1, double *v2, int n) ;

/* calculate (v1^T)*v2 */
double dot_product(double *v1, double *v2, int n) ;

/* generate new random vector bo of size n */
void generateRandom(double *b0, int n);

/* compute s according to vec , n-size s and vec */
void computeS(double *vec, double *s, int n);

/* count all the '1' in s */
int countOne(double *s, int n);

/*
 * divide to groups according to s
 * s=1 go to group division[1]
 * s=-1 go to group division[0]
 * */
void makeDivision(int*g,double *s, int **division, int n);

/* mult k (according to the index in g) with vector v^T */
double multLineVec(int *k, int *g, const double *v, int n) ;

/*put 1 in all of array*/
void allOneDouble(double *array,int size);


/* return the index of the highest value in the array
 * if checkNeeded==1 -> return the highest from s only if unmoved[i]==1 unmoved
 * otherwise return the highest from s
 * */
int max_location(double *s,int size,int *unmoved,int checkNeeded);

/*put new val in max and loc */
void changeLocMax (double *max,int *loc ,double data, int i);

/*bulid g[i]=i till ng*/
void buildFirstG(int *group,int ng);

/*build the inverse of g*/
void buildInverse(int *o,int* g,int ng);
#endif /* HELPER_H_ */
