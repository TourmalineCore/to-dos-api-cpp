include(GoogleTest)

set(TEST_PROJECT ${PROJECT_NAME}_unit_tests)

file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TEST_PROJECT} ${test_sources})

find_package(GTest REQUIRED)

target_link_libraries(${TEST_PROJECT} PRIVATE 
  ${PROJECT_OBJECTS}
  GTest::gtest
)

target_include_directories(${TEST_PROJECT} PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

gtest_discover_tests(${TEST_PROJECT})