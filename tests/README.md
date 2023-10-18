# Unit Testing in C++ with Catch2

This guide will walk you through the process of adding unit tests to the project using the Catch2 testing framework. We'll use a simple `add` function as an example.

## 1. Creating the `add` Function

First, we need a C++ function to test. Let's create a file named `add.h` in the `src` directory (or any of its subdirectories) with the following content:

```cpp
#ifndef ADD_H
#define ADD_H

int add(int a, int b);

#endif
```

And the corresponding `add.cpp` file:

```cpp
#include "add.h"

int add(int a, int b) {
    return a + b;
}
```

## 2. Setting up Catch2 Unit Tests

Now, let's create a new test file in the `tests` folder of the project, named `test_add.cpp`. Here's the content of the test file:

```cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "../src/add.h"   // Adjust the path accordingly 

TEST_CASE("Addition of 1 and 2") {
    REQUIRE( add(1, 2) == 3 );
}

TEST_CASE("Addition of 5 and 3") {
    REQUIRE( add(5, 3) == 8);
}
```

## 3. Building and Running the Tests

Navigate to the project folder and create a `build` directory if it does not already exist. Then run the following commands to build and execute the tests:

```sh
mkdir build  # Create the build directory
cd build     # Navigate into the build directory
cmake .. -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=.. -DBUILD_ONLY_TESTS=ON   # Generate Makefile for tests only
make         # Compile the project
./AlphaLogosTests  # Run the tests
```

You should see the test results printed to the console, indicating whether each test passed or failed.

## Conclusion

That's it! You have now added Catch2 unit tests to our project! Always adjust the test cases in the test file to cover more scenarios (more code coverage) and ensure the robustness of your code.
