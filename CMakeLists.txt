cmake_minimum_required(VERSION 3.15)
project(to-dos-api CXX)

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(libodb REQUIRED)
find_package(libodb-pgsql REQUIRED)

add_subdirectory(src/core)
add_subdirectory(src/application)
add_subdirectory(src/api)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        api
        Drogon::Drogon
)

enable_testing()
add_subdirectory(test)