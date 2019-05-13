cmake_minimum_required (VERSION 2.8)
# Our project name
project (neural-net)

# Add flags for C++11 (-std=C++11)
set (CMAKE_CXX_STANDARD 11)

# Require at least C++11, fail if not available
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Prefer extensions that are not compiler specific
set (CMAKE_CXX_EXTENSIONS OFF)

# Output executable named neural-net-app
add_executable (neural-net-app
    # Compile these source files together
    app/main.cpp
    src/NeuralNetwork.cpp
    src/NetLayer.cpp
    src/MatrixManipulation.cpp
)

