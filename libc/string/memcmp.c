#include <string.h>

int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* arr1 = (const unsigned char*) s1;
    const unsigned char* arr2 = (const unsigned char*) s2;
    for (size_t i = 0; i < n; i++, arr1++, arr2++) {
        if (*arr1 < *arr2) {
            return -1;
        }
        else if (*arr1 > *arr2) {
            return 1;
        }
    }
    return 0;
}
