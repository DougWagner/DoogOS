#include <string.h>

void* memset(void* s, int c, size_t n) {
    unsigned char* dst = (unsigned char*) s;
    for (size_t i = 0; i < n; i++) {
        *(dst++) = (unsigned char) c;
    }
    return s;
}
