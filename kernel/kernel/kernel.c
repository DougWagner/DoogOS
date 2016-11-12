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
    printk("negative number test: %d\n", -4112583);
    delay(100);
    int int1 = 9193831;
    printk("positive integer: %d\n", int1);
    delay(100);
    unsigned int u1 = 4111111111;
    printk("unsigned integer: %u\n", u1);
    delay(100);
    printk("unsigned int in octal: %o\n", u1);
    delay(100);
    printk("unsigned int in hex: %x\n", u1);
    delay(100);
    printk("unsigned int in upper hex: %X\n", u1);
    delay(100);
    printk("testing pointers now\n");
    printk("alpha addr: %p\nint1 addr: %p\nu1 addr: %p\n", alpha, &int1, &u1);
    delay(100);
    int x = 7, y = 0;
    printk("divide by zero time!\n%d\n", x / y);
    char current[2];
    current[1] = 0;
    for (size_t i = 0;;i++) {
        current[0] = alpha[i % 26];
        printk(current);
        delay(1);
    }
}
