#include <string.h>

char* strrchr(const char* s, int c) {
    size_t len = strlen(s);
    for (size_t i = len; i > 0; i--) {
        if (s[i] == (char) c) {
            return (char*) &s[i];
        }
    }
    if (*s == (char) c) {
        return (char*) s;
    }
    return NULL;
    // alternate implementation? slightly less sure if it will work - probably should test all of these
    /*
    size_t len = strlen(s);
    s += len;
    for (size_t i = 0; i <= len; i++, s--) {
        if (*s == (char) c) {
            return s;
        }
    }
    return NULL;
    */
}
