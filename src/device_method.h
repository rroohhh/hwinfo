#ifndef _DEVICE_METHOD_H
#define _DEVICE_METHOD_H

#include "device_node.h"
#include <functional>
#include <string>
#include <exception>

class DeviceMethod {
public:
    DeviceMethod(DeviceNode node, std::string path)
        : read_value(std::bind(&DeviceNode::read, node, path)),
          write_value(std::bind(&DeviceNode::write, node, path,
                                std::placeholders::_1)) {}

	std::string read() { return {read_value()}; }

    int write(std::string value) { return write_value({value}); }

private:
    std::function<std::string(void)> read_value;
    std::function<int(std::string)> write_value;
};

#endif
