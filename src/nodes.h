/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  nodes.h -- Stores all known nodes and provides access to them
*/

#ifndef _NODES_H
#define _NODES_H

#include <unordered_map>
#include "component.h"
#include "component_array.h"

#define DECLARE_NODES(type, ...)                                               \
    struct __ignore##type {                                                    \
        __ignore##type() { Nodes::addNodes<type>(#type, {__VA_ARGS__}); }      \
    } __ignore_##type;

namespace Nodes {
    std::unordered_map<std::string, ComponentArray> nodes;

    template <typename T>
    void addNode(std::string name, std::string path) {
        nodes[name].capatibilities = T::getCapatibilities();
        nodes[name].components.push_back(new T(path));
    }

    template <typename T>
    int addNodes(std::string name, std::vector<std::string> paths) {
        for(const auto & path : paths) { addNode<T>(name, path); }

        return 0;
    }
}

#endif
