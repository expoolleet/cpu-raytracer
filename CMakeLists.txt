cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(Project raytracer)

project(${Project})

set(SRC_DIR
  src/program.cpp
)

add_executable(${Project}
  ${SRC_DIR}
)

target_include_directories(${Project} PRIVATE
  ${INCLUDE_DIR}
)
