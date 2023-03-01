cmake_minimum_required(VERSION 3.16)
project(llvm-pass-inject)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(inject)  # Use your pass name here.
