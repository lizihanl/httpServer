cmake_minimum_required(VERSION 3.21)
project(httpServer C)

set(CMAKE_C_STANDARD 17)

add_executable(httpServer main.c http.h tcp.h tcp.c)
add_executable(ndbmDatabase ndbm.c)
target_link_libraries(httpServer -ldb)
target_link_libraries(ndbmDatabase -ldb)