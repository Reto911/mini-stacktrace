#include <iostream>
#include <mini-stacktrace/StacktraceLinux.h>

int main() {
    std::cout << mini_stacktrace::StacktraceLinux(100) << std::endl;

    return 0;
}
