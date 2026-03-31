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

file(GLOB main_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${main_sources})

target_include_directories(${PROJECT_NAME} PRIVATE
    src/
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE -Wl,--whole-archive ${API_LIB} -Wl,--no-whole-archive
)

# Tests
if (ENV{EXCLUDE_UNIT_TESTS_FROM_BUILD} STREQUAL "true")
  message(STATUS "UNIT TEST DISABLED")
else()
  message(STATUS "UNIT TEST ENABLED")
  enable_testing()
  add_subdirectory(test)
endif()
