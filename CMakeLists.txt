cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)



add_executable(${PROJECT_NAME} src/to-dos-api.cpp src/main.cpp src/controller/simple-controller.cpp)

find_package(Drogon REQUIRED)
target_link_libraries(${PROJECT_NAME} Drogon::Drogon)


install(TARGETS to-dos-api DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
