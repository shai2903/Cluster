/*
 * cluster.h
 *
 *  Created on: 7 Sep 2020
 *      Author: Shai
 */

#ifndef MAIN_H_
#define MAIN_H_

/*
 * main - summery
 *
 * writeInFile - write the result of division in Output
 *
 * */

#include "spmat.h"

#include "LinkedList.h"

/*
 * writeInFile - write the result of division in Output
 *
 * */

void writeInFile(ElementA * head,FILE *Output);

/*
 * read the input file
 * if it's empty - exit(EXIT_FAILURE)
 * if M =0 - exit(EXIT_FAILURE)
 *
 * */
int main(int argc, char *argv[]);



#endif /* MAIN_H_ */
