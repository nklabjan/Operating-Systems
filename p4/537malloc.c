/////////////////////////////////////////////////////////////////
//
// FileName: 537malloc.c
//
// Authors: Nick Klabjan, klabjan@cs.wisc.edu
//          Sam Wheeler, swheeler@cs.wisc.edu
//
// Description: Implements versions of malloc(), free(), and realloc()
//
/////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "537malloc.h"
#include "AVL.h"

// static Node variable that will be root of our tree
static Node * root = NULL;

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
void * malloc537(size_t size) {
	// if size is 0, there is no error, but it is worth mentioning
	if (size == 0) {
		printf("Specified memory allocation is of size 0.\n");
	}

	// mallocs space of size, size, which is pointed to by ptr
	void * ptr = malloc(size);
	if (ptr == NULL) {
		printf("Memory allocation failed.\n");
		exit(0);
	}

	// searches tree for the new ptr being malloced
	Node * temp = search(root, ptr);
	// if ptr is already in the tree
	if (temp != NULL){
		temp->freed = 0;
		temp->key->size = size;
		temp->key->addr = ptr;
	}
	// if ptr is not already in the tree
	else{
		// creates a new tuple
		tuple * tp = malloc(sizeof(tuple));
		if (tp == NULL) {
			printf("Memory allocation failed.\n");
			exit(0);
		}

		// sets the data member fields for the tp structure
		tp->addr = ptr;
		tp->size = size;
		
		// if root is null
		if (root == NULL){
			// set root to be this newly created node
			root = createNode(tp);
		}
		// if root is not null
		else{
			// create a new node and insert it into tree
			Node * n = createNode(tp);
			root = insert(root, n);
		}
	}
	// return the ptr
	return ptr;
}

/*
* This function will first check to make sure that freeing the memory specified by ptr makes sense, then will
* call free() to do the actual free. Some of the error conditions that you should check for include:
*              Freeing memory that has not be allocated with malloc537().
*              Freeing memory that is not the first byte of the range of memory that was allocated.
*              Freeing memory that was previously freed (double free).
* When an error is detected, then print out a detailed and informative error message and exit the
* program (with a -1 status). If all checks pass,then this function removes the tuple for addr = ptr and calls free().
*
* params: ptr, pointer to be freed
*/
void free537(void * ptr) {
	// ptr can't be null 
	if (ptr == NULL){
		fprintf(stderr, "Null pointer passed in as argument to free537().");
		exit(-1);
	}
	
	// search the tree for the ptr
	Node * temp = search(root, ptr);
	
	// if temp is null
	if (temp == NULL){
		fprintf(stderr, "Specified memory wanting to be freed was never allocated by malloc537.\n");
		exit(-1);
	}
	
	// if temp->freed == 1
	if (temp->freed == 1){
		fprintf(stderr, "Specified memory to be freed has already been freed.\n");
		exit(-1);
	}
	
	// if ptr addr is same as the addr pointed to by temp
	else if (temp->key->addr != ptr){
		fprintf(stderr, "Specified pointer to be freed does not point at first bit of allocated memory.\n");
		exit(-1);
	}
	
	// else if freed is 0
	else if (temp->freed == 0){
		temp->freed = 1;//Set node as freed
	}
	// free the pointer
	free(ptr);
}

/*
* If ptr is NULL,then this follows the specification of malloc537() above. If size is zero and ptr
* is not NULL,then this follows the specification of free537() above. Otherwise, in addition to
* changing the memory allocation by calling realloc(), this function will first check to see if
* there was a tuple for the (addr = ptr), and removes that tuple, then adds a new one where
* addr is the return value from realloc() and len is size.
*
* params: ptr, the pointer that is being reallocated
*         size, the size to be allocated
*
* return: pointer to an address in the heap
*/
void * realloc537(void * ptr, size_t size) {
	// if ptr is null then just call malloc()
	if (ptr == NULL) {
		void * temp = malloc537(size);
		return temp;
	}
	
	// if ptr isn't null and size is 0, then free()
	else if (ptr != NULL && size == 0) {
		fprintf(stderr, "Reallocation of size 0.\n");
		free537(ptr);
		return NULL;
	}

	else {
		// searches tree for ptr
		Node * n = search(root, ptr);
		void * temp = realloc(ptr, size);
		if (temp == NULL) {
			fprintf(stderr, "Reallocation failed!");
			exit(-1);
		}


		// if n is null 
		if (n == NULL){
			n = malloc(sizeof(Node));
			if (n == NULL) {
                        	fprintf(stderr, "Malloc failed!");
                        	exit(-1);
               		}
			tuple * tp = malloc(sizeof(tuple));
			if (tp == NULL) {
				fprintf(stderr, "Malloc failed!");
                                exit(-1);
			}
			tp->addr = temp;
			tp->size = size;
			n->key = tp;
			root = insert(root, n);
		}
		// if temp is pointing to same address as the ptr stored in n
		else if (temp != n->key->addr){
			n->freed = 1;//Set old node to freed
			n = malloc(sizeof(Node));
			if (n == NULL) {
                                fprintf(stderr, "Malloc failed!");
                                exit(-1);
                        }
			tuple * tp = malloc(sizeof(tuple));
			if (tp == NULL) {
                                fprintf(stderr, "Malloc failed!");
                                exit(-1);
                        }
			tp->addr = temp;
			tp->size = size;
			n->key = tp;
			root = insert(root, n);
		}

		else{
			n->key->addr = temp;
			n->key->size = size;
			n->freed = 0;
		}
		return temp;
	}
}


/*
* This function checks to see the address range specified by address ptr and length size are fully
* within a range allocated by malloc537() and memory not yet freed by free537(). When an error is detected,
* then it prints out a detailed and informative error message and exits the program (with a -1 status).
*
* params: ptr, pointer to be analyzed
*         size, the size to be checked
*/
void memcheck537(void * ptr, size_t size) {
	Node * n = search(root, ptr);

	if (n == NULL){
		fprintf(stderr, "Null pointer passed as argument\n");
		exit(-1);
	}

	else {
		if ((n->key->addr + n->key->size) < (ptr + size)){
			fprintf(stderr, "Specified address range not within range allocated by malloc537\n");
			exit(-1);
		}

		if (n->freed == 1){
			fprintf(stderr, "Specified memory has already been freed\n");
			exit(-1);
		}
	}
}
