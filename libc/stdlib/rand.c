#include <stdlib.h>

unsigned long long int next = 1;

// a really simple linear congruential generator - borrowed from K&R c book
// TODO: write a better random number generator
int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int) next % 2147483647;
}

void srand(unsigned int seed) {
    next = seed;
}