#include <Cosa/UART.hh>

#include <wlib/memory>

#define printf(...) tlsf_printf(__VA_ARGS__)

static constexpr int BAUD_RATE = 9600;

extern void tlsf_printf(const char *fmt, ...);

static char string0[] = "zero";
static char string1[] = "first";
static char string2[] = "second";
static char string3[] = "third";

static char *strings[] = {string0, string1, string2, string3};

static constexpr int POOL_SIZE = 1024;
static char memory[POOL_SIZE];

static int dest = 0;

using namespace wlp;

struct item {
    int integer;
    float floating;
    const char *string;

    item() : integer(0), floating(0), string(string0) {}
    item(int i, float f, const char *s) : integer(i), floating(f), string(s) {}
    ~item() { ++dest; }
};

void setup() {
    uart.begin(BAUD_RATE);
    printf("Hello %i\n", 55);

    if (mem::init(memory, POOL_SIZE)) 
    { tlsf_printf("Memory initialized\n"); } 
    else { tlsf_printf("Failed to initialize memory\n"); }
}

void loop() {
    tlsf_printf("Element test: ");
    item *p_item = create<item>(dest, 12.3f, strings[((int) abs(dest)) % 4]);
    tlsf_printf("%i, %i, %s\n", p_item->integer, (int) p_item->floating, p_item->string);
    destroy<item>(p_item);

    item *p_arr_item = create<item[]>(16);
    destroy<item[]>(p_arr_item);
    delay(50);
}
