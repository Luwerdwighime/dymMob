cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(dym LANGUAGES C CXX)

add_library(inih
  lib/inih/ini.c
  lib/inih/INIReader.cpp
)

target_include_directories(inih PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/inih
)

add_executable(dym
  main.cpp
)

target_include_directories(dym PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(dym PRIVATE inih)

