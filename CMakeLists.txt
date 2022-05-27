cmake_minimum_required(VERSION 3.16)

project(app VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_Declare(
   jsoncpp
   GIT_REPOSITORY      https://github.com/open-source-parsers/jsoncpp
   GIT_TAG master
)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(jsoncpp)

set(PROJECT_SOURCES Vector.h VectorLib.cpp)


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app src/pantry/Pantry.cpp)
add_executable(json_reader_example json_example/reader.cpp)
add_executable(json_writer_example json_example/writer.cpp)
add_executable(tests test.cpp)

target_link_libraries(tests PUBLIC gtest_main)
target_link_libraries(json_reader_example jsoncpp_lib)
target_link_libraries(json_writer_example jsoncpp_lib)
