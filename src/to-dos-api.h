#pragma once

#include <string>
#include <vector>


#ifdef _WIN32
#define TO_DOS_API_EXPORT __declspec(dllexport)
#else
#define TO_DOS_API_EXPORT
#endif

TO_DOS_API_EXPORT void to_dos_api();
TO_DOS_API_EXPORT void to_dos_api_print_vector(const std::vector<std::string>& strings);
