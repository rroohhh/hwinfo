/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  args.h -- Parse the user specified arguments
*/

#ifndef _ARGS_H
#define _ARGS_H

#include "aggregator.h"
#include "complete.h"
#include "nodes.h"
#include "util.h"
#include <iostream>
#include <string>
#include <vector>

void dump_component(const Component & component,
                    const std::vector<Capatibility> & capatibilities,
                    const std::string prefix = "") {
    for(const auto & method : capatibilities) {
        std::cout << prefix << method << " " << component.read(method)
                  << std::endl;
    }
}

void dump_node(const ComponentArray & node, const std::string prefix1 = "",
               const std::string prefix2 = "") {
    int i = 0;

    for(const auto & component : node.components) {
        std::cout << prefix1 << i++ << std::endl;
        dump_component(*component, node.capatibilities, prefix2);
    }
}

void dump_nodes() {
    for(const auto & node : Nodes::nodes) {
        std::cout << node.first << std::endl;
        dump_node(node.second, "\t", "\t\t");
    }
}

void parse_args(const std::vector<std::string> & arguments) {
    std::vector<std::string> args(arguments.begin() + 1, arguments.end());

    // no node specified -> dump all of them
    if(args.size() == 0) {
        dump_nodes();
    } else {
        if(args.at(0) == "--complete") {
            complete(std::vector<std::string>(args.begin() + 1, args.end()));
        } else {

            // get the node
            auto node = Nodes::nodes.find(args.at(0));
            if(node == Nodes::nodes.end()) {
                std::cerr << "node " << args.at(0) << " not found" << std::endl;
            } else if(args.size() == 1) {
                dump_node(node->second, "", "\t");
            } else {
                try {
                    unsigned int index = std::stoi(args.at(1));

                    if(node->second.components.size() > index) {
                        if(args.size() == 2) {
                            dump_component(*node->second.components.at(index),
                                           node->second.capatibilities);
                        } else {
                            if(args.size() == 3) {
                                std::cout
                                    << node->second.components.at(index)->read(
                                        args.at(2));
                            } else {
                                node->second.components.at(index)->write(
                                    args.at(2), args.at(3));
                            }
                        }
                    } else {
                        std::cerr << "no component at index " << index << " of "
                                  << node->first << std::endl;
                    }
                } catch(...) {
                    // std::cout << "hello" << std::endl,
                    if(node->second.components.size() > 1) {
                        std::cout
                            << Aggregator::aggregate(node->first, args.at(1),
                                                     node->second.components)
                            << std::endl;
                    } else if(args.size() == 2) {
                        std::cout
                            << node->second.components.at(0)->read(args.at(1));
                    } else {
                        node->second.components.at(0)->write(args.at(1),
                                                             args.at(2));
                    }
                }
            }
        }
    }
}

#endif
