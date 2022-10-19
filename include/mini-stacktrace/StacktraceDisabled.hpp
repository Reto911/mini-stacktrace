//
// Created by Shiroan on 2022/10/19.
//

#ifndef MINI_STACKTRACE_STACKTRACEDISABLED_H
#define MINI_STACKTRACE_STACKTRACEDISABLED_H

#include <ostream>

namespace mini_stacktrace {
    class StacktraceDisabled {
    public:
        friend std::ostream &operator<<(std::ostream &os, const StacktraceDisabled &disabled);

        explicit StacktraceDisabled(const int=0, const int=0) {}
    };

    std::ostream &operator<<(std::ostream &os, const StacktraceDisabled &disabled) {
        return os;
    }
}

#endif //MINI_STACKTRACE_STACKTRACEDISABLED_H
