# Generate static library for linking with main executable
add_library(${CORE_LIB} INTERFACE)

# Provide to library includes
target_include_directories(${CORE_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Linking only interfaces of dependencies, bc core layer store only interfaces of models
target_link_libraries(${CORE_LIB}
    INTERFACE libodb::libodb
)