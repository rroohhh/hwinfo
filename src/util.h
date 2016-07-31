/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  util.h -- misc util functions
*/

#ifndef _UTIL_H
#define _UTIL_H

#include <iostream>
#include <vector>
#include <iterator>

template <typename T>
std::ostream & operator<<(std::ostream & out, const std::vector<T> & v) {
    if(!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

#endif
