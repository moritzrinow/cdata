cmake_minimum_required(VERSION 3.1)
project(cdata)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

set(cdata_SOURCES
    src/cdata.h
    src/array.h
    src/array.c
    src/list.h
    src/list.c
    src/map.h
    src/map.c
    src/types.h
    src/types.c
    src/hash.h
    src/hash.c
    src/sort.h
    src/sort.c
)

add_library(cdata STATIC ${cdata_SOURCES})

include_directories(src)

add_executable(arraytest src/test/array_test.c)
add_executable(listtest src/test/list_test.c)
add_executable(maptest src/test/map_test.c)

target_link_libraries(arraytest cdata)
target_link_libraries(listtest cdata)
target_link_libraries(maptest cdata)
