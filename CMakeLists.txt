cmake_minimum_required(VERSION 3.28)
project(lastsnake)

set(CMAKE_CXX_STANDARD 17)

add_executable(lastsnake main.cpp
        map.hpp
        input.hpp
        snake.hpp
        randm.hpp
        definitions.hpp
)
