// From COMP1927 Algoirthms Almanac
// Modified for pagerank.c

#include <stdlib.h>
#include "mergesort.h"

void mergesort(void *PageRanks[], int lo, int hi, int size, int(*first)(const void*, const void*))
{
   int mid = (lo+hi)/2; // mid point
   if (hi <= lo) return;
   mergesort(PageRanks, lo, mid, size, first);
   mergesort(PageRanks, mid+1, hi, size, first);
   merge(PageRanks, lo, mid, hi, size, first);
}
void merge(void *PageRanks[], int lo, int mid, int hi, int size, int(*first)(const void*, const void*))
{
   int  i, j, k, nitems = hi-lo+1;
   void *tmp = malloc(nitems*size);

   i = lo; j = mid+1; k = 0;

   // scan both segments, copying to tmp
   while (i <= mid && j <= hi) {
     if (first(PageRanks[i],PageRanks[j]))
        tmp[k++] = PageRanks[i++];
     else
        tmp[k++] = PageRanks[j++];
   }
   // copy items from unfinished segment
   while (i <= mid) tmp[k++] = PageRanks[i++];
   while (j <= hi) tmp[k++] = PageRanks[j++];

   //copy tmp back to main array
   for (i = lo, k = 0; i <= hi; i++, k++)
      PageRanks[i] = tmp[k];
   free(tmp);
}
