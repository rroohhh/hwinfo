#include "config.h"
#include "log.h"
#include "component.h"
#include "device_method.h"
#include "util.h"
#include "capatibility.h"
#include "nodes.h"
#include "aggregator.h"

#include <type_traits>

int main(int argc, char ** argv) {
    // Logger::info() << "batteries: " <<
    // std::vector<std::string>(battery_nodes) << std::endl;

    for(const auto & node : Nodes::nodes) {
        Logger::info() << node.first << ": " << node.second.capatibilities
                       << std::endl;
        for(const auto & method : node.second.capatibilities) {
            Logger::info() << "\t" << method << ": "
                           << Aggregator::aggregate(node.first, method,
                                                    node.second.components)
                           << std::endl;
            for(const auto & component : node.second.components) {
                Logger::info() << "\t\t" << component->read(method)
                               << std::endl;
            }
        }
    }

    Logger::info() << "aggregation: " << std::endl;
    for(const auto & component : Aggregator::aggregators) {
        Logger::info() << component.first << std::endl;
        for(const auto & method : component.second) {
            Logger::info() << method.first << ": "
                           << Aggregator::aggregate(
                                  component.first, method.first,
                                  Nodes::nodes.at(component.first).components)
                           << std::endl;
        }
    }
}
