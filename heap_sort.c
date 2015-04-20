#include <stdio.h>
#include <stdlib.h>
#include "heap_sort.h"

// takes a pointer to an array and the size of the array
void heapsort(ValType *a, int count)
{
    // create a couple integer vars
    int start, end;

    /* heapify */
    for(start = (count-2)/2; start >= 0; start--) {
        siftDown(a, start, count);
    }

    /* do the actual sorting */
    for(end = count-1; end > 0; end--) {
        // swap the first and last to move the biggest number off of the top
        SWAP(a[end], a[0]);
        siftDown(a, 0, end);
    }
}

void siftDown(ValType *a, int start, int end)
{
    int root = start;
    while(root*2+1 < end) {
        int child = 2*root+1;
        // checks to make sure the left child is bigger than the right. Otherwise use the right child
        if((child + 1 < end) && IS_LESS(a[child], a[child+1])) {
            child += 1;
        }
        // if the child is greater than the root, swap places
        if(IS_LESS(a[root], a[child])) {
            SWAP(a[child], a[root]);
            // move down one level
            root = child;
        }
        else
            return;
    }
}

int main()
{
    int ix;
    // create an array of doubles
    double valsToSort[] = {
        1.4, 50.2, 5.11, -1.55, 301.521, 0.3301, 40.17,
        -18.0, 88.1, 30.44, -37.2, 3012.0, 49.2
    };
    // the size of the array
#define VSIZE (sizeof(valsToSort)/sizeof(valsToSort[0]))

    // sort the array
    heapsort(valsToSort, VSIZE);
    printf("{");
    // move through the array and print off everything
    for(ix=0; ix<VSIZE; ix++) printf(" %.3f ", valsToSort[ix]);
    printf("}\n");
    return 0;
}
