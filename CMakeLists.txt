cmake_minimum_required(VERSION 3.10)
project(SentimentClassifier)

# Set the compiler (this might help if CMake has trouble finding it)
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe") # Replace with your actual g++ path

set(CMAKE_CXX_STANDARD 17)

# Define the source files
set(SOURCES
    src/main.cpp
    src/DSString.cpp
    src/SentimentClassifier.cpp
)

# Add the executable target
add_executable(sentiment ${SOURCES})

# Add the data directory to the build directory (optional)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})