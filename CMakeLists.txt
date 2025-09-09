cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/data/models/odb-gen/*.cxx
)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE
${CMAKE_SOURCE_DIR}/src
/usr/include
src/data/models/
)

target_link_libraries(${PROJECT_NAME} PRIVATE odb odb-pgsql)