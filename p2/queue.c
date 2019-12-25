/*******************************************************
 * File Name: queue.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Implements queue data structure.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*
 * Initializes a queue data structure.
 *
 * arguments: size, the size of the queue
 *
 * return: Queue, a queue data structure
 */
Queue * CreateStringQueue(int size) {
	// mallocs memory for queue data structure
	Queue * q = malloc(sizeof(Queue));
	// if q is null
 	if ( q == NULL){

  	}
 	else { 
		// sets buffer for character pointers
  		q->buff = malloc(sizeof(char*) * size);
  	}
	
	// initializes pthread 
  	if (pthread_cond_init(&(q->full), NULL) != 0){
  		perror("pthread_cond_init() error");
  	}
  	if (pthread_cond_init(&(q->empty), NULL) != 0){
		perror("pthread_cond_init() error");
  	}
	// sets queue statistics to be 0
  	q->enqueueCount = 0;
  	q->dequeueCount = 0;
  	q->enqueueBlockCount = 0;
  	q->dequeueBlockCount = 0;
  	return q;
}

/*
 * Adds a string to the queue.
 *
 * arguments: string, the string to be added the queue
 * 	      q, the queue that which string will be added to
 */
void EnqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&(q->lock));
	// while the queue is full
	while (q->last == QUEUE_SIZE){
  		q->enqueueBlockCount++;
		if (pthread_cond_wait(&(q->full), &(q->lock)) != 0) {
			fprintf(stderr, "Error when waiting on condition variable");
	  	}	
	}	
	// adds string to end of buff	
	q->buff[q->last] = string;
	fprintf(stdout, "Enqueue: %s\n", string);
	q->last = (q->last+1) % QUEUE_SIZE;
	q->enqueueCount++;
	pthread_cond_signal(&(q->empty));
	pthread_mutex_unlock(&(q->lock));
}	

/*
 * Removes a string from the queue.
 *
 * arguments: q, the queue that which a string will be removed from
 * 
 * return: char, the string that is removed from the queue
 */
char * DequeueString(Queue *q) {
	pthread_mutex_lock(&(q->lock));
	// while the queue is empty
	while (q->first == q->last){
    		q->dequeueBlockCount++;
    		if (pthread_cond_wait(&(q->empty), &(q->lock)) != 0) {
    			fprintf(stderr, "Error when waiting on condition variable");
		}
  	}
	// grabs the first char in buff
  	char * ret =  q->buff[q->first];
  	fprintf(stdout, "Dequeue: %s\n", ret);
	q->first = (q->first + 1) % QUEUE_SIZE;
  	q->dequeueCount++;
  	pthread_cond_signal(&(q->full));
	pthread_mutex_unlock(&(q->lock));
	return ret;
}

/*
 * Prints the queue statistics.
 *
 * arguments: q, the queue that which its statistics will be printed
 */
void PrintQueueStats(Queue *q) {
	fprintf(stderr, "Enqueue Count: %d\n", q->enqueueCount);
	fprintf(stderr, "Dequeue Count: %d\n", q->dequeueCount);
	fprintf(stderr, "Enqueue Block Count: %d\n", q->enqueueBlockCount);
	fprintf(stderr, "Dequeue Block Count: %d\n", q->dequeueBlockCount);
}
