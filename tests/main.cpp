#include <Cosa/UART.hh>

#define printf(...) tlsf_printf(__VA_ARGS__)

static constexpr BAUD_RATE = 9600;

extern void tlsf_printf(const char *fmt, ...);

void setup() {
    uart.begin(BAUD_RATE);
    printf("Hello %i\n", 5);
}

void loop() {
    delay(500);
}
