file(GLOB_RECURSE api_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Generate static library for linking with main executable
add_library(${API_LIB} STATIC ${api_sources})

# Provide to library includes
target_include_directories(${API_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Linking and provide to public only neccessary dependencies
target_link_libraries(${API_LIB}
    PUBLIC  ${APPLICATION_LIB}
            Drogon::Drogon
)