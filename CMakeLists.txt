# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

# The name of the project
PROJECT(AI3)
MESSAGE(${PROJECT_NAME} ":")

# Use c++11
set (CMAKE_CXX_STANDARD 11)

# Set build type to release
SET(CMAKE_BUILD_TYPE Release)
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})

# Set .h includes
include_directories( Neuron/include PSN/include RK4/include SO2/include TransferFunction/include VRN/include)
#link_directories(tests)

# Output executables into bin/
set(EXECUTABLE_OUTPUT_PATH "../bin")

# Create transfer_function shared library
add_library(transfer_function SHARED TransferFunction/src/transfer_function.cpp)

# Create neuron shared library (basis)
add_library(neuron SHARED Neuron/src/neuron.cpp)

# Create shared libraries
add_library(psn SHARED PSN/src/psn.cpp)
add_library(rk4 SHARED RK4/src/rk4.cpp)
add_library(so2_cpg SHARED SO2/src/so2_cpg.cpp)
add_library(vrn SHARED VRN/src/vrn.cpp)

#link_directories(/usr/local/lib)

# Create executables:
add_executable(test_basic tests/test_basic.cpp)
target_link_libraries(test_basic transfer_function neuron so2_cpg)

add_executable(test_so2 tests/test_so2.cpp)
target_link_libraries(test_so2 transfer_function neuron so2_cpg)

# Output end message
MESSAGE(${PROJECT_NAME} " done!")