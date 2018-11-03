# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project
PROJECT(Dynamic_computation_and_muscle_model)
MESSAGE(${PROJECT_NAME} ":")

# Use c++11
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Set build type to release
SET(CMAKE_BUILD_TYPE Release)
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})

set(EXECUTABLE_OUTPUT_PATH "../bin")

ADD_EXECUTABLE(rk4 src/rk4_eu2.cpp)
ADD_EXECUTABLE(so2CPG src/so2_cpg_hexapod.cpp)

# Output end message
MESSAGE(${PROJECT_NAME} " done!")