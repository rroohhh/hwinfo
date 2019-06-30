#ifndef _HW_TIME_H
#define _HW_TIME_H

#include "string_util.h"
#include <ctime>
#include <string>
#include <sys/types.h>

std::time_t now() { return std::time(0); }
std::string dateString() {
    auto        n = now();
    std::string tmp(std::ctime(&n));
    return trim(tmp);
}

#endif
