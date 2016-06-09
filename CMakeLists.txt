cmake_minimum_required(VERSION 2.8.9)
project(pilot)
find_package (Threads)

file(GLOB SOURCES "source/src/*.cpp" "source/include/*.hpp" "../adt/source/src/*.cpp" "../adt/source/include/*.hpp" "../sharedobjects/source/src/*.cpp" "../sharedobjects/source/include/*.hpp")
file(GLOB SOURCES_TEST "source/src/*.cpp" "source/include/*.hpp" "../adt/source/src/*.cpp" "../adt/source/include/*.hpp" "../sharedobjects/source/src/*.cpp" "../sharedobjects/source/include/*.hpp" "test/*.cpp" "test/*.hpp")
list(REMOVE_ITEM SOURCES_TEST ${CMAKE_CURRENT_SOURCE_DIR}/source/src/main.cpp)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++11" )

include_directories(
  ../adt/source/include
  ../sharedobjects/source/include
  ../deps/gtest-1.7.0/include
  ../deps/gtest-1.7.0)

link_directories(../deps/gtest-1.7.0/src ../adt/source/src ../sharedobjects/source/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)

add_executable(PilotSimulation_test ${SOURCES_TEST})
target_link_libraries(PilotSimulation_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})

