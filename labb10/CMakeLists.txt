cmake_minimum_required(VERSION 3.10)
project(Ulamek)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

set(SOURCE_FILES
    fraction.cpp
    fraction.hpp)
    
set(LIBRARIES m)

add_executable(ulamek ${SOURCE_FILES})
target_link_libraries(ulamek ${LIBRARIES})