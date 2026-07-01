# Collect source files
file(GLOB_RECURSE SRC_FILES "*.cpp")

# Remove main.cpp from the core library since we don't want it in the static lib
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/cli/main.cpp")

# Define the core library
add_library(sentinel_core STATIC ${SRC_FILES})

# Link dependencies
target_link_libraries(sentinel_core
    PUBLIC
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        OpenSSL::SSL
        OpenSSL::Crypto
)

# Include directories
target_include_directories(sentinel_core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Define the main executable
add_executable(sentinel cli/main.cpp)
target_link_libraries(sentinel PRIVATE sentinel_core)
