# Discover tests
include(GoogleTest)

# Add test executable
add_executable(sentinel_tests
    config_test.cpp
    logger_test.cpp
    core_engine_test.cpp
)

# Link libraries
target_link_libraries(sentinel_tests
    PRIVATE
        sentinel_core
        gtest_main
)

# Include directories
target_include_directories(sentinel_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Register tests
gtest_discover_tests(sentinel_tests)
