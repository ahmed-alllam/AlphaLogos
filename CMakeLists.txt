cmake_minimum_required(VERSION 3.12)  # Adjust the minimum version as needed
project(AlphaLogos)

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
# find_package(Boost REQUIRED)
# target_link_libraries(AlphaLogos PRIVATE Boost::Boost)

# Specify any compiler-specific options or flags
# target_compile_options(AlphaLogos PRIVATE -Wall -Wextra)

# Specify the output binary name (optional)
# set_target_properties(AlphaLogos PROPERTIES OUTPUT_NAME my_program)

