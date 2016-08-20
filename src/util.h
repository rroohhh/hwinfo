/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  util.h -- misc util functions
*/

#ifndef _UTIL_H
#define _UTIL_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
std::ostream & operator<<(std::ostream & out, const std::vector<T> & v) {
    if(!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

bool is_number(const std::string & s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) {
                             return !std::isdigit(c);
                         }) == s.end();
}

template <typename T, typename U, typename size_type>
std::vector<T> from_arr(U * arr, size_type len) {
    std::vector<T> vector;
    vector.assign(arr, arr + len);
    return vector;
}

#endif
