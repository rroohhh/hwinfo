/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  complete.h -- Complete the given arguments
*/

#ifndef _COMPLETE_H
#define _COMPLETE_H

#include "nodes.h"
#include "util.h"
#include <iostream>
#include <string>
#include <vector>

void complete_nodes() {
    for(const auto & node : Nodes::nodes) {
        std::cout << node.first << std::endl;
    }
}

void complete_components(std::vector<Component *> components) {
    int i = 0;

    for(const auto & component : components) {
        std::cout << i++ << ":" << component->device_node << std::endl;
    }
}

void complete_capatibilities(std::vector<Capatibility> capatibilities) {
    for(const auto & capatibility : capatibilities) {
        std::cout << capatibility << std::endl;
    }
}

bool should_complete(const ComponentArray & node, const std::string & word) {
    int count   = 0;
    int perfect = -1;

    for(const auto & capatibility : node.capatibilities) {
        if(std::string(capatibility).find(word) == 0) {
            count++;

            if(std::string(capatibility) == word) perfect = 0;
        }
    }

    return count > 1 || perfect == -1;
}

void complete(const std::vector<std::string> & args) {
    int current = std::stoi(args.at(0));

    if(current == 2) {
        complete_nodes();
    } else if(current == 3) {
        auto node = Nodes::nodes.at(args.at(2));

        if(node.components.size() > 1) { complete_components(node.components); }

        complete_capatibilities(node.capatibilities);
    } else if(current == 4) {
        if(is_number(args.at(3))) {
            auto node = Nodes::nodes.at(args.at(2));

            complete_capatibilities(node.capatibilities);
        }
    }

    return;
}

#endif
