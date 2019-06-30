#ifndef _CAPATIBILITY_H
#define _CAPATIBILITY_H

#include <iostream>
#include <string>
#include <vector>

class Capatibility {
public:
    std::string identifier;

    operator std::string() const { return identifier; }

    static std::vector<Capatibility>
    from_strings(std::vector<std::string> strings) {
        std::vector<Capatibility> ret;

        for(const auto & string : strings) ret.push_back({string});

        return ret;
    }
};

std::ostream & operator<<(std::ostream & out, const Capatibility & c) {
    out << c.identifier;
    return out;
}

#endif
