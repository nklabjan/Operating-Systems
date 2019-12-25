/*******************************************************
 * File Name: reader.h
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Reads line by line from standard input and stores the lines in a queue.
 */

#ifndef READER_H_
#define READER_H_

/*
 * Reads in line by line from standard input and stores the lines in a queue
 *
 * arguments: args, the queue to which lines will be added to
 */
void * read(void * arg);

#endif
