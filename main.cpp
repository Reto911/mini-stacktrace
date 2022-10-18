#include <iostream>
#include <mini-stacktrace/StacktraceLinux.h>

int main() {
    std::cout << mini_stacktrace::StacktraceLinux() << std::endl;

    return 0;
}
