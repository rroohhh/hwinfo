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

void complete(const std::vector<std::string> & args) {
    if(args.size() == 1) {
        complete_nodes();
    } else if(args.size() == 2) {
        try {
            auto node = Nodes::nodes.at(args.at(1));

            if(node.components.size() > 1) {
                complete_components(node.components);
            }

            complete_capatibilities(node.capatibilities);
        } catch(...) { complete_nodes(); }
    } else if(args.size() == 3) {
        auto node = Nodes::nodes.at(args.at(1));

        try {
            std::stoi(args.at(2));
            complete_capatibilities(node.capatibilities);
        } catch(...) {
            int count   = 0;
            int perfect = -1;

            for(const auto & capatibility : node.capatibilities) {
                if(std::string(capatibility).find(args.at(2)) == 0) {
                    count++;

                    if(std::string(capatibility) == args.at(2)) perfect = 0;
                }
            }

            if(count > 1 || perfect == -1) {
                complete_capatibilities(node.capatibilities);
            }
        }
    } else if(args.size() == 4) {
        try {
            std::stoi(args.at(2));
        } catch(...) { return; }

        auto node = Nodes::nodes.at(args.at(1));

        int count   = 0;
        int perfect = -1;

        for(const auto & capatibility : node.capatibilities) {
            if(std::string(capatibility).find(args.at(3)) == 0) {
                count++;

                if(std::string(capatibility) == args.at(3)) perfect = 0;
            }
        }

        if(count > 1 || perfect == -1) {
            complete_capatibilities(node.capatibilities);
        }
    }

    return;
}

#endif
