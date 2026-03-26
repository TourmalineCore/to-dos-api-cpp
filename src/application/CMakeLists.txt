file(GLOB_RECURSE application_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/odb-gen/*.cxx
)

add_library(application STATIC ${application_sources})

target_include_directories(application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/odb-gen
)

target_link_libraries(application
    PUBLIC  core
    PRIVATE libodb::libodb
            libodb-pgsql::libodb-pgsql
            JsonCpp::JsonCpp
)