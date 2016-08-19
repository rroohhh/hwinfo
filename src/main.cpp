#include "config.h"
#include "args.h"

// ToDo(robin): cmd auto completion

int main(int argc, char ** argv) {
    parse_args(from_arr<std::string>(argv, argc));
}
