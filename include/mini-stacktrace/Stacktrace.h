//
// Created by shiroan on 22-10-18.
//

#ifndef MINI_STACKTRACE_STACKTRACE_H
#define MINI_STACKTRACE_STACKTRACE_H

#ifdef __linux__
#include "StacktraceLinux.h"

namespace mini_stacktrace {
    using Stacktrace = StacktraceLinux;
}

#elif defined(__WIN32__)

#include "StacktraceWindows.h"

namespace mini_stacktrace {
    using Stacktrace = StacktraceWindows;
}

#endif // __linux__

#endif //MINI_STACKTRACE_STACKTRACE_H
