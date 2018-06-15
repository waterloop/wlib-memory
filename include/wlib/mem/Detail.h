#ifndef __WLIB_MEMORY_DETAIL_H__
#define __WLIB_MEMORY_DETAIL_H__

namespace wlp {
    namespace det {
        template<bool Cond, typename T = void>  struct enable_type_if {};
        template<           typename T>         struct enable_type_if<true, T> { typedef T type; };

        template<typename T> struct is_alloc_primitive :
            public or_<is_arithmetic<T>, is_pointer<T>>::type {};
        template<typename T> struct is_alloc_complex :
            public and_<is_object<T>, not_<is_alloc_primitive<T>>>::type {};
    }
}

#endif
