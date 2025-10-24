cmake_minimum_required(VERSION 3.15)
project(mai_oop_cpp_task_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/Rhomb.cpp
    src/Pentagon.cpp
    src/Hexagon.cpp
    src/Array.cpp
)

add_library(figure_lib ${SOURCES})
target_include_directories(figure_lib PUBLIC include)
add_executable(lab03 src/main.cpp)
target_link_libraries(lab03 PRIVATE figure_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_figure tests/test_figure.cpp)
target_link_libraries(test_figure PRIVATE figure_lib gtest_main)
add_test(NAME FigureTests COMMAND test_figure)
