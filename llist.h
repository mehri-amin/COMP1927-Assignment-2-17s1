#ifndef LLIST_H
#define LLIST_H

#include <stdio.h> 
typedef struct Node *Node;
typedef struct ListHead *List;

typedef struct Node {
        char *val;
        struct Node *next, *prev;
} *Node;

typedef struct ListHead {
        int length;
        struct Node *first, *last, *curr;

} *List;

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
// print the list
void showList(List l);
// does the list have element val?
int listHasElement(List l, char *val);

void ListAfter(List, char *);

List listCopy(List l);

#endif


