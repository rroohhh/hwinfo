#ifndef _STRING_UTIL_H
#define _STRING_UTIL_H

#include <algorithm>
#include <functional>
#include <sstream>
#include <string>

static inline std::string & ltrim(std::string & s) {
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

static inline std::string & rtrim(std::string & s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace)))
                .base(),
            s.end());
    return s;
}

static inline std::string & trim(std::string & s) { return ltrim(rtrim(s)); }

std::string & surround_by(std::string & s, std::string & surrounding) {
    s.insert(0, surrounding);
    s.append(surrounding);

    return s;
}

template <typename T>
static inline std::string str(T t) {
    std::ostringstream strs;
    strs << t;
    return strs.str();
}

#endif
