cmake_minimum_required(VERSION 3.5)
project(My_tiny_Web_Test)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(lock)
include_directories(log)

add_executable(My_tiny_Web_Test
        lock/locker.h
        log/block_queue.h
        log/log.cpp
        log/log.h
        Config.cpp
        Config.h
        main.cpp
        WebServer.cpp
        WebServer.h)


target_link_libraries(My_tiny_Web_Test pthread)