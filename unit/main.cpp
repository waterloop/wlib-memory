#include <stdio.h>
#include <wlib/memory>

typedef unsigned char byte;

using namespace wlp;

static char s_label[] = "None";

struct items {
    int count;
    double fraction;
    const char *label;

    items() : count(1), fraction(0), label(s_label) {}
    items(int t_count, double t_fraction, const char *t_label) :
        count(t_count), fraction(t_fraction), label(t_label) {}
    ~items() {
        printf("~items()\n");
    }

    void print() 
    { printf("%i, %.2f, %s\n", count, fraction, label); }
};

int main(int argc, char *argv[]) {
    static byte memory[1024];
    static byte pool[2 * sizeof(items)];
    static char label[] = "Items";
    mem::init(memory, 1024);

    int *iptr;
    items *ptr;
    unsigned long *lptr;

    // construct
    ptr = construct<items>(pool, 5, 10.15, label);
    ptr->print();
    deconstruct(ptr);

    lptr = construct<unsigned long>(pool, 167);
    printf("%li\n", *lptr);
    deconstruct(lptr);

    // create
    iptr = create<int>(25);
    printf("%i\n", *iptr);
    destroy(iptr);

    ptr = create<items>(55, 66.67, label);
    ptr->print();
    destroy(ptr);

    iptr = create<int[]>(4);
    iptr[0] = 1;
    iptr[1] = 2;
    iptr[2] = 4;
    iptr[3] = 8;
    printf("%i, %i, %i, %i\n", iptr[0], iptr[1], iptr[2], iptr[3]);
    destroy<int[]>(iptr);

    ptr = create<items[]>(4);
    ptr[0].print();
    ptr[1].print();
    ptr[2].print();
    ptr[3].print();
    destroy<items[]>(ptr);
}
