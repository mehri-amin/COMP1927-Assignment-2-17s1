#ifndef LLIST_H
#define LLIST_H

#include <stdio.h>
typedef struct Node *Node;
typedef struct ListHead *List;


Node newNode(char *val);
char *nodeValue(Node n);

// make an new list
List newList();
// free the list and all memory it's using
void destroyList(List l);
// if n is NULL, return the first element in the list
// else return the element after n (NULL if there is none)
Node next(List l, Node n);
// add n at the start of the list
void listPrepend(List l, Node n);
// return the length of the list
int listLength(List l);
// delete last element in the list
void listDelete(List l);
// print the list
void showList(List l);
// does the list have element val?
int listHasElement(List l, char *val);
// returns the index of val in the list, -1 if not found
int listIndex(List l, char *val);
// append to the end of the list
void ListAppend(List l, char *val);
void ListAfter(List, char *);

List listCopy(List l);

#endif


