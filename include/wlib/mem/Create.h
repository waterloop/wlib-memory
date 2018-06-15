#ifndef __WLIB_MEMORY_CREATE_H__
#define __WLIB_MEMORY_CREATE_H__

#include <stdint.h>
#include <wlib/malloc>
#include <wlib/type_traits>
#include <wlib/mem/Detail.h>
#include <wlib/mem/Construct.h>

namespace wlp {
    template<typename T, typename... Args>
    typename det::enable_type_if<!is_array<T>::value, T *>::type
    create(Args... args) {
        void *ptr = mem::alloc(sizeof(T));
        return construct<T>(ptr, forward<Args>(args)...);
    }
    template<typename Arr, typename T = typename remove_extent<Arr>::type>
    typename det::enable_type_if<is_array<Arr>::value && det::is_alloc_primitive<T>::value, T *>::type
    create(size_t num) {
        void *ptr = mem::alloc(sizeof(T) * num);
        return reinterpret_cast<T *>(ptr);
    }
    template<typename Arr, typename T = typename remove_extent<Arr>::type>
    typename det::enable_type_if<is_array<Arr>::value && det::is_alloc_complex<T>::value, T *>::type
    create(size_t num) {
        void *mem = mem::alloc(sizeof(size_t) + sizeof(T) * num);
        size_t *count = reinterpret_cast<size_t *>(mem);
        *count = num;
        ++count;
        T *ptr = reinterpret_cast<T *>(count);
        for (size_t i = 0; i < num; ++i) 
        { construct<T>(ptr + i); }
        return ptr;
    }
}

#endif
