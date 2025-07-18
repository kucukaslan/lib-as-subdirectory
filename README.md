# Reproducing the project step by step



## Init git submodules and add abseil https://github.com/abseil/abseil-cpp

```bash
git submodule update --init --recursive
git submodule add https://github.com/abseil/abseil-cpp
#git submodule update --remote abseil-cpp
```

## Add abseil to CMakeLists.txt

```cmake
add_subdirectory(abseil-cpp)
target_link_libraries(my-project-exe PRIVATE absl::strings)
target_include_directories(my-project-exe PRIVATE absl::strings)
```