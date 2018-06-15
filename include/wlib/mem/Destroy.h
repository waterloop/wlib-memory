#ifndef __WLIB_MEMORY_DESTORY_H__
#define __WLIB_MEMORY_DESTORY_H__

#include <wlib/malloc>
#include <wlib/mem/Detail.h>
#include <wlib/mem/Deconstruct.h>

namespace wlp {
    template<typename T>
    typename det::enable_type_if<!is_array<T>::value, void>::type
    destroy(T *ptr) {
        deconstruct<T>(ptr);
        mem::free(ptr);
    }
    template<typename Arr, typename T = typename remove_extent<Arr>::type>
    typename det::enable_type_if<is_array<Arr>::value && det::is_alloc_primitive<T>::value, void>::type
    destroy(T *ptr) 
    { mem::free(ptr); }
    template<typename Arr, typename T = typename remove_extent<Arr>::type>
    typename det::enable_type_if<is_array<Arr>::value && det::is_alloc_complex<T>::value, void>::type
    destroy(T *ptr) {
        size_t *count = reinterpret_cast<size_t *>(ptr);
        --count;
        size_t num = *count;
        for (size_t i = 0; i < num; ++i)
        { deconstruct<T>(ptr + i); }
        mem::free(count);
    }
}

#endif
