#include <string.h>

void* memcpy(void* __restrict s1, const void* __restrict s2, size_t n) {
    unsigned char* dst = (unsigned char*) s1;
    const unsigned char* src = (const unsigned char*) s2;
    for (size_t i = 0; i < n; i++) {
        *(dst++) = *(src++);
    }
    return s1;
}
