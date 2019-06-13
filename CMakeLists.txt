cmake_minimum_required(VERSION 3.1)
project(cdata)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)

# cdata source files
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
    src/set.h
    src/set.c
)

# add cdata library
add_library(cdata STATIC ${cdata_SOURCES})

# link math library on unix systems, MSVC has it included
if (UNIX)
	target_link_libraries(cdata m)
endif (UNIX)

include_directories(src)

# add test executables
add_executable(arraytest src/test/array_test.c)
add_executable(listtest src/test/list_test.c)
add_executable(maptest src/test/map_test.c)
add_executable(settest src/test/set_test.c)

# link tests with the cdata library
target_link_libraries(arraytest cdata)
target_link_libraries(listtest cdata)
target_link_libraries(maptest cdata)
target_link_libraries(settest cdata)
