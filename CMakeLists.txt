cmake_minimum_required(VERSION 3.0.0)
project(Ecryption VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

FILE(GLOB compSec src/*.c)
add_executable(Ecryption src/main.c)

add_definitions(-w)

execute_process(COMMAND ./chngPerm.sh)

