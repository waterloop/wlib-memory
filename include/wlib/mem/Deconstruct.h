#ifndef __WLIB_MEMORY_DECONSTRUCT_H__
#define __WLIB_MEMORY_DECONSTRUCT_H__

#include <wlib/utility>
#include <wlib/type_traits>
#include <wlib/mem/Detail.h>

namespace wlp {
    template<typename T>
    typename det::enable_type_if<is_object<T>::value, void>::type
    deconstruct(T *ptr) { ptr->~T(); }
}

#endif
