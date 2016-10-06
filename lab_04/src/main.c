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

    if (strcmp(argv[1], "int") == 0) {
        size = sizeof(int);
        base = malloc(num * size);

        for (i = 0; i < num; i++) {
            * (int *) ((char *)base + i * size) = atoi(argv[i + 2]);
        }

        mergesort(base, num, size, * intcmp);

        for (i = 0; i < num; i++) {
            printf("%i ", * (int *) ((char *)base + i * size));
        }
        printf("\n");
    }
    else if (strcmp(argv[1], "char") == 0) {
        size = sizeof(char);
        base = malloc(num * size);

        for (i = 0; i < num; i++) {
            * ((char *)base + i * size) = * argv[i + 2];
        }

        mergesort(base, num, size, * chrcmp);
        for (i = 0; i < num; i++) {
            printf("%c ", * ((char *)base + i * size));
        }
        printf("\n");
    }
    else if (strcmp(argv[1], "str") == 0) {
        // PANIC!
        size = 100 * sizeof(char);
        base = malloc(num * size);

        for (i = 0; i < num; i++) {
            * ((char *)base + i * size) = * argv[i + 2];
        }

        mergesort(base, num, size, * strcmp);
    }
    else {
        // MORE PANIC!
        ;
    }

    //for (i = 1; i < argc; i++)
    //    printf("%s%s", argv[i], (i < argc-1) ? " " : "");
    //printf("\n");

    return 0;
}
