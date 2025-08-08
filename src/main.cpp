#include "to-dos-api.h"
#include <vector>
#include <string>

int main() {
    to_dos_api();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    to_dos_api_print_vector(vec);
}
