#include <string.h>

int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* arr1 = (const unsigned char*) s1;
    const unsigned char* arr2 = (const unsigned char*) s2;
    for (size_t i = 0; i < n; i++) {
        if (arr1[i] < arr2[i]) {
            return -1;
        }
        else if (arr1[i] > arr2[i]) {
            return 1;
        }
    }
    return 0;
}
