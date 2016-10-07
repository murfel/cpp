#include "../src/mergesort.c"

int mergesort (void* base, size_t num, size_t size, int (*compar)(const char*, const char*));

int intcmp (const char* a, const char* b);
int chrcmp (const char* a, const char* b);

void cpy (void * a, void * b, size_t size);
