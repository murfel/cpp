#include <stddef.h>

typedef int (*compar_t)(const void*, const void*);

int mergesort (void* base, size_t num, size_t size, compar_t compar);

int intcmp (const void* a, const void* b);
int chrcmp (const void* a, const void* b);
int chrcmp2 (const void** a, const void** b);
int strcmp2 (const void** a, const void** b);

void cpy (void * a, void * b, size_t size);
