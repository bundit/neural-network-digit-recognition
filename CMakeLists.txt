cmake_minimum_required (VERSION 2.8)

# General compilation options
if (MSVC)
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    add_compile_options(/permissive-)
else()
    add_compile_options(-Wall -Wextra)
endif()

set (CMAKE_CXX_STANDARD 11)

project (neural-net)
add_executable (neural-net-app main.cpp NeuralNetwork.cpp NetLayer.cpp MatrixManipulation.cpp)
