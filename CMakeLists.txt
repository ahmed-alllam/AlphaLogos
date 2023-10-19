cmake_minimum_required(VERSION 3.12)
project(AlphaLogos)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


link_directories(/usr/local/lib)

# Set C++ standard (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 11)

# Find all .cpp and .h files in the src directory and its subdirectories
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/**/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES
    "include/*.h"
    "include/**/*.h"
)


option(BUILD_ONLY_TESTS "Build only tests without main application dependencies" OFF)

if(NOT BUILD_ONLY_TESTS)


# Add your source files to the executable
add_executable(AlphaLogos ${SOURCE_FILES} ${HEADER_FILES})




add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/static_updated"  # Dummy output
    BYPRODUCTS "${CMAKE_BINARY_DIR}/static"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/web/static"
        "${CMAKE_BINARY_DIR}/static"
    COMMENT "Copying web/static folder to build directory"
)

add_custom_command(
    OUTPUT "${CMAKE_BINARY_DIR}/templates_updated"  # Dummy output
    BYPRODUCTS "${CMAKE_BINARY_DIR}/templates"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/src/web/templates"
        "${CMAKE_BINARY_DIR}/templates"
    COMMENT "Copying web/templates folder to build directory"
)




add_custom_target(
    copy_web_content ALL
    DEPENDS "${CMAKE_BINARY_DIR}/static_updated" "${CMAKE_BINARY_DIR}/templates_updated"
)




# If your project generates an executable, make it depend on the custom target
add_dependencies(AlphaLogos copy_web_content)







# Specify include directories for header files
target_include_directories(AlphaLogos PRIVATE include)




# Additional libraries or dependencies (if needed)
find_package(Boost)
target_link_libraries(AlphaLogos ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(AlphaLogos PUBLIC Boost)


find_package(Crow)
target_link_libraries(AlphaLogos PUBLIC Crow::Crow)


target_link_libraries(AlphaLogos PUBLIC Jinja2CppLight)






# Specify any compiler-specific options or flags
# target_compile_options(AlphaLogos PRIVATE -Wall -Wextra)

# Specify the output binary name (optional)
# set_target_properties(AlphaLogos PROPERTIES OUTPUT_NAME my_program)



endif()



include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1  # Use the version you want
)

FetchContent_MakeAvailable(Catch2)


# Create the test target
file(GLOB_RECURSE TEST_SOURCES
    "tests/*.cpp"
    "src/logic_utils/*.cpp"  # Include source files from src directory in tests
    "src/qm/*.cpp"
)


add_executable(AlphaLogosTests ${TEST_SOURCES})


# Link the test target with Catch2
target_link_libraries(AlphaLogosTests PRIVATE Catch2::Catch2WithMain)

# Specify the output binary name for the test target (optional)
set_target_properties(AlphaLogosTests PROPERTIES OUTPUT_NAME AlphaLogosTests)

# Configure CTest to run the tests
include(Catch)
catch_discover_tests(AlphaLogosTests)

# Optionally, you can create a custom target to run the tests
add_custom_target(run_tests
    COMMAND AlphaLogosTests
    DEPENDS AlphaLogosTests
)
