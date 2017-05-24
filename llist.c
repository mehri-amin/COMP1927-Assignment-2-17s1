#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llist.h"
#include <string.h>
#include <assert.h>



Node newNode(char *val) {

	struct Node *n = malloc(sizeof(struct Node));
	n->val = strdup(val);
	n->next = NULL;
	return n;
}

char *nodeValue(Node n) {
	return n->val;
}

List newList() {
	List l = calloc(1, sizeof(struct ListHead));
	l->head = NULL;
	return l;
}

void destroyList(List l) {
	Node cur = l->head;
	while (cur != NULL) {
		Node tmp = cur;
		free(cur->val);
		cur = cur->next;
		free(tmp);
	}
	free(l);
}

Node next(List l, Node n) {
	if (n == NULL)
		return l->head;
	return n->next;
}

void listPrepend(List l, Node n) {
	n->next = l->head;
	l->head = n;
	l->length++;
}

int listLength(List l) {
	return l->length;
}

void showList(List l) {
	Node n = NULL;
	printf("list(length=%d)", l->length);
	while ((n = next(l, n)) != NULL) {
		printf(", %s", n->val);
	}
	printf("\n");
}

int listHasElement(List l, char *val) {
	Node n = NULL;
	while ((n = next(l, n)) != NULL) {
		if (strcmp(val, n->val) == 0) {
			return 1;
		}
	}
	return 0;
}

List listCopy(List l){
	List copy = newList();
	Node temp = newNode(l->first->val);
	temp = l->first;

	while(temp->next != NULL){
	ListAfter(copy, temp->val);
	temp = temp->next;
	}
	ListAfter(copy, temp->val);
	return copy;
}

void ListAfter(List l, char *val)
{
	Node new = newNode(val);
	if(l->first == NULL){
	l->first = l->last = l->curr = new;
	l->length++;
	return;
	}

	assert(l!=NULL);
	new->prev = l->curr;
	if(l->curr->next != NULL){
		new->next = l->curr->next;
		l->curr->next->prev = new;
	}else{
		new->next = NULL;
		l->last = new;
	}
	l->curr->next = new;
	l->curr = new;
	l->length++;
}
