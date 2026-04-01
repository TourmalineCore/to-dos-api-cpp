file(GLOB_RECURSE application_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/odb-gen/*.cxx
)

# Generate static library for linking with main executable
add_library(${APPLICATION_LIB} STATIC ${application_sources})

# Provide to library includes
target_include_directories(${APPLICATION_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/odb-gen
)

# Linking and provide to public only neccessary dependencies
target_link_libraries(${APPLICATION_LIB}
    PUBLIC  ${CORE_LIB}
            JsonCpp::JsonCpp
    PRIVATE libodb::libodb
            libodb-pgsql::libodb-pgsql
            Drogon::Drogon
)