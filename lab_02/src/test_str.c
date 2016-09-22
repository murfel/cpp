#include <assert.h>
#include "../include/test_str.h"
#include "str.c"


void test_strlen() {
    const char s1[] = "";
    const char s2[] = "abcabc";
    assert(strlen(s1) == 0);
    assert(strlen(s2) == 6);
    return;
}

void test_strcat() {
    const char s1[] = "abc";
    const char s2[] = "xyzt";
    char s3[8] = "abc";
    int i, j;
    assert(* strcat(s3, s2) == * s3);
    for (i = 0; i < strlen(s1) - 1; i++) {
        assert(* (s3 + i) == * (s1 + i));
    }
    i++;
    for (j = 0; j < strlen(s2); j++) {
        assert(* (s3 + i + j) == * (s2 + j));
    }
    return;
}

void test_strcpy() {
    char s1[] = "abcabc";
    const char s2[] = "xyzt";
    assert(* strcpy(s1, s2) == * s1);
    int i;
    for (i = 0; i < strlen(s2); i++) {
        assert(* (s1 + i) == * (s2 + i));
    }
    return;
}

void test_strcmp() {
    const char s1[] = "abc";
    const char s2[] = "xyz";
    const char s3[] = "abcabc";
    assert(strcmp(s1, s3) < 0);
    assert(strcmp(s1, s2) == 0);
    assert(strcmp(s3, s1) > 0);
    return;
}

int main() {

    test_strlen();
    test_strcat();
    test_strcpy();
    test_strcmp();

    return 0;
}
