#ifndef _DEVICE_NODE_H
#define _DEVICE_NODE_H

#include <string>
#include <fstream>
#include <ostream>
#include "log.h"

class InvalidRead : public std::exception {
public:
    InvalidRead(std::string method) : method(method) {}

    virtual const char * what() const throw() {
        return (std::string("Invalid read on method ") + method).c_str();
    }

private:
    std::string method;
};

class InvalidWrite : public std::exception {
public:
    InvalidWrite(std::string method) : method(method) {}

    virtual const char * what() const throw() {
        return (std::string("Invalid write on method ") + method).c_str();
    }

private:
    std::string method;
};

class DeviceNode {
public:
    DeviceNode(std::string path) {
        if(path.back() != '/')
            this->path = path + '/';
        else
            this->path = path;
    }

    std::string read(std::string method) {
        std::ifstream in;

        try {
            in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            in.open(path + method, std::ios::in | std::ios::binary);

            std::string contents((std::istreambuf_iterator<char>(in)),
                                 std::istreambuf_iterator<char>());
            in.close();
            return trim(contents);

        } catch(...) {
            throw InvalidRead(std::string("invalid read at: ") + path + method);
        }

        return "unreachable code\n";
    }

    int write(std::string method, std::string value) {
        try {
            std::ofstream out;

            out.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            out.open(path + method, std::ios::in | std::ios::binary);

            out.write(value.c_str(), value.size());
            out.close();
            return 0;
        } catch(...) {
            throw InvalidWrite(std::string("invalid write at: ") + path +
                               method);
        }

        return -1;
    }

    friend std::ostream & operator<<(std::ostream & out, const DeviceNode & d);

private:
    std::string path;
};

std::ostream & operator<<(std::ostream & out, const DeviceNode & d) {
    out << d.path;
    return out;
}

#endif
