// From COMP1927 Algoirthms Almanac
// Modified for pagerank.c

#include <stdlib.h>
#include "mergesort.h"

void mergeSort(void *array[], int lo, int hi, int size, int(*first)(void*, void*))
{
   int mid = (lo+hi)/2; // mid point
   if (hi <= lo) return;
   mergesort(array, lo, mid, size, first);
   mergesort(array, mid+1, hi, size, first);
   merge(array, lo, mid, hi, size, first);
}
void merge(void *array[], int lo, int mid, int hi, int size, int(*first)(void*, void*))
{
   int  i, j, k, nitems = hi-lo+1;
   void *tmp = malloc(nitems*size);

   i = lo; j = mid+1; k = 0;

   // scan both segments, copying to tmp
   while (i <= mid && j <= hi) {
     if (first(array[i],array[j]))
        tmp[k++] = arrayi++];
     else
        tmp[k++] = array[j++];
   }
   // copy items from unfinished segment
   while (i <= mid) tmp[k++] = array[i++];
   while (j <= hi) tmp[k++] = array[j++];

   //copy tmp back to main array
   for (i = lo, k = 0; i <= hi; i++, k++)
      array[i] = tmp[k];
   free(tmp);
}
