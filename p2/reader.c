/*******************************************************
 * File Name: reader.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Reads line by line from standard input and stores the lines in a queue.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

/*
 * Reads in line by line from standard input and stores the lines in a queue
 *
 * arguments: args, the queue to which lines will be added to
 */
void * read(void * arg) {
	Queue * q1 = arg;
	// pointer to string that iterates through line
	char * lineBuff;
	// points to start of line
	char * line;
	int c;
	int str_len = 0;

	// mallocs memory for linebuff
	lineBuff = malloc(sizeof(char) * BUFF_SIZE);
	// if linebuff is null
	if (lineBuff == NULL){
		fprintf(stderr, "Malloc failed in Reader!");
		EnqueueString(q1, END_STR);
		pthread_exit(0);
	} else {
		line = lineBuff;
	}

	// while end of file isn't reached and str_len is less than buffer size
	while ((c = fgetc(stdin)) != EOF && str_len < BUFF_SIZE) {//Get chars till end of file or full buffer
		if (c != '\n'){
			*lineBuff = c;
		}
		else {*lineBuff = '\0';}
		lineBuff++;
		str_len++;
		if (str_len == BUFF_SIZE && c != '\n'){//If line too big
			while ((c = fgetc(stdin)) != '\n' && c != EOF) {
				//Flush string buffer
			}
			fprintf(stderr, "String exceded buffer size\n");
			str_len = 0;
		}
		if ((c == '\n') || (c == EOF)){//if at end of file
			if (line != NULL){
				EnqueueString(q1, line);
				lineBuff = malloc(sizeof(char) * BUFF_SIZE);
				if (lineBuff == NULL){
					fprintf(stderr, "Malloc fail: Reader");
					pthread_exit(0);
				}
				line = lineBuff;			
			}
			str_len = 0;
		}
	}
	pthread_exit(0);
}
