#include "args.h"
#include "config.h"

int main(int argc, char ** argv) {
    parse_args(from_arr<std::string>(argv, argc));
}
