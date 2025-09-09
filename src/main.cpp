#include "to-dos-api.h"
#include <string>
#include <vector>

int main()
{
    to_dos_api();

    std::vector<std::string> vec;
    vec.emplace_back("test_package");

    to_dos_api_print_vector(vec);
}
