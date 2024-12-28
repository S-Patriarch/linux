cmake_minimum_required(VERSION 3.25)

project(dcheck)

set(CMAKE_BUILD_TYPE Release)

set(SOURCES
    main.cc
    dcheck.cc
    logo.cc
    domain_checker.cc
    read_configuration.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
