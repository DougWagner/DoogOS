#include <string.h>

int strncmp(const char* s1, const char* s2, size_t n) {
    // i'm not sure if i am supposed to cast these as unsigned char, but whatever i'm doing it anyway.
    // the C standard is too damn vague; all these functions are probably going to change at some point.
    const unsigned char* str1 = (const unsigned char*) s1;
    const unsigned char* str2 = (const unsigned char*) s2;
    for (size_t i = 0; i < n && (*str1 != 0 || *str2 != 0); i++, str1++, str2++) {
        if (*str1 < *str2) {
            return -1;
        }
        else if (*str1 > *str2) {
            return 1;
        }
    }
    return 0;
}
