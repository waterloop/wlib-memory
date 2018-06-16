cmake_minimum_required(VERSION 3.1.0)
project(wlib-memory)

set(CMAKE_CXX_STANDARD 11)

set(PACKAGE wlib-memory)
set(${PACKAGE}_dir ${CMAKE_CURRENT_LIST_DIR})
set(${PACKAGE}_include ${${PACKAGE}_dir}/include)

set(TARGET tests)
set(${TARGET}_dir ${CMAKE_CURRENT_LIST_DIR}/tests)
set(${TARGET}_PRIVATE_headers wlib-memory)

set(MODULES_DIR ${CMAKE_CURRENT_LIST_DIR}/.wio/node_modules)
set(MODULES wlib-tlsf wlib-malloc)
set(HEADERS wlib-tmp)

set(wlib-malloc_PRIVATE_dependencies wlib-tlsf)
set(wlib-memory_PUBLIC_dependencies wlib-malloc)
set(wlib-memory_PUBLIC_headers wlib-tmp)
set(tests_PRIVATE_headers wlib-memory)

set(wlib-tlsf_PRIVATE_defines
    WLIB_TLSF_64BIT
    WLIB_TLSF_LOG2_ALIGN=3
    WLIB_TLSF_LOG2_DIV=3
    WLIB_TLSF_LOG2_MAX=11
    )

foreach(module ${MODULES})
    set(${module}_dir ${MODULES_DIR}/${module})
endforeach()

foreach(header ${HEADERS})
    set(header_dir ${MODULES_DIR}/${header})
    set(${header}_include ${header_dir}/include)
endforeach()

set(HEADERS ${HEADERS} ${PACKAGE})

foreach(module ${MODULES})
    set(module_dir ${${module}_dir})
    set(${module}_include ${module_dir}/include)
    set(${module}_src ${module_dir}/src)
endforeach()

foreach(module ${MODULES})
    file(GLOB_RECURSE ${module}_files ${${module}_src}/*.cpp)
    add_library(${module} ${${module}_files})
    target_include_directories(${module} PRIVATE ${${module}_include})
    foreach(scope PRIVATE PUBLIC)
        target_compile_definitions(${module} ${scope} ${${module}_${scope}_defines})
    endforeach()
endforeach()

file(GLOB_RECURSE ${TARGET}_files ${${TARGET}_dir}/*.cpp)
add_executable(${TARGET} ${${TARGET}_files})

set(MODULES ${MODULES} ${TARGET})

foreach(scope PRIVATE PUBLIC)
    foreach(module ${MODULES})
        set(dependencies ${${module}_${scope}_dependencies})
        foreach(dependency ${dependencies})
            target_link_libraries(${module} ${dependency})
        endforeach()
        while(dependencies)
            set(loop ${dependencies})
            set(dependencies)
            foreach(dependency ${loop})
                target_include_directories(${module} ${scope} ${${dependency}_include})
                set(dependencies ${dependencies} ${${dependency}_PUBLIC_dependencies})
                set(dependencies ${dependencies} ${${dependency}_PUBLIC_headers})
            endforeach()
        endwhile()
    endforeach()
endforeach()

foreach(scope PRIVATE PUBLIC)
    foreach(module ${MODULES})
        set(headers ${${module}_${scope}_headers})
        while(headers)
            set(loop ${headers})
            set(headers)
            foreach(header ${loop})
                target_include_directories(${module} ${scope} ${${header}_include})
                target_link_libraries(${module} ${${header}_PUBLIC_dependencies})
                set(headers ${headers} ${${header}_PUBLIC_dependencies})
                set(headers ${headers} ${${header}_PUBLIC_headers})
            endforeach()
        endwhile()
    endforeach()
endforeach()
