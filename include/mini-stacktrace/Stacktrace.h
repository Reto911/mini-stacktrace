//
// Created by shiroan on 22-10-18.
//

#ifndef MINI_STACKTRACE_STACKTRACE_H
#define MINI_STACKTRACE_STACKTRACE_H

namespace mini_stacktrace {
template<typename ST>
concept IsStacktrace = requires (ST trace, int size, int skip, std::ostream& os) {
    ST(skip, size);
    os << trace;
};
}

#ifdef __linux__
#include "StacktraceLinux.hpp"

namespace mini_stacktrace {
    using Stacktrace = StacktraceLinux;

    static_assert(IsStacktrace<Stacktrace>);
}

#elif defined(__WIN32__)

#include "StacktraceWindows.hpp"

namespace mini_stacktrace {
    using Stacktrace = StacktraceWindows;

    static_assert(IsStacktrace<Stacktrace>);
}

#endif // __linux__

#endif //MINI_STACKTRACE_STACKTRACE_H
