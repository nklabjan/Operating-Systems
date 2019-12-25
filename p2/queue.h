/*******************************************************
 * File Name: queue.h
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Implements queue data structure.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <pthread.h>

#define BUFF_SIZE 1024
#define QUEUE_SIZE 10
#define END_STR "\n"

// queue structure
typedef struct Queue{
  	unsigned int first;
 	unsigned int last;
 	pthread_cond_t full;
  	pthread_cond_t empty;
  	pthread_mutex_t lock;
       int enqueueCount;
       int dequeueCount;
       int enqueueBlockCount;
       int dequeueBlockCount;
  	char ** buff;
} Queue;

// multi queue data structure
typedef struct mltQ{
Queue* input;
Queue* output;
}mltQ;

/*
 * Initializes a queue data structure.
 *
 * arguments: size, the size of the queue
 *
 * return: Queue, a queue data structure
 */
Queue * CreateStringQueue(int size);

/*
 * Adds a string to the queue.
 *
 * arguments: string, the string to be added the queue
 *            q, the queue that which string will be added to
 */
void EnqueueString(Queue *q, char *string);

/*
 * Removes a string from the queue.
 *
 * arguments: q, the queue that which a string will be removed from
 *
 * return: char, the string that is removed from the queue
 */
char * DequeueString(Queue *q);

/*
 * Prints the queue statistics.
 *
 * arguments: q, the queue that which its statistics will be printed
 */
void PrintQueueStats(Queue *q);

#endif
