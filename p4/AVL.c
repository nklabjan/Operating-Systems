#include "AVL.h"
#include <stdio.h>
#include <stdint.h>

/*
* Calculates which integer is the maximum between the two.
*
* @params a, one integer to be compared
*         b, second integer to be compared
*
* @return the max integer between the two
*/
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

/*
* Grabs the height of a node.
*
* @params n, the node to be evaluated
*
* @return the height of the node n
*/
int getHeight(Node * n) {
	if (n == NULL) {
		return 0;
	}
	return n->height;
}

/*
* Creates a new node given a tuple.
*
* @param key, a tuple to be used to create the new node
*
* @return the new node created.
*/
Node * createNode(tuple * key) {
	Node * n = malloc(sizeof(Node));
	if (n == NULL) {
		fprintf(stderr, "Invalid Mem Alloc");
		exit(-1);
	}
	n->key = key;
	n->left   = NULL;
	n->right  = NULL;
	n->height = 1;
	n->freed = 0;
	return n;
}

/*
* Rotates subtree to the right for rebalancing purposes.
*
* @param n, the node to be rotated
*
* @return the node that was rotated
*/
Node * rightRotate(Node * n) {
	Node * x = n->left;
	Node * T2 = x->right;

	x->right = n;
	n->left = T2;

	n->height = max(getHeight(n->left), getHeight(n->right))+1;
	x->height = max(getHeight(x->left), getHeight(x->right))+1;

	return x;
}

/*
* Rotates subtree to the left for rebalancing purposes.
*
* @param n, the node to be rotated
*
* @return the node that was rotated
*/
Node * leftRotate(Node * n) {
	Node * y = n->right;
	Node * T2 = y->left;

	y->left = n;
	n->right = T2;

	n->height = max(getHeight(n->left), getHeight(n->right))+1;
	y->height = max(getHeight(y->left), getHeight(y->right))+1;

	return y;
}

/*
* Grabs the blanace for the node.
*
* @param n, the node to calculate its balance
*
* @return the blanace value for that node
*/
int getBalance(Node * n) {
	if (n == NULL) {
		fprintf(stderr, "Null pointer was passed in to get the balance!");
		exit(-1);
	}
	return getHeight(n->left) - getHeight(n->right);
}

/*
* Inserts node into tree.
*
* @param n, the node to be inserted
*        key, the tuple to be inserted
*
* @return the node that is inserted
*/
Node * insert(Node * root, Node * n) {
	if (root == NULL){
		return n;
	}

	tuple * key = n->key;

	if (compareKey(key, root->key) == -1){//Node addr is greater than current root
		root->left  = insert(root->left, n);//Traverse to left node
	}

	else if (compareKey(key, root->key) == 1){//Node addr is less than current root
		root->right = insert(root->right, n);//Traverse to left node
	}

	else{
		return root;
	}

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	int balance = getBalance(root);

	if (balance > 1 && compareKey(key, root->left->key) == -1){
		return rightRotate(root);
	}

	if (balance > 1 && compareKey(key, root->left->key) == 1) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && compareKey(key, root->right->key) == 1){
		return leftRotate(root);
	}

	if (balance < -1 && compareKey(key, root->right->key) == -1) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

/*
* Searches tree for a given node.
*
* @return NULL, if not found
* 	   n, if found
*
* @return the node to be found in the tree
*/
Node * search(Node * n, void * ptr) {
	if (n == NULL){
		return NULL;
	}

	if (ptr == n->key->addr){
		return n;
	}

	if (n->key->addr > ptr){
		if (n->left != NULL){
			if (((n->left->key->addr + n->left->key->size) > ptr) && (n->left->key->addr < ptr)){
				return n->left;
			}
		}
		return search(n->left, ptr);
	}

	else if (n->key->addr < ptr){
		if ((n->key->addr + n->key->size) > ptr){
			return n;
		}
		return search(n->right, ptr);
	}

	else{
		return n;
	}
}


/*
* Compares two tuples and their adress data fields.
*
* @params t1, one tuple to be compared
*         t2, the second tuple to be compared to the first one
*
* @return 0, if tuples are equal
*         1, if t1 is greater than t2
*         -1, if t1 is less than t2
*/
int compareKey(tuple * t1, tuple * t2) {
	if ((void *)(t1->addr) == (void *)(t2->addr)) {
		return 0;
	}

	else if ((void *)(t1->addr) > (void *)(t2->addr)) {
		return 1;
	}

	else {
		return -1;
	}
}
