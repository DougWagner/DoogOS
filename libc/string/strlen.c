#include <string.h>

size_t strlen(const char* str) {
    const char* i = str;
    for (; *i; ++i);
    return (size_t)(i - str);
}
