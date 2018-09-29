#include <wlib/memory>
#include <stdio.h>

static constexpr unsigned POOL_SIZE = 16400;
static char memory[POOL_SIZE];

using namespace wlp;

int main(void) {
    if (!mem::init(memory, POOL_SIZE)) {
        return -1;
    }

    char *pArr = create<char[]>(32);
    for (int i = 0; i < 32; ++i) {
        pArr[i] = 'a';
    }
    pArr[31] = 0;
    printf("String: %s\n", pArr);
    destroy<char[]>(pArr);
    printf("Test complete\n");
}
