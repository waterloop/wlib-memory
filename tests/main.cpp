#include <stdio.h>

#include <wlib/mem/Construct.h>

typedef unsigned char byte;

using namespace wlp;

struct items {
    int count;
    double fraction;
    const char *label;

    items(int t_count, double t_fraction, const char *t_label) :
        count(t_count), fraction(t_fraction), label(t_label) {}
};

int main(int argc, char *argv[]) {
    static byte pool[512];
    static char label[] = "Items";
    items *ptr = construct<items>(pool, 5, 10.15, label);

    printf("%i, %.2f, %s\n", ptr->count, ptr->fraction, ptr->label);
}
