#include <iostream>
#include <mini-stacktrace/mini-stacktrace>

int main() {
    std::cout << mini_stacktrace::Stacktrace() << std::endl;

    return 0;
}
