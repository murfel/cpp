#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mergesort.h"

int main(int argc, char *argv[])
{
    int i;
    size_t size;
    char * endptr = NULL;
    size_t num = argc - 2;
    void * base;
    int elem;

    if (strcmp(argv[1], "int") == 0) {
        size = sizeof(int);
        base = malloc(num * size);

        for (i = 0; i < num; i++) {
            elem = atoi(argv[i + 2]);
            cpy(((char *)base + i * size), &elem, size);
        }

        mergesort(base, num, size, intcmp);

        for (i = 0; i < num; i++) {
            printf("%i ", * ((int *)base + i));
        }
        free(base);
    }
    else if (strcmp(argv[1], "char") == 0) {
        size = sizeof(char);
        base = malloc(num * size);
        for (i = 0; i < num; i++) {
            * ((char *)base + i * size) = * argv[i + 2];
        }

        mergesort(base, num, size, chrcmp);

        for (i = 0; i < num; i++) {
            printf("%c ", * ((char *)base + i * size));
        }
        printf("\n");
        free(base);

        // Alternatively
        //mergesort(argv + 2, num, sizeof(char *), (compar_t)chrcmp2);
        //for (i = 0; i < num; i++) {
        //    printf("%c ", * argv[i + 2]);
        //}
    }
    else if (strcmp(argv[1], "str") == 0) {

        mergesort(argv + 2, num, sizeof(char *), (compar_t)strcmp2);

        for (i = 0; i < num; i++) {
            printf("%s ", *(argv + 2 + i));
        }
    }
    else {
        printf("Unknown type argument: %s\nUsage: ./ms_cli type elems*", argv[1]);
    }
    printf("\n");

    return 0;
}
