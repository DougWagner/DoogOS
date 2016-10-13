#include <string.h>

size_t strlen(const char* str) {
    volatile char* i = (char*)str;
    for (; *i; ++i);
    return (size_t)(i - str);
}
