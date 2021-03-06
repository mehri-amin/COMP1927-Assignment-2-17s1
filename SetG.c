// SetG.c ... Generic Set ADT implementation
// Written by Ashesh Mahidadia, March 2016

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SetG.h"

typedef struct Node {
	void  *value;
	struct Node *next;
} Node;

typedef struct SetRep {
	Node *elems;

	int size;
	SetElmCopyFp    copyElm;
	SetElmCompareFp cmpElm;
	SetElmFreeFp    freeElm; 
	SetElmValidFp   isValidElm; 
} SetRep;

// Local functions
// check whether Set looks plausible
int isValid(Set s)
{
	if (s == NULL) return 0;

	return 1;
}


// create new empty set
Set SetNew(SetElmValidFp isValid, SetElmCompareFp cmp, SetElmCopyFp copy, SetElmFreeFp free)
{
	Set newS;
	if ((newS = malloc(sizeof(struct SetRep))) == NULL) {
	  printf("Error!!  .... \n"); 
	}
	newS->elems = NULL;
	newS->size = 0;
	newS->isValidElm = isValid;
	newS->cmpElm = cmp;
	newS->copyElm = copy;
	newS->freeElm = free;

	return newS;
}

// set membership test
int SetMember(Set s, void *elem)
{

	assert(isValid(s));
	assert(s->isValidElm(elem)); 

	Node *ptr = s->elems;
	while(ptr != NULL){
		if(s->cmpElm(ptr->value, elem) == 0 ) return 1;
		ptr = ptr->next; 
	}

	return 0;
}

// add value into set
int SetInsert(Set s, void *elem)
{
	assert(isValid(s));
	assert(s->isValidElm(elem)); 

	if(SetMember(s, elem)) { return 0; }

	Node *new;
	if ((new = malloc(sizeof(Node))) == NULL) { return 0; }

	// new->value =  elem;  
	// ... or ... copy elm ...
	new->value = s->copyElm(elem);

	new->next = s->elems;
	s->elems = new;
	s->size++;

	return 1;
}

// remove value from set
int SetDelete(Set s, void *elem)
{
	assert(isValid(s));
	assert(s->isValidElm(elem)); 

	Node *cur, *prev; 
	cur = s->elems;
	prev = NULL;

	while( cur != NULL){
		if(s->cmpElm( cur->value, elem)==0) {

			// avoid memory leaks!
			s->freeElm( cur->value ); 
			s->size--;
			// .. delete node here ... 
			if(cur == s->elems){
				s->elems = cur->next;
				free(cur);
			}
			else {
				prev->next = cur->next;
				free(cur);
			}
			return 1;
		}
		prev = cur;
		cur = cur->next; 
	}
	return 0;
}

// display set using given printFp
void SetTraverse(Set s, void (*Fp)(void const *e1))
{
	assert(isValid(s));
	Node *cur;
	for (cur = s->elems; cur != NULL; cur = cur->next) {
	  Fp(cur->value);
	}
}

void *SetNext(Set s, void **node) {
	if (*node == NULL) {
		*node = s->elems;
	} else {
		*node = ((Node*)*node)->next;
	}
	if (node == NULL || *node == NULL) return NULL;
	return (*((Node**)node))->value;
}

// free memory used by set
void SetDrop(Set s)
{
	// assert(isValid(s));
}

// make a copy of a set
Set SetCopy(Set s)
{
	// assert(isValid(s));
	return NULL;
}


// cardinality (#elements)
int SetSize(Set s)
{
	assert(isValid(s));
	return s->size;
}


//==========================================




