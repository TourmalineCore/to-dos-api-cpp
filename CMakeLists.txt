cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/data/models/odb-gen/*.cxx
)
list(REMOVE_ITEM sources ${CMAKE_SOURCE_DIR}/src/main.cpp)

set(LIB_TARGET ${PROJECT_NAME}_lib)

add_library(${LIB_TARGET} OBJECT ${sources})

target_include_directories(${LIB_TARGET} PUBLIC
  ${CMAKE_SOURCE_DIR}/src
  /usr/include
  src/data/models/
)

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)

target_link_libraries(${LIB_TARGET} PUBLIC 
  Drogon::Drogon
  JsonCpp::JsonCpp
  odb odb-pgsql
)

add_executable(${PROJECT_NAME} 
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  $<TARGET_OBJECTS:${LIB_TARGET}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  ${LIB_TARGET}
)

if("$ENV{SKIPTESTS}" STREQUAL "TRUE")
    message(STATUS "UNIT TESTS DISABLED")
else()
    message(STATUS "UNIT TESTS ENABLED")
    enable_testing()
    add_subdirectory(test)
endif()
