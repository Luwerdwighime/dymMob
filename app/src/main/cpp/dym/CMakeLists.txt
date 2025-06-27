cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(dym LANGUAGES C CXX)

set(DYM_SOURCES
  src/main.cpp
  src/Cfg.cpp
  src/Fs.cpp
  src/User.cpp
  src/Yt.cpp
  src/lib/inih/INIReader.cpp
  src/lib/inih/ini.c
)

add_executable(dym ${DYM_SOURCES})

target_include_directories(dym PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/inih
)
