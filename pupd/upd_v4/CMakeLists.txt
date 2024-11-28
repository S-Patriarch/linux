cmake_minimum_required(VERSION 3.5)

project(upd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(upd
  main.cc
  upd.cc
  is_locale_available.cc
  detect_package_manager.cc
  logo.cc
  help.cc
  command_generator.cc
)

install(TARGETS upd
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
