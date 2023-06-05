cmake_minimum_required(VERSION 3.16)
project(YADRO_Task)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -pedantic -g3 -O0")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -O2")
add_executable(YADRO_Task src/main.cpp include/allheaders.h src/App.cpp include/App.h src/CsvTable.cpp src/CsvTable.h)
