cmake_minimum_required(VERSION 3.16)

project(app VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES Vector.h VectorLib.cpp)


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app src/pantry/pantry.cpp)
add_executable(tests test.cpp)

target_link_libraries(tests PUBLIC gtest_main)
