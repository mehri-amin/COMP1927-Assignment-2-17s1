// stringSet.c ... 
// string Set implementation 
// Written by Ashesh Mahidadia, March 2016


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SetG.h"
#include "stringSet.h" 

/* =====   string Set ===== */

int stringValid(void const *vp){
  // if required/possible, check for valid string
  return 1;
}

void stringFree(void *vp){
  free(vp);
}

void *stringCopy(void const *vp){
  return strdup(vp);
}

int stringCompare(void const *vp1, void const *vp2){
  return strcmp(vp1, vp2);
}

Set newStringSet(void) {
	return SetNew(stringValid, stringCompare, stringCopy, stringFree);
}


/* =======  Additional methods ====== */ 

void stringPrintNode(void const *vp){
  char *st = (char *) vp;
  printf("%s, ", st);
}


