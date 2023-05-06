cmake_minimum_required(VERSION 3.25)
project(Zinka)

set(CMAKE_CXX_STANDARD 23)

add_executable(Zinka main.cpp
        threadPool/threadPool.hpp
        threadPool/threadPool.cpp
        sync/blockingQueue.hpp
        threadPool/detail/waitGroup.hpp
        threadPool/detail/waitGroup.cpp
        async/future/detail/sharedChannel.hpp
        async/future/future.hpp
        async/future/promise.hpp
        )
