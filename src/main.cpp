#include "config.h"
#include "args.h"

int main(int argc, char ** argv) {
    // Logger::info() << "batteries: " <<
    // std::vector<std::string>(battery_nodes) << std::endl;

    // auto args = from_arr<std::string>(argv, argc);

    parse_args(from_arr<std::string>(argv, argc));
}
