// SetG.h ... interface to generic Set ADT
// Written by Ashesh Mahidadia, March 2016

#ifndef SETG_H
#define SETG_H

#include <stdio.h>

typedef struct SetRep *Set;

typedef void *(*SetElmCopyFp)(void const *e1);
typedef int   (*SetElmCompareFp)(void const *e1, void const *e2);
typedef void  (*SetElmFreeFp)(void *e1); 
typedef int   (*SetElmValidFp)(void const *e1);


Set SetNew( SetElmValidFp         isValid, 
	    SetElmCompareFp       cmp, 
            SetElmCopyFp          copy, 
            SetElmFreeFp          free    );

// free memory used by set
void SetDrop(Set);

// make a copy of a set
Set SetCopy(Set);

// add value into set
int SetInsert(Set, void *);

// remove value from set
int SetDelete(Set, void *);

// set membership test
int SetMember(Set, void *);

// return size of the set (#elements)
int SetSize(Set);

// iterate through the set
void *SetNext(Set s, void **node);
// display set with given function
void SetTraverse(Set, void (*Fp)(void const *e1) );

#endif
