cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)


file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
  ${CMAKE_SOURCE_DIR}/src/*/*.cpp
  ${CMAKE_SOURCE_DIR}/src/data/models/odb-gen/*.cxx
)

set(PROJECT_OBJECTS ${PROJECT_NAME}_lib)

add_library(${PROJECT_OBJECTS} OBJECT ${sources})

find_package(Drogon REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(libodb REQUIRED)

find_library(ODB_PGSQL_LIB 
    NAMES odb-pgsql libodb-pgsql
    REQUIRED
)
find_path(ODB_PGSQL_INCLUDE 
    NAMES odb/pgsql/database.hxx
    REQUIRED
)

find_library(LIBPQ       NAMES pq       REQUIRED)
find_library(LIBPGCOMMON NAMES pgcommon REQUIRED)
find_library(LIBPGPORT   NAMES pgport   REQUIRED)

target_include_directories(${PROJECT_OBJECTS} PUBLIC
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/data/models
  ${ODB_PGSQL_INCLUDE}
)

target_link_libraries(${PROJECT_OBJECTS} PUBLIC
  Drogon::Drogon
  JsonCpp::JsonCpp
  ${ODB_PGSQL_LIB}
  libodb::libodb
  ${LIBPQ}
  ${LIBPGCOMMON}
  ${LIBPGPORT}
)


add_executable(${PROJECT_NAME} 
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  $<TARGET_OBJECTS:${PROJECT_OBJECTS}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  ${PROJECT_OBJECTS}
)

# Tests
enable_testing()
add_subdirectory(test)