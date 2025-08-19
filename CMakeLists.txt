cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)

include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.c src/*.cc src/*.cpp src/*.hpp src/*.h)

add_executable(${PROJECT_NAME} ${sources})

find_package(Drogon REQUIRED)
target_link_libraries(${PROJECT_NAME} Drogon::Drogon)

install(TARGETS to-dos-api DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
