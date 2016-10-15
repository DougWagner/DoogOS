#include <string.h>

int strcmp(const char* s1, const char* s2) {
    const unsigned char* str1 = (const unsigned char*) s1;
    const unsigned char* str2 = (const unsigned char*) s2;
    for (size_t i = 0; str1[i] != 0 || str2[i] != 0; i++) {
        if (str1[i] < str2[i]) {
            return -1;
        }
        else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}
