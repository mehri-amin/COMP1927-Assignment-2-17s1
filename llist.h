#ifndef LLIST_H
#define LLIST_H

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
// print the list
void showList(List l);
// does the list have element val?
int listHasElement(List l, char *val);
#endif

