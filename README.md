# Reproducing the project step by step

## Initialize the single file project
You can use the initial commit of this project:
https://github.com/kucukaslan/lib-as-subdirectory/tree/0e9eaeae61785c7bf0e61929427aa8761f09c99f

## Build and run the project
As usual you can use the following commands to build and run the project:
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./lib_as_subdirectory
```

## Init git submodules and add abseil https://github.com/kucukaslan/abseil-cpp
I forked the original [abseil-cpp](https://github.com/abseil/abseil-cpp) repository,
and added it as a submodule to this project as I wanted to make & commit changes to it.
You can initialize the git submodules and add the abseil-cpp repository as a submodule to your project using the following commands:
```bash
git submodule update --init --recursive
git submodule add https://github.com/kucukaslan/abseil-cpp
#git submodule update --remote abseil-cpp
```
Just change the git submodule URL to the one you want to use, if you want to use the original repo or any other fork.

## Add abseil-cpp as a subdirectory in CMakeLists.txt
You can add the abseil-cpp as a subdirectory in your CMakeLists.txt file to use it in your project.

simply add the following line to the `CMakeLists.txt` file:
```cmake
add_subdirectory(abseil-cpp)
```
As usual you need to link the abseil-cpp libraries to your target as well:
```cmake
target_link_libraries(lib_as_subdirectory absl::strings)
```
As you may have noticed [^shoulda] the `absl::strings` library is linked to the target.
[^shoulda]: if you did not, duh! you should have noticed it!

abseil-cpp has many libraries and you can link any of them to your target as needed.
I linked `absl::strings` since I used [absl::StrCat](https://abseil.io/docs/cpp/guides/strings#abslstrcat-and-abslstrappend-for-string-concatenation).




