﻿cmake_minimum_required (VERSION 3.8)

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

add_executable(day_7 ${SOURCE_DIR}/07.cpp)
set_target_properties(day_7 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_8 ${SOURCE_DIR}/08.cpp)
set_target_properties(day_8 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_9 ${SOURCE_DIR}/09.cpp)
set_target_properties(day_9 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_10 ${SOURCE_DIR}/10.cpp)
set_target_properties(day_10 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_11 ${SOURCE_DIR}/11.cpp)
set_target_properties(day_11 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_12 ${SOURCE_DIR}/12.cpp)
set_target_properties(day_12 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_13 ${SOURCE_DIR}/13.cpp)
set_target_properties(day_13 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_14 ${SOURCE_DIR}/14.cpp)
set_target_properties(day_14 PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_executable(day_15 ${SOURCE_DIR}/15.cpp)
set_target_properties(day_15 PROPERTIES EXCLUDE_FROM_ALL TRUE)
