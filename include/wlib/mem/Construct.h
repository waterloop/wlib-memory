#ifndef __WLIB_MEMORY_CONSTRUCT_H__
#define __WLIB_MEMORY_CONSTRUCT_H__

#include <wlib/utility>
#include <wlib/type_traits>
#include <wlib/mem/Detail.h>

namespace wlp {
    template<typename T, typename... Args>
    typename det::enable_type_if<is_object<T>::value, T *>::type
    construct(void *ptr, Args... args) {
        ::new(ptr) T(forward<Args>(args)...);
        return reinterpret_cast<T *>(ptr);
    }
}

#endif
