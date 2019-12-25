/*******************************************************
 * File Name: munch1.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Converts any space character to '*' char.
 */

#include "queue.h"
#include <stdio.h>
#include <strings.h>

/*
 * Replaces any space characters to '*' char.
 *
 * arguments: arg, muti queue structure defined in queue.h
 */
void * replaceSpace(void *arg){
	mltQ *q1q2 = arg;
	// points to first and second queue in array
	Queue *q1 = q1q2->input;
	Queue *q2 = q1q2->output;

	int END = 0;
	char *c;
	char *s;

	// while it is not the end of the line
	while (!END){
		// dequeue first character from queue
	s = DequeueString(q1);
		// if it is new line character
	if (*s == '\n'){
			// set end to one
	END = 1;
			// enqueue the character 
	EnqueueString(q2, END_STR);
		// if same line
	} else {
			// grabs index of first space character
	c = index(s, ' ');//Get index of first space
			// while c isn't end of string and not end of line
	while(c && *c != '\0' && !END) {
				// check if c reaches new line character
		if (*c == '\n'){
			//If End signal recieved, end loop and pass on signal
			END = 1;
		}
				// else if c is a spcae character	
		else if(*c == ' ') {
					// replace it with a * char
					*c = '*';
				}
				c++;
			}	
			EnqueueString(q2,s);
		}
	}		
	pthread_exit(0);
}
