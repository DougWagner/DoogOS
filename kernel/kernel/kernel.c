#include <kernel/tty.h>
#include <kernel/kernel.h>
#include <string.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}



void kernel_main(void) {
    printk("Welcome to DoogOS! Have fun doing nothing!\n");
    delay(100);
    printk("We will be testing the printk function now!\n");
    delay(100);
    char* alpha = "abcdefghijklmnopqrstuvwxyz";
    printk("Alphabet: %s\n", alpha);
    delay(100);
    char letter = 'q';
    printk("This should be the letter \"q\": %c\n", letter);
    delay(100);
    int num = 514738;
    int num2 = 1234;
    int num3 = 7;
    int num4 = 259919918;
    int num5 = 1234567890;
    printk("lots of nums: %d\n%d\n%d\n%d\n%d\n", num, num2, num3, num4, num5);
    delay(100);
    printk("now for the real test! MULTIPLE TYPES!!!\n");
    printk("alpha: %s\nchar: %c\nint: %d\n", alpha, letter, num4);
    delay(100);
    printk("hopefully it all worked!\n");
    char current[2];
    current[1] = 0;
    for (size_t i = 0;;i++) {
        current[0] = alpha[i % 26];
        printk(current);
        delay(1);
    }
}
