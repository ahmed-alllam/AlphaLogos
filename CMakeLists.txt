cmake_minimum_required(VERSION 3.12)  # Adjust the minimum version as needed
project(AlphaLogos)

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


# Add your source files to the executable
add_executable(AlphaLogos ${SOURCE_FILES} ${HEADER_FILES})

# Specify include directories for header files
target_include_directories(AlphaLogos PRIVATE include)




# Additional libraries or dependencies (if needed)
find_package(Boost REQUIRED)
target_link_libraries(AlphaLogos ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(AlphaLogos PUBLIC Boost)


find_package(Crow)
target_link_libraries(AlphaLogos PUBLIC Crow::Crow)


target_link_libraries(AlphaLogos PUBLIC Jinja2CppLight)






# Specify any compiler-specific options or flags
# target_compile_options(AlphaLogos PRIVATE -Wall -Wextra)

# Specify the output binary name (optional)
# set_target_properties(AlphaLogos PROPERTIES OUTPUT_NAME my_program)



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
    "src/**/*.cpp"  # Include source files from src directory in tests
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
