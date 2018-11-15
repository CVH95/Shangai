# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project
PROJECT(AI3)
MESSAGE(${PROJECT_NAME} ":")

# Use c++11
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Set build type to release
SET(CMAKE_BUILD_TYPE Release)
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})

# Set .h includes
include_directories(include)

# Output executables into bin/
set(EXECUTABLE_OUTPUT_PATH "../bin")

# Create transfer_function shared library
add_library(transfer_function SHARED src/transfer_function.cpp)

# Create neuron shared library (basis)
add_library(neuron SHARED src/neuron.cpp)

# Create shared libraries
add_library(rk4 SHARED src/rk4.cpp)
add_library(so2_cpg SHARED src/so2_cpg.cpp)
add_library(vrn SHARED src/vrn.cpp)

# Create executables:
add_executable(test_vrn tests/test_vrn.cpp)
target_link_libraries(transfer_function neuron so2_cpg vrn)

# Output end message
MESSAGE(${PROJECT_NAME} " done!")