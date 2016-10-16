#include <string.h>

char* strpbrk(const char* s1, const char* s2) {
    const unsigned char* str1 = (const unsigned char*) s1;
    const unsigned char* str2 = (const unsigned char*) s2;
    while (*str1 != 0) {
        if (strchr(str2, *str1) != NULL) {
            return str1;
        }
    }
    return NULL;
}
