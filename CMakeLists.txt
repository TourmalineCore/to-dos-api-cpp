cmake_minimum_required(VERSION 3.15)
project(to-dos-api CXX)


add_executable(to-dos-api src/to-dos-api.cpp src/main.cpp src/auth/Authorization/Authorization.cpp src/lib/RouterInterceptor/RouterInterceptor.cpp)


find_package(oatpp REQUIRED)
target_link_libraries(to-dos-api oatpp::oatpp)


install(TARGETS to-dos-api DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
