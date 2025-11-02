cmake_minimum_required(VERSION 3.10)
project(bhesh)

include_directories(include src)

set(SOURCES
   src/shell.c
   src/shell_exec.c
   src/bhesh.c
   src/input.c
   src/prompt.c
)

add_custom_target(clean-all
   COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
   COMMENT "Cleaning all build files"
)

add_executable(bhesh ${SOURCES})