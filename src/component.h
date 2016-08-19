#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "capatibility.h"
#include "device_method.h"
#include <unordered_map>
#include <vector>

template <typename T>
class CapatibilityProvider {
public:
    static std::vector<Capatibility> getCapatibilities() {
        return T::getCapatibilities();
    }
};

#define DECLARE_COMPONENT(name, ...)                                           \
    class name : public Component, public CapatibilityProvider<name> {         \
    public:                                                                    \
        name(DeviceNode device_node) : Component(device_node) {                \
            this->device_node = device_node;                                   \
            add_methods({__VA_ARGS__});                                        \
        }                                                                      \
                                                                               \
        static std::vector<Capatibility> getCapatibilities() {                 \
            return Capatibility::from_strings({__VA_ARGS__});                  \
        }                                                                      \
    };                                                                         \
    DECLARE_DEFAULT_AGGREGATION(name, average, __VA_ARGS__)

class Component {
public:
    std::string read(std::string method) const {
        try {
            return methods.at(method)->read();
        } catch(const std::out_of_range & oor) {
            std::cerr << "No method named " << method << " for " << device_node
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    int write(std::string method, std::string value) {
        try {
            return methods.at(method)->write(value);
        } catch(const std::out_of_range & oor) {
            std::cerr << "No method named " << method << " for " << device_node
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    DeviceNode device_node;

protected:
    Component(DeviceNode device_node) : device_node(device_node) {}

    void add_method(std::string name) {
        methods[name] = new DeviceMethod(device_node, name);
    }

    void add_methods(std::vector<std::string> methods) {
        for(auto const & method : methods) { add_method(method); }
    }

    std::vector<Capatibility> capatibilities;

    std::unordered_map<std::string, DeviceMethod *> methods;
};

#endif
