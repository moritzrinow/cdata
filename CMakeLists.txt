macro(use_c99)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
    endif ()
  else ()
    set (CMAKE_C_STANDARD 99)
  endif ()
endmacro(use_c99)

use_c99()

cmake_minimum_required(VERSION 2.8)
project(cdata C)

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
target_link_libraries(cdata m)

include_directories(src)

add_executable(arraytest src/test/array_test.c)
add_executable(listtest src/test/list_test.c)
add_executable(maptest src/test/map_test.c)

target_link_libraries(arraytest cdata)
target_link_libraries(listtest cdata)
target_link_libraries(maptest cdata)
