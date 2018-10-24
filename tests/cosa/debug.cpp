#include <Cosa/UART.hh>
#include <stdarg.h>
#include <stdio.h>

static constexpr int BUFFER_SIZE = 64;

static char buffer[BUFFER_SIZE];
static int wrt;

extern int sprintf(char *str, const char *fmt, ...);
extern int vsprintf(char *str, const char *fmt, va_list);

void tlsf_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    wrt = vsprintf(buffer, fmt, args);
    uart.write(buffer, wrt);
    va_end(args);
}

void tlsf_assert(bool expr, const char *msg) {
    if (!expr) { uart.write(msg, strlen(msg)); }
}
