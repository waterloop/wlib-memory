#ifndef __WLIB_MEMORY_PLACEMENT_H__
#define __WLIB_MEMORY_PLACEMENT_H__

void *operator new(decltype(sizeof(0)), void *ptr) noexcept { return ptr; }

#endif
