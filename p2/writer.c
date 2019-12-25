/*******************************************************
 * File Name: writer.c
 *
 * Authors: Nick Klabjan, klabjan@cs.wisc.edu
 *          Sam Wheeler, swheeler4@wisc.edu
 *
 * Description: Traverses queue and print queue elements to standard output.
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/*
 * Reads from a queue and writes it to standard output.
 *
 * arguments: args, the queue from which lines will be read from
 */
void * write(void * arg){
  Queue * q3 = arg;
  int END = 0;
  char * tempStr;

  while (!END){
  tempStr = DequeueString(q3);
    if (tempStr != NULL){ 
  if (*tempStr == '\n'){
    END = 1;
  }
  else {
  fprintf(stderr, "%s\n", tempStr);//Throwing seg fault
}
  }
  }
pthread_exit(0);
}
