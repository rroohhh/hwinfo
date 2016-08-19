#include "args.h"
#include "config.h"

//ToDo(robin): cleaup complete.h a bit
//ToDo(robin): find out if the double completion bug can be fixed (hwinfo battery energy_full <TAB>)

int main(int argc, char ** argv) {
    // std::cout << "b" << from_arr<std::string>(argv, argc) << std::endl;
    parse_args(from_arr<std::string>(argv, argc));
}
