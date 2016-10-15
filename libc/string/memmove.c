#include <string.h>

void* memmove(void* s1, const void* s2, size_t n) {
    unsigned char* dst = (unsigned char*) s1;
    const unsigned char* src = (const unsigned char*) s2;
    if (s1 < s2) {
        for (size_t i = 0; i < n; i++) {
            dst[i] = src[i];
        }
    }
    else {
        for (size_t i = n; i != 0; i--) {
            dst[i - 1] = src[i - 1];
        }
    }
    return s1;
}
