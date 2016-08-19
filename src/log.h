#ifndef _LOG_H
#define _LOG_H

#include "string_util.h"
#include "time.h"
#include <iostream>

namespace Logger {
    std::ostream * stdout = &std::cout;
    std::ostream * stderr = &std::cerr;

    void setStdout(std::ostream sout) { stdout = &sout; }

    void setStderr(std::ostream serr) { stderr = &serr; }

    std::ostream & log(std::ostream & target, const char * identifier) {
        target << "[" << identifier << "]"
               << "[" << dateString() << "] ";

        return target;
    }

    std::ostream & info() { return log(*stdout, "I"); }

    std::ostream & err() { return log(*stderr, "E"); }

    std::ostream & warn() { return log(*stdout, "W"); }
}

#endif
