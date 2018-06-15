#ifndef __WLIB_MEMORY_LEGACY_H__
#define __WLIB_MEMORY_LEGACY_H__

#include <wlib/mem/Create.h>
#include <wlib/mem/Destroy.h>

namespace wlp {
    template<typename T, typename... Args>
    T *malloc(Args... &&args) 
    { return create<T>(forward<Args>(args)...); }
    template<typename T>
    void free(T *ptr)
    { return destroy<T>(ptr); }
}

#endif
