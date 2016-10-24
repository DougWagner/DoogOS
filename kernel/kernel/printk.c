#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <kernel/kernel.h>
#include <kernel/tty.h>

// check if format is valid and return arg count
// NOTE: this function might end up being wasted cycles. will decide later if this function stays or goes.
static int checkfmt(const char* __restrict fmt) {
    int argc = 0;
    for (; *fmt != '\0'; fmt++) {
        if (*fmt == '%') {
            switch (*(fmt + 1)) {
            case 'd':
            case 'i':
            case 'o':
            case 'u':
            case 'x':
            case 'X':
            // no case for 'f' 'F' 'e' 'E' 'g' 'G' 'a' or 'A' yet - i don't know how to convert floating point to string yet
            case 'c':
            case 's':
            case 'p':
            //case 'n': // currently not being used - will implement later. (maybe)
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

// printk function works, but will probably not be portable to other architectures. fix later.
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
            // --INTEGER TYPES--
            case 'u': case 'o': case 'x': case 'X': case 'd': case 'i': case 'p': ; // case for 'p' will only work here on 32 bit systems.
                unsigned int u = va_arg(args, unsigned int);
                char intstr[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                size_t len = 0;
                // there is probably a better way to do this than using goto statements, but whatever.
                if (*fmt == 'u')
                    goto printint;
                else if (*fmt == 'o')
                    goto printoct;
                else if (*fmt == 'x' || *fmt == 'X')
                    goto printhex;
                else if (*fmt == 'p') {
                    t_writestr("0x");
                    written += 2;
                    remaining -= 2;
                    goto printhex;
                }
                else { // (*fmt == 'd' || *fmt == 'i')
                    int d = (int) u; // if integer is negative, converting from unsigned back to signed SHOULD still be negative...
                    if (d < 0) {
                        t_putchar('-');
                        written += 1;
                        remaining -= 1;
                        u = (unsigned int) d * -1;
                    }
                    else {
                        u = (unsigned int) d;
                    }
                }
            printint:
                for (size_t i = 0; u > 0; u /= 10, i++, len++) {
                    intstr[i] = (u % 10) + '0';
                }
                goto finishprintnum;
            printoct:
                for (size_t i = 0; u > 0; u >>= 3, i++, len++) {
                    intstr[i] = (u % 8) + '0';
                }
                goto finishprintnum;
            printhex:
                for (size_t i = 0; u > 0; u >>= 4, i++, len++) {
                    char digit = u % 16;
                    if (digit >= 10) {
                        intstr[i] = *fmt == 'X' ? 'A' + (digit - 10) : 'a' + (digit - 10);
                    }
                    else {
                        intstr[i] = '0' + digit;
                    }
                }
                // no goto necessary here because fallthrough
            finishprintnum:
                len--;
                for (size_t i = 0; i < len; i++, len--) {
                    char temp = intstr[i];
                    intstr[i] = intstr[len];
                    intstr[len] = temp;
                }
                t_writestr(intstr);
                written += strlen(intstr);
                remaining -= strlen(intstr);
                break;

            // --CHAR AND STRINGS--
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
