#include "../include/str.h"


size_t strlen(const char * str) {
    size_t counter = 0;
    while (* (str + counter) != '\0')
        counter++;
    return counter;
}

char * strcat(char * to, const char * from) {
    int l = strlen(to);
    int l2 = 0;
    while (* (from + l2) != '\0') {
        // to[l + l2] = from[l2];
        * (to + l + l2) = * (from + l2);
        l2++;
    }
    * (to + l + l2) = '\0';
    return to;
}

char * strcpy(char * to, const char * from) {
    * to = '\0';
    return strcat(to, from);
}

int strcmp(const char * str1, const char * str2) {
    return strlen(str1) - strlen(str2);
}
