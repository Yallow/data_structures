#ifndef _heap_sort_h
#define _heap_sort_h

#include <stdlib.h>

#define ValType double
#define IS_LESS(v1, v2) (v1 < v2)

void siftDown(ValType *a, int start, int end);
void heapsort(ValType *a, int count);

// do a swap between two values
#define SWAP(r, s) do{ValType t=r; r=s; s=t;} while(0)

#endif
