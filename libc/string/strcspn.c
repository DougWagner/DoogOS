#include <string.h>

size_t strcspn(const char* s1, const char* s2) {
    // once again, not sure if i need to cast as unsigned char. doing it anyway.
    const unsigned char* str1 = (const unsigned char*) s1;
    const unsigned char* str2 = (const unsigned char*) s2;
    size_t len;
    for (len = 0; *str1 != 0; len++, str1++) {
        if (strchr(str2, *str1) != NULL) {
            return len;
        }
    }
    return len;
}
