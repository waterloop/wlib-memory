#if defined(WIO_PLATFORM_AVR) && defined(WIO_FRAMEWORK_ARDUINO)

#include <new.h>

void* operator new(decltype(sizeof(0)), void* ptr) noexcept {
    return ptr;
}

#elif defined(WIO_PLATFORM_NATIVE)

#include <new>

#else

#include <stdlib.h>

void *operator new(decltype(sizeof(0)) n) noexcept(false) {
    return malloc(n);
}

void *operator new(decltype(sizeof(0)), void *ptr) noexcept {
    return ptr;
}

void operator delete(void *ptr) throw() {
    free(ptr);
}

void *operator new[](decltype(sizeof(0)) n) noexcept(false) {
    return malloc(n);
}

void operator delete[](void *ptr) throw() {
    free(ptr);
}

#endif
