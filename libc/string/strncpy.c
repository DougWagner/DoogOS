#include <string.h>

char* strncpy(char* __restrict s1, const char* __restrict s2, size_t n) {
    // see comment at beginning of strcpy.c
    unsigned char* dst = (unsigned char*) s1;
    const unsigned char* src = (const unsigned char*) s2;
    size_t i;
    for (i = 0; i < n && *src != 0; i++) {
        *(dst++) = *(src++);
    }
    if (*src == 0 && i < n) {
        for (; i < n; i++) {
            *(dst++) = 0;
        }
    }
    return s1;
}
