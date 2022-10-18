//
// Created by shiroan on 22-10-17.
//

#ifndef MINI_STACKTRACE_STACKTRACELINUX_H
#define MINI_STACKTRACE_STACKTRACELINUX_H

#include <string>
#include <cstdio>
#include <cstdint>
#include <execinfo.h>

#ifdef __linux__
namespace mini_stacktrace {
    class StacktraceLinux {
        std::string result;
        const int size;
        const int skip;
        void stacktrace() {
            char** symbols;
            void** stack = new void*[size]{nullptr};
            char buffer[1024];
            int count = backtrace(stack, size);
            symbols = backtrace_symbols(stack, count);

            for (int j = 2 + skip; j < count; j++) {  // Skip 2 frames: the Constructor and stacktrace().
                sprintf(buffer, "[%02d] 0x%016lx+%s\n", j - 2 - skip, (std::size_t) stack[j], symbols[j]);
                result.append(buffer);
            }

            std::free(symbols);
            delete[] stack;
        }

    public:
        explicit StacktraceLinux(const int skip=0, const int size=100) : size(size), skip(skip) {
            stacktrace();
        }

        friend std::ostream& operator<<(std::ostream& os, const StacktraceLinux& stacktrace);
    };

    std::ostream& operator<<(std::ostream& os, const StacktraceLinux& stacktrace) {
        return os << stacktrace.result;
    }

}
#else
static_assert(false, "Should not include this header.");
#endif  // __linux__

#endif //MINI_STACKTRACE_STACKTRACELINUX_H
