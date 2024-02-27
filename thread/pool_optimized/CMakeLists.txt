# 
# (c) 2024 S-Patriarch
# 

cmake_minimum_required(VERSION 3.25)

project(tpool)

set(ts_VERSION_MAJOR 1)
set(ts_VERSION_MINOR 0)
set(ts_VERSION "${ts_VERSION_MAJOR}.${ts_VERSION_MINOR}")

set(CMAKE_BUILD_TYPE Release)

set(SOURCES
   main.cc
   src/t_pool.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
   ${PROJECT_NAME} PRIVATE
   -pthread
)

set_target_properties(
   ${PROJECT_NAME} PROPERTIES
   CXX_STANDARD 17
   CXX_STANDARD_REQUIRED ON
)
