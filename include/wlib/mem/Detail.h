#ifndef __WLIB_MEMORY_DETAIL_H__
#define __WLIB_MEMORY_DETAIL_H__

namespace wlp {
    namespace det {
        template<bool Cond, typename T = void>  struct enable_type_if {};
        template<typename T>                    struct enable_type_if<true, T> { typedef T type; };
    }
}

#endif
