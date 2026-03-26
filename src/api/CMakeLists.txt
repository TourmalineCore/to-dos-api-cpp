file(GLOB_RECURSE api_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(api STATIC ${api_sources})

target_include_directories(api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(api
    PRIVATE application
            Drogon::Drogon
            JsonCpp::JsonCpp
)