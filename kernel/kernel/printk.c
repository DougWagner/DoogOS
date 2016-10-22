#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <kernel/kernel.h>
#include <kernel/tty.h>

// check if format is valid and return arg count
static int checkfmt(const char* __restrict fmt) {
    int argc = 0;
    for (; *fmt != '\0'; fmt++) {
        if (*fmt == '%') {
            switch (*(fmt + 1)) {
            case 'c':
            case 's':
            case 'd':
            case '%':
                fmt++;
                argc++;
                break;
            default:
                return -1;
            }
        }
    }
    return argc;
}

int printk(const char* __restrict fmt, ...) {
    int argc;
    if ((argc = checkfmt(fmt)) == -1) { 
        t_writestr("printk - error: invalid format\n");
        return -1;
    }
    if (argc == 0) {
        t_writestr(fmt);
        return strlen(fmt);
    }
    va_list args;
    va_start(args, fmt);
    // ok we have the arg list now. apparently we can't check if 
    int written = 0;
    int remaining = INT_MAX;
    for (; *fmt != '\0'; fmt++) {
        if (remaining == 0) {
            t_writestr("printk - error: no more room remaining\n");
            return -1;
        }
        if (*fmt != '%') {
            t_putchar(*fmt);
            written += 1;
            remaining -= 1;
        }
        else {
            fmt++;
            switch (*fmt) {
            case 'c': ;
                char c = (char) va_arg(args, int);
                t_putchar(c);
                written += 1;
                remaining -= 1;
                break;
            case 's': ;
                char* s = va_arg(args, char*);
                t_writestr(s);
                written += strlen(s);
                remaining -= strlen(s);
                break;
            case 'd': ;
                int d = va_arg(args, int);
                char numstr[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                size_t len = 0;
                for (size_t i = 0; d > 0; d /= 10, i++, len++) {
                    numstr[i] = (d % 10) + '0';
                }
                len--;
                for (size_t i = 0; i < len; i++, len--) {
                    char temp = numstr[i];
                    numstr[i] = numstr[len];
                    numstr[len] = temp;
                }
                t_writestr(numstr);
                written += strlen(numstr);
                remaining -= strlen(numstr);
                break;
            case '%':
                t_putchar('%');
                written += 1;
                remaining -= 1;
                break;
            default:
                t_writestr("printk - error: somehow format check failed. weird.\n");
                return -1;
            }
        }
    }
    return written;
}
