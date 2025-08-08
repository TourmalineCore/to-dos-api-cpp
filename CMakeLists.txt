cmake_minimum_required(VERSION 3.15)
project(to-dos-api CXX)



add_executable(to-dos-api src/to-dos-api.cpp src/main.cpp)



install(TARGETS to-dos-api DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
