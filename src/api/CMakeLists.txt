file(GLOB_RECURSE api_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(${API_LIB} STATIC ${api_sources})

target_include_directories(${API_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${API_LIB}
    PUBLIC  ${APPLICATION_LIB}
            Drogon::Drogon
)