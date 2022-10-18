//
// Created by shiroan on 22-10-18.
//

#ifndef MINI_STACKTRACE_STACKTRACE_H
#define MINI_STACKTRACE_STACKTRACE_H

#include <iostream>

#ifdef __linux__
#include "StacktraceLinux.hpp"

namespace mini_stacktrace {
    using Stacktrace = StacktraceLinux;
}

#elif defined(__WIN32__) || defined(_WIN32) || defined(WIN32)

#include "StacktraceWindows.hpp"

namespace mini_stacktrace {
    using Stacktrace = StacktraceWindows;
}

#endif // __linux__

#endif //MINI_STACKTRACE_STACKTRACE_H
