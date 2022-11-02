//
// Created by shiroan on 22-10-18.
//

#ifndef MINI_STACKTRACE_STACKTRACEWINDOWS_HPP
#define MINI_STACKTRACE_STACKTRACEWINDOWS_HPP

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
#include <windows.h>
#include <dbghelp.h>
#include <ostream>

namespace mini_stacktrace {
#ifndef _MSC_VER
    inline bool gen_pdb() {
        CHAR path[MAX_PATH] = {0};
        CHAR name[MAX_PATH]  = {0};
        CHAR buf[MAX_PATH * 2 + 10] = {0};

        DWORD len= GetModuleFileName(nullptr, path, 1024);
        if (len == 0) {
            return false;
        }
        PCHAR programName = path;

        for (PCHAR i = programName; *i != 0; i++) {  // find the programName.
            if (*i == '/' || *i == '\\') {
                programName = i;
            }
        }
        programName++;
        strcpy(name, programName);
        len -= (programName - path);  // get length of name

        strcpy(name + len - 3, "pdb");  // replace *.exe with *.pdb

        sprintf(buf, "cv2pdb %s nul %s", path, name);
        system(buf);
        return true;
    }
#endif

    class StacktraceWindows {
        HANDLE hProcess;
        const int size, skip;
        std::string result = "Stacktrace:\n";

        void init_sym() {
            SymInitialize(hProcess, nullptr, TRUE);
        }

        void stack_trace() {
            void** frames = new void*[size]{nullptr};
            char buf[MAX_SYM_NAME * 2];
            WORD count = RtlCaptureStackBackTrace(2 + skip, size, frames, nullptr);

            DWORD64 symDisplament  = 0;
            DWORD   lineDisplament = 0;

            char symbolBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(WCHAR)]{0};
            auto pSym = (PSYMBOL_INFO) symbolBuffer;
            pSym->SizeOfStruct = sizeof(SYMBOL_INFO);
            pSym->MaxNameLen = MAX_SYM_NAME;
            IMAGEHLP_LINE imageLine;
            ZeroMemory(&imageLine, sizeof(imageLine));
            imageLine.SizeOfStruct = sizeof(IMAGEHLP_LINE);

            for (WORD i = 0; i < count; i++) {
                ULONG64 address    = 0;
                PCSTR   name       = "??";
                PCSTR   fileName   = "??";
                DWORD   lineNumber = 0;

                if (SymFromAddr(hProcess, (DWORD64)frames[i], &symDisplament, pSym)) {
                    address = pSym->Address;
                    name    = pSym->Name;
                }
                if (SymGetLineFromAddr(hProcess, (DWORD64)frames[i], &lineDisplament, &imageLine)) {
                    fileName   = imageLine.FileName;
                    lineNumber = imageLine.LineNumber;
                }
                sprintf(buf, "\t[%02d] %016llx+%s(FILE[%s]LINE[%lu])\n", i, address, name, fileName, lineNumber);
                result.append(buf);
            }

            delete[] frames;
        }

        void clean_up() {
            SymCleanup(hProcess);
        }
    public:
        explicit StacktraceWindows(const int skip=0, const int size=100)
        : hProcess(GetCurrentProcess()), size(size), skip(skip) {
#ifndef _MSC_VER
            gen_pdb();
#endif
            init_sym();
            stack_trace();
            clean_up();
        }

        friend std::ostream &operator<<(std::ostream &os, const StacktraceWindows &trace);
    };

    std::ostream &operator<<(std::ostream &os, const StacktraceWindows &trace) {
        return os << trace.result;
    }
}
#else
static_assert(false, "Should not include this header.");
#endif
#endif //MINI_STACKTRACE_STACKTRACEWINDOWS_HPP
