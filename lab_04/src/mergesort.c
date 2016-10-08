#include "../include/mergesort.h"
#include <stdlib.h>
#include <stdio.h>


void cpy (void * a, void * b, size_t size) {
    int q;
    char * ap = (char *)a;
    char * bp = (char *)b;
    for (q = 0; q < size; q++) {
        * (ap + q) = * (bp + q);
    }
}


int intcmp (const void* a, const void* b) {
    return *(int *)(char **)a - *(int *)(char **)b;
}


int chrcmp (const void* a, const void* b) {
    return (int)(*(char **)a - *(char **)b);
}


int chrcmp2 (const void** a, const void** b) {
    return (int)(**(char **)a - **(char **)b);
}

int strcmp2 (const void** a, const void** b) {
    return strcmp(*(char **)a, *(char **)b);
}


int mergesort (void* base, size_t num, size_t size, compar_t compar) {
    /* Inplace mergesort.
     * Adapted from stackoverflow.com/a/17957133
     */

    int right, right_end;
    int i, j, m;
    int k, left;

    void * temp = malloc(num * size);

    for (k = 1; k < num; k *= 2 ) {
        for (left = 0; left + k < num; left += k*2 ) {
            right = left + k;
            right_end = right + k;
            if (right_end > num)
                right_end = num;
            m = left;
            i = left;
            j = right;

            while (i < right && j < right_end) {
                if ((*compar)((char *)base + i * size, (char *)base + j * size) < 0) {
                    cpy((char *)temp + m * size, (char *)base + i * size, size);
                    i++;
                }
                else {
                    cpy((char *)temp + m * size, (char *)base + j * size, size);
                    j++;
                }
                m++;
            }
            // When one of the arrays is exhausted, add all the rest
            // elements from the other.
            while (i < right) {
                cpy((char *)temp + m * size, (char *)base + i * size, size);
                i++;
                m++;
            }
            while (j < right_end) {
                cpy((char *)temp + m * size, (char *)base + j * size, size);
                j++;
                m++;
            }
            // Copy merged subarrays back.
            for (m = left; m < right_end; m++) {
                 cpy((char *)base + m * size, (char *)temp + m * size, size);
            }
        }
    }

    free(temp);

    return 0;
}
