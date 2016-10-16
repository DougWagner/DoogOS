/* string.h functions as defined by C11 standard
 *
 * for some reason I have decided to delete identifier names in 
 * this header as functions are implemented. don't ask me why. */
#ifndef STRING_H
#define STRING_H

#include <stddef.h>

// Copyinhg functions
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
char* strcpy(char* __restrict, const char* __restrict);
char* strncpy(char* __restrict, const char* __restrict, size_t);

// Concatenation functions
char* strcat(char* __restrict, const char* __restrict);
char* strncat(char* __restrict, const char* __restrict, size_t);

// Comparison functions
int memcmp(const void*, const void*, size_t);
int strcmp(const char*, const char*);
int strcoll(const char* s1, const char* s2); // not implemented - no locale.h yet
int strncmp(const char*, const char*, size_t);
size_t strxfrm(char* __restrict s1, const char* __restrict s2, size_t n); // not implemented - no locale.h yet

// Search functions
void* memchr(const void*, int, size_t);
char* strchr(const char*, int);
size_t strcspn(const char*, const char*);
char* strpbrk(const char*, const char*);
char* strrchr(const char*, int);
size_t strspn(const char*, const char*);
char* strstr(const char*, const char*);
char* strtok(char* __restrict s1, const char* __restrict s2); // not implemented

// Miscellaneous functions
void* memset(void*, int, size_t);
char* strerror(int errnum); // not implemented - no error numbers yet
size_t strlen(const char*); 

#endif
