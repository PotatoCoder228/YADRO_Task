cmake_minimum_required(VERSION 3.16)
project(YADRO_Task)

set(CMAKE_CXX_STANDARD 17)

if (MSVC_VERSION)
    set(CMAKE_CXX_FLAGS_DEBUG "/Wall /pedantic /g3 /O0")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -pedantic -g3 -O0")
endif ()
if (MSVC_VERSION)
    set(CMAKE_CXX_FLAGS "/Wall /pedantic /O2")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -pedantic -O2")
endif ()

add_executable(YADRO_Task src/main.cpp include/all_headers.h src/app.cpp include/app.h src/csv_table.cpp include/csv_table.h)
