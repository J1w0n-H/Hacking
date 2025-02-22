#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

int strcmp(const char *s1, const char *s2) {
    printf("[Hijacked] Comparing:\n");
    printf("String 1: %s\n", s1);
    printf("String 2: %s\n", s2);
    return 0;
}
