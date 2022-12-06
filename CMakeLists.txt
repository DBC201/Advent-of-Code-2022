cmake_minimum_required (VERSION 3.8)

project (AOC2021)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test_all ${CMAKE_CURRENT_SOURCE_DIR}/test/test_all.cpp)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_executable(day_1 ${SOURCE_DIR}/01.cpp)
set_target_properties(day_1 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_2 ${SOURCE_DIR}/02.cpp)
set_target_properties(day_2 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_3 ${SOURCE_DIR}/03.cpp)
set_target_properties(day_3 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_4 ${SOURCE_DIR}/04.cpp)
set_target_properties(day_4 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_5 ${SOURCE_DIR}/05.cpp)
set_target_properties(day_5 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_6 ${SOURCE_DIR}/06.cpp)
set_target_properties(day_6 PROPERTIES EXCLUDE_FROM_ALL TRUE)
