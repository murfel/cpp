#include <stdlib.h>
#include <stddef.h>

void cpy (void * a, void * b, size_t size) {
    int q;
    for (q = 0; q < size; q++) {
        * ((char *) a + q) = * ((char *) b + q);
    }
}

int mergesort (void* base, size_t num, size_t size, int (*compar)(const char*, const char*)) {
    /* Inplace mergesort.
     * Adapted from stackoverflow.com/a/17957133
     */

    size_t left, right, right_end;
    size_t k, i, j, m, t;

    void * temp = malloc(num * size);

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

            while (i < right && j < right_end) {
                // Merging.
                //if (base[i * size] < base[j * size]) {
                if ((*compar)((char *) base + i * size, (char *) base + j * size) < 0) {
                    //temp[m * size] = base[i * size];

                    cpy((char *) temp + m * size, (char *) base + i * size, size);

                    i++;
                }
                else {
                    //temp[m * size] = base[j * size];

                    cpy((char *) temp + m * size, (char *) base + j * size, size);

                    j++;
                }
            }

            // When one of the arrays is exhausted, add all the rest
            // elements from the other.
            while (i < right) {
                //temp[m * size] = base[i * size];

                cpy((char *) temp + m * size, (char *) base + i * size, size);

                i++;
            }
            while (j < right) {
                //temp[m * size] = base[j * size];

                cpy((char *) temp + m * size, (char *) base + j * size, size);

                j++;
            }

            // Copy merged subarrays back.
            for (m = left; m < right_end; m++) {
                //base[m * size] = temp[m * size];

                //for (q = 0; q < size; q++) {
                //    * ((char *) base + m * size + q) = * ((char *) temp + i * size + q);
                //}

                cpy((char *) base + m * size, (char *) temp + m * size, size);
            }
        }
    }

    return 0;
}


int intcmp (const char* a, const char* b) {
    return *(int *)a - *(int *)b;
}

int chrcmp (const char* a, const char* b) {
    return (int)(*a - *b);
}
