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

#ifndef RANGETREE_H
#define RANGETREE_H

#include "537malloc.h"

/*
 * Structure that will represent a node in the AVL tree.
 */
typedef struct Node {
    tuple *key; // key for each node is the tuple
    struct Node *left; // left child
    struct Node *right; // right child
    int height; // height of the tree with node being root
    int freed; // 0 if not freed, 1 if freed
} Node;

/*
 * Calculates which integer is the maximum between the two.
 *
 * @params a, one integer to be compared
 * 	   b, second integer to be compared
 *
 * @return the max integer between the two
 */
int max(int a, int b);

/*
 * Grabs the height of a node.
 *
 * @params n, the node to be evaluated
 *
 * @return the height of the node n
 */
int getHeight(Node *n);

/*
 * Creates a new node given a tuple.
 *
 * @param key, a tuple to be used to create the new node
 *
 * @return the new node created.
 */
Node *createNode(tuple *key);

/*
 * Rotates subtree to the right for rebalancing purposes.
 *
 * @param n, the node to be rotated
 *
 * @return the node that was rotated
 */
Node *rightRotate(Node *n);

/*
 * Rotates subtree to the left for rebalancing purposes.
 *
 * @param n, the node to be rotated
 *
 * @return the node that was rotated
 */
Node *leftRotate(Node *n);

/*
 * Grabs the blanace for the node.
 *
 * @param n, the node to calculate its balance
 *
 * @return the blanace value for that node
 */
int getBalance(Node *n);

/*
 * Inserts node into tree.
 *
 * @param n, the node to be inserted
 * 	  key, the tuple to be inserted
 *
 * @return the node that is inserted
 */
Node *insert(Node *root, Node *n);

/*
 * Searches tree for a given node.
 *
 * @return NULL, if not found
 *         n, if found
 *
 * @return the node to be found in the tree
 */
Node *search(Node *n, void* ptr);

/*
 * Compares two tuples and their adress data fields.
 *
 * @params t1, one tuple to be compared
 * 	   t2, the second tuple to be compared to the first one
 *
 * @return 0, if tuples are equal
 *         1, if t1 is greater than t2
 *         -1, if t1 is less than t2
 */
int compareKey(tuple *t1, tuple *t2);

void preOrder(struct Node *root);
#endif
