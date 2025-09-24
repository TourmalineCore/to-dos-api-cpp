cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
  ${CMAKE_SOURCE_DIR}/src/*/*.cpp
  ${CMAKE_SOURCE_DIR}/src/data/models/odb-gen/*.cxx
)

set(PROJECT_OBJECTS ${PROJECT_NAME}_lib)

add_library(${PROJECT_OBJECTS} OBJECT ${sources})

target_include_directories(${PROJECT_OBJECTS} PUBLIC
  ${CMAKE_SOURCE_DIR}/src
  /usr/include
  src/data/models/
)

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)

target_link_libraries(${PROJECT_OBJECTS} PUBLIC 
  Drogon::Drogon
  JsonCpp::JsonCpp
  odb odb-pgsql
)

add_executable(${PROJECT_NAME} 
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  $<TARGET_OBJECTS:${PROJECT_OBJECTS}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  ${PROJECT_OBJECTS}
)

add_subdirectory(test)
