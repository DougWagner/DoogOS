#include <kernel/tty.h>
#include <string.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}

void kernel_main(void) {
    t_writestr("Hello kernel world!\n");
    t_writestr("blahblahblah\n");
    t_writestr("gonna test some string.h functions now\n");
    char* str = "testing strcpy";
    char arr[20];
    char* newstr = arr;
    newstr = strcpy(str, newstr);
    delay(20);
    t_writestr(newstr);
    delay(20);
    t_writestr("\n");
    /*
    char* str = "abcdefghijklmnopqrstuvwxyz";
    char current[2];
    current[1] = 0;
    for (size_t i = 0;;i++) {
        current[0] = str[i % 26];
        t_writestr(current);
        delay(1);
    }
    */
}
