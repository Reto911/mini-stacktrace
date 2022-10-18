# Mini-Stacktrace
A lightweight, (maybe) cross-platform stacktrace library.

The library supports:
* Linux
* Windows

# Getting Started
Mini-Stacktrace is a header-only library,
so that you can copy the directory `include/mini-stacktrace` to anywhere you want,
and include header `mini-stacktrace` from the directory in your codes.

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

## For Windows Users
Because this library uses DbgHelp, the library will work properly with MSVC, but Mingw.

If you want to use the library with Mingw, you must use [cv2pdb](https://github.com/rainers/cv2pdb) to generate a PDB file.
