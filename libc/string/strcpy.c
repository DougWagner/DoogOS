#include <string.h>

char* strcpy(char* __restrict s1, const char* __restrict s2) {
    // section 7.24.1 of C11 standard says "For all functions in this subclause, each character shall
    // be interpreted as if it had the type unsigned char", so I am casting pointers as unsigned char
    // even though they are already of type char.
    unsigned char* dst = (unsigned char*) s1;
    const unsigned char* src = (const unsigned char*) s2;
    while (*src != 0) {
        *(dst++) = *(src++);
    }
    *dst = *src; // put '\0' at end of dst
    return s1;
}
