cmake_minimum_required(VERSION 3.31)
project(lib_as_subdirectory)

set(CMAKE_CXX_STANDARD 20)

add_executable(lib_as_subdirectory main.cpp)

add_subdirectory(abseil-cpp)

target_link_libraries(lib_as_subdirectory absl::strings absl::log absl::log_initialize)