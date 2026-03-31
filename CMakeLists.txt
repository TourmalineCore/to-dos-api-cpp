cmake_minimum_required(VERSION 3.15)
project(to-dos-api CXX)

# Make dependencies are visible for whole project
find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(libodb REQUIRED)
find_package(libodb-pgsql REQUIRED)

set(API_LIB         api)
set(APPLICATION_LIB application)
set(CORE_LIB        core)

# Add a subdirectory where placed cmakefiles of leveles
add_subdirectory(src/core)
add_subdirectory(src/application)
add_subdirectory(src/api)

# Making a list of source files only on high level of src folder (main.cpp and app-config.cpp)
file(GLOB main_sources
${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${main_sources})

target_include_directories(${PROJECT_NAME} PRIVATE
src/
)

target_link_libraries(${PROJECT_NAME}
    # Links API level with parameters for linking of whole dependencies of API level (see https://stackoverflow.com/a/842770)
    PRIVATE -Wl,--whole-archive ${API_LIB} -Wl,--no-whole-archive
)

# Tests
if (ENV{EXCLUDE_UNIT_TESTS_FROM_BUILD} STREQUAL "true")
  # Disable test here needed for uncompatible builds, bc `enable_testing` is run executable tests file for collecting tests.
  # E.g. if executable tests are builded for another OS or CPU arch. 
  message(STATUS "UNIT TEST DISABLED")
else()
  message(STATUS "UNIT TEST ENABLED")
  enable_testing()
  add_subdirectory(test)
endif()
