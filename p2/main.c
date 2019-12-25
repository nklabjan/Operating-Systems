/*******************************************************
 * File Name: main.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Creates queues that are passed into four threads.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"

/*
 * Creates queues that are then passed into four threads
 * that will run in parallel.
 *
 * return: 0, program exists
 */
int main() {
	// creates three queues
	Queue *q1 = CreateStringQueue(QUEUE_SIZE);
	Queue *q2 = CreateStringQueue(QUEUE_SIZE);
	Queue *q3 = CreateStringQueue(QUEUE_SIZE);

	// creates two mutliqueue structures
	mltQ *q1q2 = malloc(sizeof(mltQ));
	if (q1q2 == NULL) {
		fprintf(stderr, "Failed to allocate memory!");
	} else {
		q1q2->input = q1;
		q1q2->output = q2;
	}

	mltQ *q2q3 = malloc(sizeof(mltQ));
	if (q2q3 == NULL) {
                fprintf(stderr, "Failed to allocate memory!");
        } else {
		q2q3->input = q2;
		q2q3->output = q3;
	}

	pthread_t reader, munch1, munch2, writer;

	pthread_cond_init(&(q1->full), NULL);
	pthread_cond_init(&(q2->full), NULL);
	pthread_cond_init(&(q3->full), NULL);

	for (int i = 0; i < 10; i++) {
		pthread_cond_signal(&(q1->full));
		pthread_cond_signal(&(q2->full));
		pthread_cond_signal(&(q3->full));
	}

	pthread_cond_init(&(q1->empty), NULL);
        pthread_cond_init(&(q2->empty), NULL);
        pthread_cond_init(&(q3->empty), NULL);

	// creates four threads
	pthread_create(&reader, NULL, &read, q1);
	pthread_create(&munch1, NULL, &replaceSpace, q1q2);
	//pthread_create(&munch2, NULL, &toUppercase, q2q3);
	//pthread_create(&writer, NULL, &write, q3);

	//joins the four threads
	pthread_join(reader, NULL);
	pthread_join(munch1, NULL);
	//pthread_join(munch2, NULL);
	//pthread_join(writer, NULL);
	
	// prints out Queue statistics
	fprintf(stderr, "Queue 1 stats: \n");
        PrintQueueStats(q1);
	fprintf(stderr, "Queue 3 stats: \n");
        PrintQueueStats(q2);
	fprintf(stderr, "Queue 2 stats: \n");
        PrintQueueStats(q3);

	return 0;
}
