#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "capatibility.h"
#include "device_method.h"
#include <vector>
#include <unordered_map>

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
    };

class Component {
public:
    std::string read(Capatibility c) { return read(c.identifier); }
    std::string read(std::string method) {
        try {
            return methods.at(method)->read();
        } catch(const std::out_of_range & oor) {
            Logger::err() << "No method named " << method << " for "
                          << device_node << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    int write(Capatibility c, std::string value) {
        return write(c.identifier, value);
    }

    int write(std::string method, std::string value) {
        try {
            return methods[method]->write(value);
        } catch(const std::out_of_range & oor) {
            Logger::err() << "No method named " << method << " for "
                          << device_node << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

protected:
    Component(DeviceNode device_node) : device_node(device_node) {}

    void add_method(std::string name) {
        methods[name] = new DeviceMethod(device_node, name);
    }

    void add_methods(std::vector<std::string> methods) {
        for(auto const & method : methods) { add_method(method); }
    }

    DeviceNode device_node;

    std::vector<Capatibility> capatibilities;

    std::unordered_map<std::string, DeviceMethod *> methods;
};

#endif
