cmake_minimum_required(VERSION 3.25)

project(upd)

set(CMAKE_BUILD_TYPE Release)

set(SOURCES
  main.cc
  upd.cc
  is_locale_available.cc
  detect_package_manager.cc
  logo.cc
  help.cc
  command_generator.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
)
