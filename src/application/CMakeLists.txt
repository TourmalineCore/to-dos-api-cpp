file(GLOB_RECURSE application_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/odb-gen/*.cxx
)

add_library(${APPLICATION_LIB} STATIC ${application_sources})

target_include_directories(${APPLICATION_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/odb-gen
)

target_link_libraries(${APPLICATION_LIB}
    PUBLIC  ${CORE_LIB}
            JsonCpp::JsonCpp
    PRIVATE libodb::libodb
            libodb-pgsql::libodb-pgsql
            Drogon::Drogon
)