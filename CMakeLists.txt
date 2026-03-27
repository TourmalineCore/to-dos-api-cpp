cmake_minimum_required(VERSION 3.15)
project(to-dos-api CXX)

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(libodb REQUIRED)
find_package(libodb-pgsql REQUIRED)

set(API_LIB         api)
set(APPLICATION_LIB application)
set(CORE_LIB        core)

add_subdirectory(src/core)
add_subdirectory(src/application)
add_subdirectory(src/api)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE -Wl,--whole-archive ${API_LIB} -Wl,--no-whole-archive
)

enable_testing()
add_subdirectory(test)