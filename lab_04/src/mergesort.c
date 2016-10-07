#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void cpy (void * a, void * b, size_t size) {
    int q;
    char * ap = (char *)a;
    char * bp = (char *)b;
    for (q = 0; q < size; q++) {
        * (ap + q) = * (bp + q);
    }
}

int mergesort (void* base, size_t num, size_t size, int (*compar)(const char*, const char*)) {
    /* Inplace mergesort.
     * Adapted from stackoverflow.com/a/17957133
     */

    size_t left, right, right_end;
    size_t k, i, j, m, t;

    void * temp = malloc(num * size);

    // print first two numbers
    //printf("%d %d\n", * (int *)((char *)base), * (int *)((char *)base + size));


    // test intcmp
    //int qq = 2; int ww = 5;
    //printf("Comparing qq and ww: %d\n", (*compar)( & qq, & ww));


    for (k = 1; k < num; k *= 2) {
        for (left = 0; left + k < num; left += k * 2) {
            right = left + k;
            right_end = right + k;
            if (right_end > num) {
                right_end = num;
            }
            m = left;
            i = left;
            j = right;



            //printf("%d %d; %d %d\n", i, right, j, right_end);
            while ((i < right) && (j < right_end)) {

                //printf("while\n");
                //printf("%d %d\n", * (int *)((char *) base + i * size), * (int *)((char *) base + j * size));

                // Merging.
                //if (base[i * size] < base[j * size]) {

                printf("Comparing %d and %d: ", * (int *)((char *)base + i * size), * (int *)((char *)base + j * size)  );
                printf("%d\n", (*compar)((char *)base + i * size, (char *)base + j * size));



                if ((*compar)((char *)base + i * size, (char *)base + j * size) < 0) {
                    //temp[m * size] = base[i * size];

                    printf("Copying %d to temp\n", * (int *)((char *)base + i * size) );
                    cpy((char *)temp + m * size, (char *)base + i * size, size);

                    i++;
                    m++;
                }
                else {
                    //temp[m * size] = base[j * size];
                    cpy((char *)temp + m * size, (char *)base + j * size, size);

                    j++;
                    m++;
                }
            }

            // When one of the arrays is exhausted, add all the rest
            // elements from the other.
            while (i < right) {
                //temp[m * size] = base[i * size];

                cpy((char *)temp + m * size, (char *)base + i * size, size);

                i++;
                m++;
            }
            while (j < right) {
                //temp[m * size] = base[j * size];

                cpy((char *)temp + m * size, (char *)base + j * size, size);

                j++;
                m++;
            }

            // Copy merged subarrays back.
            for (m = left; m < right_end; m++) {
                //base[m * size] = temp[m * size];

                cpy((char *) base + m * size, (char *) temp + m * size, size);
            }
        }
    }

    free(temp);

    return 0;
}


int intcmp (const char* a, const char* b) {
    return *(int *)a - *(int *)b;
}

int chrcmp (const char* a, const char* b) {
    return (int)(*a - *b);
}
