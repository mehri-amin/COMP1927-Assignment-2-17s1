// stringSet.h ... 
// String Set interface/API
// Written by Ashesh Mahidadia, March 2016

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SetG.h"


/* =====   string Set header/API ===== */

int stringValid(void const *vp);
void stringFree(void *vp);
void *stringCopy(void const *vp);
int stringCompare(void const *vp1, void const *vp2);

Set newStringSet(void);

void stringPrintNode(void const *vp);


/* =====   End string Set header/API ===== */
