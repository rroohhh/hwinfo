/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  algo.h -- some basic algorithms
*/

#ifndef _ALGO_H
#define _ALGO_H

#include <iterator>

namespace algo {
    template <typename T>
    struct void_t {
        typedef void type;
    };

    template <typename T, typename = void>
    struct value_type {};

    template <class T>
    struct value_type<T, typename void_t<typename T::value_type>::type> {
        typedef typename T::value_type type;
    };

    template <class T>
    struct value_type<T, typename void_t<typename std::iterator_traits<T>::value_type>::type> {
        typedef typename T::value_type type;
    };

    template <typename T>
    constexpr auto average(T data) {
        typename value_type<T>::type tmp{};
        unsigned long long count = 0;
        for(auto elem : data) {
            tmp += elem;
            count++;
        }

        tmp /= count;

        return tmp;
    }

    template <typename T>
    constexpr auto sum(T data) {
        typename value_type<T>::type tmp{};
        for(auto elem : data) { tmp += elem; }

        return tmp;
    }
}

#endif
