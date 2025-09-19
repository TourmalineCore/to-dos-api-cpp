include(GoogleTest)

set(TEST_TARGET ${PROJECT_NAME}_unit_tests)

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TEST_TARGET} ${test_sources})

find_package(GTest REQUIRED)

target_link_libraries(${TEST_TARGET} PRIVATE 
  ${LIB_TARGET}
  gtest::gtest
)

target_include_directories(${TEST_TARGET} PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

gtest_discover_tests(${TEST_TARGET})