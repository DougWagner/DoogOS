#include <string.h>

void* memchr(const void* s, int c, size_t n) {
    const unsigned char* src = (const unsigned char*)s;
    for (size_t i = 0; i < n; i++, src++) {
        if (*src == (unsigned char) c) {
            return (void*)src;
        }
    }
    return NULL;
}
