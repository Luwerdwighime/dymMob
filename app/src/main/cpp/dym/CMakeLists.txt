cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
project(dym LANGUAGES C CXX)

set(H_FILES
  src/config.hpp
  src/Cfg.hpp
  src/Fs.hpp
  src/User.hpp
  src/Yt.hpp
  src/lib/inih/ini.h
  src/lib/inih/INIReader.hpp
)
set(C_FILES src/lib/inih/ini.c)
set_source_files_properties(${C_FILES} PROPERTIES LANGUAGE C)
set(CPP_FILES
  src/main.cpp
  src/Cfg.cpp
  src/Fs.cpp
  src/User.cpp
  src/Yt.cpp
  src/lib/inih/INIReader.cpp
)
add_executable(dym ${H_FILES} ${C_FILES} ${CPP_FILES})

