/////////////////////////////////////////////////////////////////
//
// FileName: 537malloc.h
//
// Authors: Nick Klabjan, klabjan@cs.wisc.edu
//          Sam Wheeler, swheeler@cs.wisc.edu
//
// Description:
//
/////////////////////////////////////////////////////////////////

#ifndef MALLOC_H_
#define MALLOC_H_

#include <stdlib.h>

#define BUFF_SIZE 1024

/*
 * A data structure that mimics a tuple. It will store
 * an address, the starting address of allocated memory, and
 * the size of that corresponding allocated memory.
 */
typedef struct tuple { 
	void *addr; // pointer to starting address
	size_t size; // size of allocated memory
} tuple;

/*
 * In addition to actually allocating the memory by calling malloc(), this function will 
 * record a tuple (addri, leni), for the memory that it allocates in the heap. 
 * It will get the starting address, addri, from the return value from malloc() and the length, leni, 
 * from the size parameter. It checks the size parameter for zero length (this is not 
 * actually an error, but unusual enough that it is worth reporting).
 *
 * params: size, the size to be allocated in heap
 *
 * return: pointer to an address in the heap
 */
void* malloc537(size_t size);


/*
 * This function will first check to make sure that freeing the memory specified by ptr makes sense, then will 
 * call free() to do the actual free. Some of the error conditions that you should check for include:
 * 		Freeing memory that has not be allocated with malloc537().
 * 		Freeing memory that is not the first byte of the range of memory that was allocated.
 * 		Freeing memory that was previously freed (double free).
 * When an error is detected, then print out a detailed and informative error message and exit the 
 * program (with a -1 status). If all checks pass,then this function removes the tuple for addr = ptr and calls free().
 *
 * params: ptr, pointer to be freed
 */
void free537(void *ptr);

/*
 * If ptr is NULL,then this follows the specification of malloc537() above. If size is zero and ptr 
 * is not NULL,then this follows the specification of free537() above. Otherwise, in addition to 
 * changing the memory allocation by calling realloc(), this function will first check to see if 
 * there was a tuple for the (addr = ptr, and removes that tuple, then adds a new one where 
 * addr is the return value from realloc() and len is size.
 *
 * params: ptr, the pointer that is being reallocated
 * 	   size, the size to be allocated 
 *
 * return: pointer to an address in the heap
 */
void* realloc537(void *ptr, size_t size);

/*
 * This function checks to see the address range specified by address ptr and length size are fully 
 * within a range allocated by malloc537() and memory not yet freed by free537(). When an error is detected, 
 * then it prints out a detailed and informative error message and exits the program (with a -1 status).
 *
 * params: ptr, pointer to be analyzed
 * 	   size, the size to be checked 
 */
//void memcheck537(void *ptr, size_t size);
void memcheck537(void *ptr, size_t size);
#endif
