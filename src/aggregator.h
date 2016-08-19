/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  aggregator.h -- aggregates the values of multiple components
*/

#ifndef _AGGREGATOR_H
#define _AGGREGATOR_H

#include "algo.h"
#include "component.h"
#include <unordered_map>

#define PASTE_(x, y, z) x##y##z
#define PASTE(x, y, z) PASTE_(x, y, z)

typedef std::function<std::string(std::vector<Component *>)> AggregatorFunction;

#define DECLARE_DEFAULT_AGGREGATION(type, amethod, ...)                        \
    struct __ignoreA##type {                                                   \
        __ignoreA##type() {                                                    \
            Aggregator::addAggregations(                                       \
                #type, {__VA_ARGS__}, Aggregator::AggregationMethod::amethod); \
        }                                                                      \
    } __ignoreAA_##type;

#define DECLARE_AGGREGATION(type, method, amethod)                             \
    struct PASTE(__ignore, __LINE__, type) {                                   \
        PASTE(__ignore, __LINE__, type)() {                                    \
            Aggregator::addAggregation(                                        \
                #type, method, Aggregator::AggregationMethod::amethod);        \
        }                                                                      \
    } PASTE(__ignore, __COUNTER__, type);

namespace Aggregator {
    std::unordered_map<std::string,
                       std::unordered_map<std::string, AggregatorFunction>>
        aggregators;

    std::vector<double> parse_all(std::string method,
                                  std::vector<Component *> components) {
        std::vector<double> values;

        for(const auto & component : components) {
            values.push_back(std::stof(component->read(method)));
        }

        return values;
    }

    enum AggregationMethod { average, sum };

    void addAggregation(std::string component, std::string method,
                        AggregationMethod amethod) {
        AggregatorFunction a;

        switch(amethod) {
        case AggregationMethod::average: {
            a = [=](std::vector<Component *> components) -> std::string {
                if(components.size() == 1)
                    return components.back()->read(method);

                try {
                    return str(algo::average(parse_all(method, components)));
                } catch(...) { return "nan"; }
            };
            break;
        }
        case AggregationMethod::sum: {
            a = [=](std::vector<Component *> components) -> std::string {
                if(components.size() == 1)
                    return components.back()->read(method);

                try {
                    return str(algo::sum(parse_all(method, components)));
                } catch(...) { return "nan"; }
            };
            break;
        }
        }
        aggregators[component][method] = a;
    }

    void addAggregations(std::string component,
                         std::vector<std::string> methods,
                         AggregationMethod amethod) {
        for(const auto & method : methods) {
            addAggregation(component, method, amethod);
        }
    }

    std::string aggregate(std::string component, std::string method,
                          std::vector<Component *> components) {
        return aggregators[component][method](components);
    }
}

#endif
