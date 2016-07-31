#include "config.h"
#include "log.h"
#include "component.h"
#include "device_method.h"
#include "util.h"
#include "capatibility.h"
#include "nodes.h"

int main(int argc, char ** argv) {
    // Logger::info() << "batteries: " <<
    // std::vector<std::string>(battery_nodes) << std::endl;

    for(const auto & node : Nodes::nodes) {
        Logger::info() << node.first << ": " << node.second.first << std::endl;

        for(const auto & method : node.second.first) {
            Logger::info() << "\t" << method << ": " << std::endl;
            for(const auto & component : node.second.second) {
                Logger::info() << "\t\t" << component->read(method);
            }
        }
    }
}
