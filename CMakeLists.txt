cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "to-dos-api")
project(${PROJECT_NAME} CXX)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/odb")
# file(GLOB_RECURSE MODEL_HDRS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/data/models/*.h)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
# include(${CMAKE_SOURCE_DIR}/deps/odb/UseODB.cmake)


# find_package(PostgreSQL REQUIRED)
# find_library(ODB_PGSQL_LIB odb-pgsql REQUIRED)
# find_library(ODB_LIB odb REQUIRED)
# find_package(ODB REQUIRED COMPONENTS pgsql)
# include(${ODB_USE_FILE})

# odb_compile(sources FILES ${MODEL_HDRS} DB pgsql GENERATE_QUERY GENERATE_SCHEMA GENERATE_SESSION SCHEMA_FORMAT embedded
#   GENERATE_PREPARED
# )

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  # ${CMAKE_SOURCE_DIR}/src/data/models
  # ${ODB_INCLUDE_DIRS}
  # ${ODB_COMPILE_OUTPUT_DIR}
)

# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/tinyorm/TinyORM/TinyORM-builds-cmake/build-debug")
# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/tinyorm/TinyORM")

# list(APPEND CMAKE_PREFIX_PATH "/root/Code/c/tmp/TinyORM")

# include(FetchContent)
# FetchContent_Declare(TinyOrm
#     GIT_REPOSITORY https://github.com/silverqx/TinyORM.git
#     GIT_TAG        origin/main
#     # GIT_TAG        origin/silverqx-develop
#     # OVERRIDE_FIND_PACKAGE
# )
# set(BUILD_DRIVERS ON)
# set(TOM OFF)
# set(TOM_EXAMPLE ON)
# FetchContent_MakeAvailable(TinyOrm)

# find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
# find_package(TinyOrm 0.38.1 CONFIG REQUIRED)

# target_link_libraries(${PROJECT_NAME}
#     PRIVATE
#         Qt${QT_VERSION_MAJOR}::Core
#         TinyOrm::TinyOrm
# )

# target_compile_definitions(${PROJECT_NAME} PRIVATE DATABASE_PGSQL)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${ODB_PGSQL_LIB} ${ODB_LIB})

# target_link_options(${PROJECT_NAME} PRIVATE 
#     -Wl,--whole-archive 
#     ${ODB_LIBRARIES} 
#     -Wl,--no-whole-archive
# )
# message(STATUS "Files: ${sources}")
find_package(Drogon REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)

# target_sources(${PROJECT_NAME} PRIVATE ${ODB_INCLUDE_DIRS} ${ODB_GENERATED_SOURCES})


# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/odb")
# find_package(ODB REQUIRED COMPONENTS pgsql)
# include(${ODB_USE_FILE})

# include_directories(${CMAKE_SOURCE_DIR}/src)
# file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
# # list(FILTER sources EXCLUDE REGEX "/odb_gen/")
# file(GLOB_RECURSE MODEL_HDRS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/data/models/*.h)

# odb_compile(ODB_GEN_FILES
#         FILES ${MODEL_HDRS}
#         DB pgsql
#         SCHEMA_NAME test
#         GENERATE_SCHEMA
#         ) 

# add_executable(${PROJECT_NAME} ${sources} ${ODB_GEN_FILES} ${MODEL_HDRS})

# target_include_directories(${PROJECT_NAME} PRIVATE
#   ${CMAKE_SOURCE_DIR}/src
#   ${CMAKE_SOURCE_DIR}/src/data/models
#   ${ODB_COMPILE_OUTPUT_DIR}
# )

# find_package(PostgreSQL REQUIRED)
# target_sources(${PROJECT_NAME} PRIVATE ${ODB_GEN_FILES} ${MODEL_HDRS})
# # target_sources(${PROJECT_NAME} PRIVATE ${ODB_GEN_FILES})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${ODB_LIBRARIES} PostgreSQL::PostgreSQL)
# target_compile_definitions(${PROJECT_NAME} PRIVATE DATABASE_PGSQL)