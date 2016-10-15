#include <string.h>

char* strcat(char* __restrict s1, const char* __restrict s2) {
    unsigned char* dst = (unsigned char*) s1;
    const unsigned char* src = (const unsigned char*) s2;
    while (*dst != 0) {
        ++dst;
    }
    while (*src != 0) {
        *(dst++) = *(src++);
    }
    *dst = *src;
    return s1;
}
