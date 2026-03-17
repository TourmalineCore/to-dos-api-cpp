cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
  ${CMAKE_SOURCE_DIR}/src/*/*.cpp
  ${CMAKE_SOURCE_DIR}/src/data/models/odb-gen/*.cxx
  ${CMAKE_SOURCE_DIR}/src/utils/**/*.cpp
)

set(PROJECT_OBJECTS ${PROJECT_NAME}_lib)

add_library(${PROJECT_OBJECTS} OBJECT ${sources})

file(GLOB_RECURSE database_models
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data/models/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data/models/*.hxx
)

set(database_model_dirs "")
foreach(header ${database_models})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND database_model_dirs ${dir})
endforeach()
list(REMOVE_DUPLICATES database_model_dirs)

target_include_directories(${PROJECT_OBJECTS} PUBLIC
  ${CMAKE_SOURCE_DIR}/src
  /usr/include
  ${database_model_dirs}
)

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(libodb REQUIRED)
find_package(libodb-pgsql REQUIRED)

target_link_libraries(${PROJECT_OBJECTS} PUBLIC 
  Drogon::Drogon
  JsonCpp::JsonCpp
  libodb::libodb
  libodb-pgsql::libodb-pgsql
)

add_executable(${PROJECT_NAME} 
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  $<TARGET_OBJECTS:${PROJECT_OBJECTS}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  ${PROJECT_OBJECTS}
)

# Tests
if (ENV{EXCLUDE_UNIT_TESTS_FROM_BUILD} STREQUAL "true")
  message(STATUS "UNIT TEST DISABLED")
else()
  message(STATUS "UNIT TEST ENABLED")
  enable_testing()
  add_subdirectory(test)
endif()