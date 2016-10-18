#include <string.h>

int checkstr(const unsigned char* s1, const unsigned char* s2) {
    for (; *s2 != 0; s1++, s2++) {
        if (*s1 != *s2) {
            return 0;
        }
    }
    return 1;
}

char* strstr(const char* s1, const char* s2) {
    const unsigned char* str1 = (const unsigned char*) s1;
    const unsigned char* str2 =( const unsigned char*) s2;
    for (; *str1 != 0; str1++) {
        if (*str1 == *str2) {
            if (checkstr(str1, str2)) {
                return (char*) str1;
            }
        }
    }
    return NULL;
}
