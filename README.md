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

Let's say we want to use abseil's logging functions[^acthually] instead of `std::cout` in our project.
[^acthually]: wellll, [not to be pedantic](https://i.redd.it/1ef5ylxhmvx71.jpg), achtually they're logging macros if I may say 
then we can link the `absl::log` library to our target as well:
```cmake
target_link_libraries(lib_as_subdirectory absl::log)
```
Usually you'd want to initialize the logging system (?) before using it;
and as it would be most expected and totally sensible; absl:InitializeLog function
is not included in the `absl::log` library, you need to link
the `absl::log_init` library to your target as well:
```cmake
target_link_libraries(lib_as_subdirectory absl::log_init)
```

Bonus: you don't need to link each library in a separate command, you can link them all in a single command:
```cmake
target_link_libraries(lib_as_subdirectory absl::strings absl::log absl::log_init)
```

## Juicy Part why did we add abseil-cpp as a subdirectory?
Yeah, why did we bother to add abseil-cpp as a subdirectory in our project 
instead of using it as a system library or some other simpler way?

First of all, it wouldn't be simpler as it sucks to use system libraries in CMake projects,
especially when there are multiple versions of the same library installed on the system.
This might be a skill issue on my part, but for the moment I won't bother dealing with it.

The actual reason is that we may want to make changes to the abseil-cpp library,
it can be potential contribution to upstream, or just a custom tweaks for our projects.

Remember that we were using the absl::StrCat function in our project?
Let's say you are some kind of wannabe funny guy, and you want that function 
to concat the strings in reverse order, so that your colleagues can enjoy
debugging a weird 05:00 AM on-call issue. 
If you be a nice kid, one day you can even see yourself be that person!

Withour further ado, let's make the change to the absl::StrCat function!
First, we need to find the implementation of the function
`Command-click` the function name in your IDE, easy-peasy.
If you're using some AI powered super fancy text editor, 
and it doesn't support actually useful features like "go to definition"
here is the path to the file: [absl/strings/str_cat.cc](https://github.com/abseil/abseil-cpp/blob/master/absl/strings/str_cat.cc#L80)

Second, notice that the function is [overloaded](https://en.wikipedia.org/wiki/Function_overloading).
Aren't you lucky! Now the function will malfunction[^pun] only sometimes! 
[^pun]: pun was not intended, but if you'd laughed it, obviously it was intended.
It will drive your colleagues crazy excited as they debug it one day!
We used the StrCat function with three string arguments,
the corresponding overload contained:
```cpp
  out = Append(out, a);
  out = Append(out, b);
  out = Append(out, c);
```
So, we can change it to:
```cpp
  out = Append(out, c);
  out = Append(out, b);
  out = Append(out, a);
```
Recompile the project and see the magic happen!
following
```cpp
absl::StrCat(" first ", " second ");
absl::StrCat(" first ", " second ", " third ");
absl::StrCat(" first ", " second ", " third ", " fourth ");
```
functions returns the following strings:
```
" first  second "
" third  second  first "
" first  second  third  fourth "
```
Only the overload with three arguments is affected, as expected!

In order to save changes to the git you need to commit the changes to the abseil-cpp submodule:
```shell
cd abseil-cpp
git add .
git commit -m "Totally innocent change, nothing to see here"
git push
cd ..
```
We made the changes to the submodule, but now we want our main project to point to the new commit of the submodule.
```shell
git add abseil-cpp
git commit -m "updated abseil-cpp submodule to the latest commit"
git push
```
(or use your favorite git GUI client like any sane person would have done)
