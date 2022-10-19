# Mini-Stacktrace
A lightweight, (maybe) cross-platform stacktrace library.

The library supports:
* Linux
* Windows

# Getting Started
## Install the Library Directly
Mini-Stacktrace is a header-only library,
so that you can simply copy the directory `include/mini-stacktrace` to anywhere you want,
and include header `mini-stacktrace` from the directory in your codes.

In this way, you should handle the compiler options and linker options yourself.

## Install the Library with Cmake
It's recommended to install and use the library with Cmake.

```shell
git clone https://github.com/Reto911/mini-stacktrace.git
cd mini-stacktrace
git checkout main
md build
cd build
cmake ..
cmake --build . --config Release --target install
```

Then you can include the library in your projects.
```cmake
find_package(mini_stacktrace REQUIRED)
add_executable(main src/main.cpp)
target_link_libraries(main mini_stacktrace::mini_stacktrace)
```

## Use the Library
Mini-Stacktrace is such a very simple library,
that it just exposes one class `Stacktrace` as the only interface,
and what you need only to do (and can only do) is to construct an instance of `Stacktrace` (which will capture the backtrace immediately)
and make it output to a stream.

```c++
#include <iostream>
#include <mini-stacktrace/mini-stacktrace>

int main() {
    std::cout << mini_stacktrace::Stacktrace() << std::endl;

    return 0;
}
```

If you want to disable the stacktrace, just define a mrcro `MINI_STACKTRACE_DISABLED` before you include the header.

```c++
#define MINI_STACKTRACE_DISABLED
#include <iostream>
#include <mini-stacktrace/mini-stacktrace>

int main() {
    std::cout << mini_stacktrace::Stacktrace() << std::endl;  // this statement will not do anything

    return 0;
}
```


## For Windows Users
Because this library uses DbgHelp, the library will work properly with MSVC, but not with Mingw.

If you are not using MSVC, make sure that you've installed [cv2pdb](https://github.com/rainers/cv2pdb) in `PATH`.
The library will try to generate a PDB file, which is compatible with DbgHelp, automatically when you are not using MSVC.