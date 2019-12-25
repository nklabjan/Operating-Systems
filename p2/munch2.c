/*******************************************************
 * File Name: munch2.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Converts any lower case letters to upper case.
 */

#include "queue.h"
#include <stdio.h>
#include <strings.h>
#include <ctype.h>

/*
 * Replaces any lowercase character to an uppercase  char.
 *
 * arguments: arg, muti queue structure defined in queue.h
 */
void * toUppercase(void *arg){
	mltQ *q2q3 = arg;
	// sets second and third queue 
	Queue *q2 = q2q3->input;
	Queue *q3 = q2q3->output;

	int END = 0;
	char *c;
	char *s;
	
	// while not the end of the line
	while (!END){
		// grab the first string from the queue2
		s = DequeueString(q2);
		c = s;
		// while c doesn't equal end of string character
		while(*c != '\0') {
			// if c doesn't equal new line character
			if (*c == '\n'){
				// if end signal recieved, end loop and pass on signal
				END = 1;
			}
			// if c is a lowercase char
			else if(islower(*c)) {
				// change c to be an uppercase char
				*c = toupper(*c);
			}
			c++;
		}
		EnqueueString(q3, s);
	}
	pthread_exit(0);
}
