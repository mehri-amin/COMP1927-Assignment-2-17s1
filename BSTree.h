// BSTree.h ... interface to binary search tree ADT
// taken from lab 10 - https://cgi.cse.unsw.edu.au/~cs1927/17s1/labs/week10/index.php

#ifndef BSTREE_H
#define BSTREE_H

#include "llist.h"
#include <stdio.h>

typedef struct BSTNode *BSTree;

// create an empty BSTree
BSTree newBSTree();
// free memory associated with BSTree
void dropBSTree(BSTree);
// display a BSTree
void showBSTree(BSTree);
// display BSTree root node
void showBSTreeNode(BSTree);

// print values in infix order
void BSTreeInfix(BSTree);
// print values in prefix order
void BSTreePrefix(BSTree);
// print values in postfix order
void BSTreePostfix(BSTree);

// count #nodes in BSTree
int BSTreeNumNodes(BSTree);
// count #leaves in BSTree
int BSTreeNumLeaves(BSTree);

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree, char*, List);
// insert one value into a BSTree
BSTree BSTreeInsertOne(BSTree, char*, char*);
// check whether a value is in a BSTree
List BSTreeFind(BSTree, char*);
// delete a value from a BSTree
BSTree BSTreeDelete(BSTree, char*);

void BSTreeInfixDump(BSTree, FILE *);

#endif
