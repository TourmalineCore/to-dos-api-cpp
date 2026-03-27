add_library(${CORE_LIB} INTERFACE)
target_include_directories(${CORE_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${CORE_LIB}
    INTERFACE libodb::libodb
)