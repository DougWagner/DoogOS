#include <string.h>

char* strncat(char* __restrict s1, const char* __restrict s2, size_t n) {
    unsigned char* dst = (unsigned char*) s1;
    const unsigned char* src = (const unsigned char*) s2;
    while (*dst != 0) {
        ++dst;
    }
    for (size_t i = 0; i < n && *src != 0; i++) {
        *(dst++) = *(src++);
    }
    *dst = 0;
    return s1;
}
